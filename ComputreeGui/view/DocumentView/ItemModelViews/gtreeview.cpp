#include "gtreeview.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCompleter>
#include <QWhatsThis>
#include <QLineEdit>
#include <QAction>
#include <QEvent>
#include <QHeaderView>
#include <QProgressDialog>
#include <QApplication>
#include <QToolButton>
#include <QWidgetAction>

#include "dm_colorpicker.h"
#include "dm_guimanager.h"

#include "tools/treeview/dm_sortfiltermathproxymodel.h"

#include "tools/itemdrawable/dm_documentmenugenerator.h"

#include "view/ItemDrawableView/gitemdrawablemanageroptionscolor.h"
#include "tools/graphicsview/dm_pointscolourist.h"

#include "ct_global/ct_context.h"
#include "ct_model/outModel/abstract/ct_outabstractsingularitemmodel.h"
#include "ct_itemdrawable/ct_standarditemgroup.h"
#include "ct_itemdrawable/ct_itemattributelist.h"

int GTreeView::COLUMN_FIRST_DATA_VALUE = 1;

GTreeView::GTreeView(QWidget *parent) : QWidget(parent), GItemModelView()
{
    m_actionsHandler = new DM_ActionsHandlerForTreeView(*GUI_MANAGER->getActionsManager());
    m_contextMenuColorAdder = new DM_ContextMenuColouristAdder(*this);
    m_contextMenuColorAdder->setAutomaticColorProducer(&m_options);
    m_contextMenuColorAdder->setDocumentManager(GUI_MANAGER->getDocumentManagerView());
}

GTreeView::~GTreeView()
{
    delete m_actionsHandler;
    delete m_treeView->model();
    delete m_model;
    delete m_contextMenuColorAdder;
}

void GTreeView::init()
{
    m_typeBuilder.setGetter(&CT_AbstractSingularItemDrawable::model);

    m_contextMenu = new QMenu(this);

    m_model = new CG_CustomTreeItemModel();
    DM_SortFilterMathProxyModel *filterModel = new DM_SortFilterMathProxyModel();
    filterModel->setSourceModel(m_model);
    filterModel->setVariableInMathExpression("(val)");
    filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    m_treeViewController.setStandardItemBuilder(this);
    m_treeViewController.setTreeViewManager(this);
    m_treeViewController.setModel(m_model);

    documentView()->addDocumentAddFilter(this);

    // OPTIONS

    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();

    // a button to sync with other documents
    QPushButton *bSyncWith = new QPushButton(tr("Sync with.."), this);
    hLayout->addWidget(bSyncWith);

    QString wt = tr("<html>"
                    "<p><font size=\"4\"><b>Filtrer une colonne</b></font></p>"
                    "<p>Vous pouvez filtrer une colonne en écrivant son nom puis la valeur à rechercher.</p>"
                    "<p><i>MaColonne : mot</i></p>"
                    "<p></p>"
                    "<p>Vous pouvez aussi filtrer une colonne contenant des nombres en utilisant des fonctions mathématiques. "
                    "Pour celà il vous faut utiliser la syntaxe (val) qui sera remplacée par la valeur de la cellule de la colonne.</p>"
                    "<p><i>MaColonne : (val) &gt; 0 and (val) &lt; 500</i></p>"
                    "</html>");

    m_lineFilter = new QLineEdit(this);
    m_lineFilter->setPlaceholderText(tr("Filtrer la colonne..."));
    m_lineFilter->setWhatsThis(wt);

    QAction *whatThis = QWhatsThis::createAction(nullptr);
    whatThis->setText(wt);

    #if QT_VERSION < QT_VERSION_CHECK(5,2,0)
    m_lineFilter->addAction(whatThis);
    #else
    m_lineFilter->addAction(whatThis,QLineEdit::LeadingPosition);
    #endif

    hLayout->addWidget(m_lineFilter);

    QPushButton *buttonValidFilter = new QPushButton(tr("Valider"), this);
    hLayout->addWidget(buttonValidFilter);

    QPushButton *buttonShowColors = new QPushButton(this);
    buttonShowColors->setIcon(QIcon(":/Icones/Icones/triple-color-icon.png"));
    hLayout->addWidget(buttonShowColors);

    m_gradientManagerView = new GGradientManager(this);
    hLayout->addWidget(m_gradientManagerView);

    connect(m_gradientManagerView, SIGNAL(newGradientSelected(QLinearGradient)), m_contextMenuColorAdder, SLOT(setLinearGradientToUseForColorization(QLinearGradient)));
    m_contextMenuColorAdder->setGradientToUseForColorization(m_gradientManagerView->gradientSelected());

    vLayout->addLayout(hLayout);

    m_treeView = new QTreeView(this);
    m_treeView->setModel(filterModel);
    m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_treeView->setExpandsOnDoubleClick(true);
    //m_treeView->setSortingEnabled(true);
    m_treeView->setAcceptDrops(true);
    vLayout->addWidget(m_treeView);

    delete layout();
    setLayout(vLayout);

    // QMENU
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->header()->setContextMenuPolicy(Qt::CustomContextMenu);

    // EVENT
    m_treeView->installEventFilter(this);
    m_treeView->viewport()->installEventFilter(this);
    m_treeView->viewport()->setMouseTracking(true);

    // SIGNALS-SLOTS CONNECTION
    connect(documentView(), SIGNAL(itemDrawableAdded(CT_AbstractItemDrawable&)), this, SLOT(slotAddItemDrawable(CT_AbstractItemDrawable&)), Qt::DirectConnection);
    connect(documentView(), SIGNAL(itemDrawableToBeRemoved(CT_AbstractItemDrawable&)), this, SLOT(slotRemoveItemDrawable(CT_AbstractItemDrawable&)), Qt::DirectConnection);

    qRegisterMetaType<ItemDrawableTypeResult>("ItemDrawableTypeResult");
    connect(&m_typeBuilder, SIGNAL(removed()), this, SLOT(slotItemTypeRemoved()), Qt::QueuedConnection);
    connect(&m_typeBuilder, SIGNAL(added()), this, SLOT(slotNewItemTypeDetected()), Qt::QueuedConnection);

    connect(bSyncWith, SIGNAL(clicked()), this, SLOT(slotButtonSyncWithClicked()));

    connect(buttonShowColors, SIGNAL(clicked()), this, SLOT(slotShowColorOptions()));

    connect(m_treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotShowContextMenu(QPoint)), Qt::QueuedConnection);
    connect(m_treeView->header(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotShowHeaderContextMenu(QPoint)), Qt::QueuedConnection);
    connect(m_treeView->header(), SIGNAL(sectionClicked(int)), this, SLOT(slotHeaderSectionClicked(int)), Qt::DirectConnection);

    connect(m_treeView, SIGNAL(activated(QModelIndex)), this, SLOT(slotActivated(QModelIndex)), Qt::DirectConnection);
    connect(m_treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotClicked(QModelIndex)), Qt::DirectConnection);
    connect(m_treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotDoubleClicked(QModelIndex)), Qt::DirectConnection);
    connect(m_treeView, SIGNAL(expanded(QModelIndex)), this, SLOT(slotExpanded(QModelIndex)), Qt::DirectConnection);
    connect(m_treeView, SIGNAL(collapsed(QModelIndex)), this, SLOT(slotCollapsed(QModelIndex)), Qt::DirectConnection);

    connect(buttonValidFilter, SIGNAL(clicked()), this, SLOT(slotSetTextFilter()));

    m_typeBuilder.setNLevel(m_options.nLevelFiltering());

    refreshHeaders();
}

QWidget* GTreeView::getViewWidget() const
{
    return const_cast<GTreeView*>(this);
}

void GTreeView::beginAddMultipleItemDrawable()
{
    m_treeViewController.beginAddMultipleItemDrawable();
}

void GTreeView::slotAddItemDrawable(CT_AbstractItemDrawable &item)
{
    m_typeBuilder.addItemDrawable(item);

    m_treeViewController.addItemDrawable(item);
}

void GTreeView::endAddMultipleItemDrawable()
{
    m_treeViewController.endAddMultipleItemDrawable();
}

void GTreeView::beginRemoveMultipleItemDrawable()
{
    m_treeViewController.beginRemoveMultipleItemDrawable();
}

void GTreeView::slotRemoveItemDrawable(CT_AbstractItemDrawable &item)
{
    m_typeBuilder.removeItemDrawable(item);

    m_treeViewController.removeItemDrawable(item);
    m_expandedItems.removeOne(&item);
}

void GTreeView::endRemoveMultipleItemDrawable()
{
    m_treeViewController.endRemoveMultipleItemDrawable();
}

void GTreeView::slotButtonSyncWithClicked()
{
    emit syncWith(this);
}

void GTreeView::slotActivated(const QModelIndex &index)
{
    actionsHandlerTreeView()->indexActivatedEvent(index);
}

void GTreeView::slotClicked(const QModelIndex &index)
{
    actionsHandlerTreeView()->indexClickedEvent(index);
}

void GTreeView::slotDoubleClicked(const QModelIndex &index)
{
    actionsHandlerTreeView()->indexDoubleClickedEvent(index);
}

void GTreeView::slotExpanded(const QModelIndex &index)
{
    CT_AbstractItemDrawable *item = itemDrawableFromIndex(index);

    if(!m_expandedItems.contains(item))
        m_expandedItems.append(item);

    actionsHandlerTreeView()->indexExpandedEvent(index);
}

void GTreeView::slotCollapsed(const QModelIndex &index)
{
    m_expandedItems.removeOne(itemDrawableFromIndex(index));
    actionsHandlerTreeView()->indexCollapsedEvent(index);
}

void GTreeView::slotSetTextFilter()
{
    QString textToUse = m_lineFilter->text();
    int columnToUse = -1;
    bool continueLoop = true;

    DataReferenceCollectionIterator it(m_dataReferencesToUse);

    while(it.hasNext()
            && continueLoop)
    {
        it.next();

        const QString str = it.key()->displayableName() + " : ";

        if(m_lineFilter->text().startsWith(str))
        {
            columnToUse = it.value();
            textToUse.remove(str);
            continueLoop = false;
        }
    }

    if(!continueLoop)
    {
        columnToUse += COLUMN_FIRST_DATA_VALUE;

        ((QSortFilterProxyModel*)m_treeView->model())->setFilterKeyColumn(columnToUse);

        if(!textToUse.contains(((DM_SortFilterMathProxyModel*)m_treeView->model())->variableInMathExpression()))
        {
            bool ok = true;
            QMessageBox::StandardButton button = fetchAllQuestion(tr("Le modèle n'est pas chargé complètement, voulez vous le charger avant de faire la recherche ?"),
                                                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            if(button == QMessageBox::Yes)
            {
                ((DM_SortFilterMathProxyModel*)m_treeView->model())->setAcceptRows(false);
                ok = fetchAll();
                ((DM_SortFilterMathProxyModel*)m_treeView->model())->setAcceptRows(true, false);
            }
            else if(button == QMessageBox::Cancel)
                ok = false;

            if(ok)
            {
                ((QSortFilterProxyModel*)m_treeView->model())->setFilterFixedString(textToUse);

                setValidColorForLineFilter(true);
            }
        }
        else
        {
            if(((DM_SortFilterMathProxyModel*)m_treeView->model())->canSetMathExpression(textToUse))
            {
                bool ok = true;
                QMessageBox::StandardButton button = fetchAllQuestion(tr("Le modèle n'est pas chargé complètement, voulez vous le charger avant de faire la recherche ?"),
                                                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

                if(button == QMessageBox::Yes)
                {
                    ((DM_SortFilterMathProxyModel*)m_treeView->model())->setAcceptRows(false);
                    ok = fetchAll();
                    ((DM_SortFilterMathProxyModel*)m_treeView->model())->setAcceptRows(true, false);
                }
                else if(button == QMessageBox::Cancel)
                    ok = false;

                if(ok)
                    setValidColorForLineFilter(((DM_SortFilterMathProxyModel*)m_treeView->model())->setMathExpression(textToUse));
            }
            else
            {
                setValidColorForLineFilter(false);
            }
        }

        return;
    }

    ((QSortFilterProxyModel*)m_treeView->model())->setFilterKeyColumn(-1);
    ((DM_SortFilterMathProxyModel*)m_treeView->model())->setMathExpression("");

    setValidColorForLineFilter(m_lineFilter->text().isEmpty());
}

void GTreeView::slotShowContextMenu(const QPoint &p)
{
    if(!actionsHandlerTreeView()->showContextMenu(p))
    {
        initContextMenu();
        m_contextMenu->exec(treeViewport()->mapToGlobal(p));
    }
}

void GTreeView::slotShowHeaderContextMenu(const QPoint &p)
{
    actionsHandlerTreeView()->showContextMenuOnHorizontalHeader(p);
}

void GTreeView::slotHeaderSectionClicked(int logicalIndex)
{
    Q_UNUSED(logicalIndex)

    if(fetchAllQuestion(tr("Le modèle n'est pas chargé complètement, voulez vous le charger pour utiliser tous les éléments dans le tri ?\n\nAttention cette opération peut être lente."),
                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        fetchAll();
}

void GTreeView::slotResetColorLineFilter()
{
    m_lineFilter->setStyleSheet("QLineEdit{background: white;}");
}

void GTreeView::slotItemDataChanged(CG_CustomTreeItem *item, int role, QVariant value)
{
    Q_UNUSED(value)

    CT_AbstractItemDrawable *itemDrawable = itemDrawableFromItem(item);

    if(itemDrawable != nullptr)
    {
        if(role == Qt::CheckStateRole)
        {
            bool selected = (item->checkState() == Qt::Checked);

            if(itemDrawable->isSelected() != selected)
            {
                itemDrawable->setSelected(selected);
                GUI_MANAGER->getDocumentManagerView()->redrawAllDocument();
            }
        }
    }
}

void GTreeView::slotShowColorOptions()
{
    GItemDrawableManagerOptionsColor dialog(this);

    dialog.setOptions(m_options);

    if(dialog.exec())
        m_options.setColorList(dialog.getColorList());
}

void GTreeView::slotSelect()
{
    QList<CT_AbstractItemDrawable*> sel = itemDrawableFromRowSelected();
    QListIterator<CT_AbstractItemDrawable*> it(sel);

    while(it.hasNext())
        it.next()->setSelected(true);

    GUI_MANAGER->getDocumentManagerView()->redrawAllDocument();
}

void GTreeView::slotDeSelect()
{
    QList<CT_AbstractItemDrawable*> sel = itemDrawableFromRowSelected();
    QListIterator<CT_AbstractItemDrawable*> it(sel);

    while(it.hasNext())
        it.next()->setSelected(false);

    GUI_MANAGER->getDocumentManagerView()->redrawAllDocument();
}

void GTreeView::slotInverseSelection()
{
    QList<CT_AbstractItemDrawable*> sel = itemDrawableFromRowSelected();
    QListIterator<CT_AbstractItemDrawable*> it(sel);

    while(it.hasNext())
    {
        CT_AbstractItemDrawable *ii = it.next();
        ii->setSelected(!ii->isSelected());
    }

    GUI_MANAGER->getDocumentManagerView()->redrawAllDocument();
}


void GTreeView::slotAddSelectedToDocument()
{
    QAction *act = (QAction*)sender();
    int number = act->data().toInt();

    QList<DocumentInterface*> documents = GUI_MANAGER->getDocumentManagerView()->documents();
    QListIterator<DocumentInterface*> it(documents);

    while(it.hasNext())
    {
        DM_DocumentView *doc = (DM_DocumentView*)it.next();

        if(doc->getNumber() == number)
        {
            QList<CT_AbstractItemDrawable *> items = itemDrawableFromRowSelected();

            GUI_MANAGER->asyncAddAllItemDrawableOfListOnView(items, doc, nullptr);

            return;
        }
    }
}

void GTreeView::slotRemoveSelectedFromDocument()
{
    QAction *act = (QAction*)sender();
    int number = act->data().toInt();

    QList<DocumentInterface*> documents = GUI_MANAGER->getDocumentManagerView()->documents();
    QListIterator<DocumentInterface*> it(documents);

    while(it.hasNext())
    {
        DM_DocumentView *doc = (DM_DocumentView*)it.next();

        if(doc->getNumber() == number)
        {
            QList<CT_AbstractItemDrawable *> items = itemDrawableFromRowSelected();

            GUI_MANAGER->asyncRemoveAllItemDrawableOfListFromView(items, doc, nullptr);

            return;
        }
    }
}

void GTreeView::slotRefreshSelected()
{
    QList<CT_AbstractItemDrawable *> items = itemDrawableFromRowSelected();
    refreshItems(items);
}

DM_ActionsHandler* GTreeView::actionsHandler() const
{
    return m_actionsHandler;
}

CG_CustomTreeItem* GTreeView::itemFromIndex(const QModelIndex &proxyIndex) const
{
    return m_model->itemFromIndex(((DM_SortFilterMathProxyModel*)m_treeView->model())->mapToSource(proxyIndex));
}

CT_AbstractItemDrawable* GTreeView::itemDrawableFromItem(const CG_CustomTreeItem *item) const
{
    return (CT_AbstractItemDrawable*)item->data().value<void*>();
}

CT_AbstractItemDrawable *GTreeView::itemDrawableFromIndex(const QModelIndex &index) const
{
    return (CT_AbstractItemDrawable*)m_model->itemFromIndex(((DM_SortFilterMathProxyModel*)m_treeView->model())->mapToSource(index))->data().value<void*>();
}

QModelIndex GTreeView::indexAt(const QPoint &point) const
{
    return m_treeView->indexAt(point);
}

QWidget* GTreeView::treeViewport() const
{
    return m_treeView->viewport();
}

void GTreeView::setSelectionMode(QAbstractItemView::SelectionMode mode)
{
    m_treeView->setSelectionMode(mode);
}

QAbstractItemView::SelectionMode GTreeView::selectionMode() const
{
    return m_treeView->selectionMode();
}

QModelIndexList GTreeView::selectedIndexes() const
{
    return m_treeView->selectionModel()->selectedIndexes();
}

QItemSelectionModel* GTreeView::selectionModel() const
{
    return m_treeView->selectionModel();
}

void GTreeView::refreshAll()
{
    construct();
}

void GTreeView::refreshItems(const QList<QModelIndex> &indexes)
{
    QList<QPair<CG_CustomTreeItem *, CT_AbstractItemDrawable *> > list;

    QListIterator<QModelIndex> it(indexes);

    while(it.hasNext())
    {
        const QModelIndex &i = it.next();
        list << qMakePair(itemFromIndex(i), itemDrawableFromIndex(i));
    }

    m_treeViewController.refresh(list);
}

void GTreeView::refreshItems(const QList<CT_AbstractItemDrawable*> &items)
{
    QList<QPair<CG_CustomTreeItem *, CT_AbstractItemDrawable *> > list;

    QListIterator<CT_AbstractItemDrawable*> it(items);

    while(it.hasNext())
    {
        CT_AbstractItemDrawable *i = it.next();
        list << qMakePair(itemFromItemDrawable(i), i);
    }

    m_treeViewController.refresh(list);
}

QList<CG_CustomTreeItem *> GTreeView::createItems(const CT_AbstractItemDrawable &item, const int &level) const
{
    QList<CG_CustomTreeItem *> l;

    // if we are synchronized with other documents
    if((level == 0)
            && isSyncedWithAnotherDocument())
    {
        if(!item.isSelected())
            return l;

        QList<IDocumentForModel*> docs;
        item.visitDocumentsWhereThisItemIs([&docs](const IDocumentForModel* doc) -> bool {
            docs.append(const_cast<IDocumentForModel*>(doc));
            return true;
        });

        QListIterator<DM_DocumentView*> it(syncGroup()->documentViews());

        bool continueLoop = true;

        while(it.hasNext()
                && continueLoop)
            continueLoop = !docs.contains(it.next());

        if(continueLoop)
            return l;
    }

    // selectionné
    CG_CustomTreeItem *itemDisplay = new CG_CustomTreeItem();
    itemDisplay->setEditable(false);
    itemDisplay->setCheckable(true);
    itemDisplay->setCheckState(item.isSelected() ? Qt::Checked : Qt::Unchecked);
    itemDisplay->setText(item.model()->displayableName());
    itemDisplay->setData(QVariant::fromValue((void*)&item), Qt::UserRole + 1);

    QObject::connect(&item, SIGNAL(selectChange(bool)), itemDisplay, SLOT(setBoolData(bool)), Qt::DirectConnection);
    QObject::connect(itemDisplay, SIGNAL(dataChanged(CG_CustomTreeItem*,int,QVariant)), this, SLOT(slotItemDataChanged(CG_CustomTreeItem*,int,QVariant)), Qt::QueuedConnection);

    l << itemDisplay;

    const int nColumnOfAttributes = m_dataReferencesToUse.size();

    for(int i=0; i<nColumnOfAttributes; ++i)
    {
        CG_CustomTreeItem *ii = new CG_CustomTreeItem();
        ii->setData(QVariant::fromValue((void*)&item));
        ii->setEditable(false);
        l << ii;
    }

    if(dynamic_cast<const CT_AbstractSingularItemDrawable*>(&item) != nullptr)
    {
        QList<CT_AbstractItemAttribute*> lIA = ((const CT_AbstractSingularItemDrawable&)item).itemAttributes();
        QListIterator<CT_AbstractItemAttribute*> itIA(lIA);

        while(itIA.hasNext())
        {
            CT_AbstractItemAttribute *att = itIA.next();
            const int index = m_dataReferencesToUse.value(att->model()->recursiveOriginalModel(), -1);

            if(index != -1)
            {
                CG_CustomTreeItem *ii = l.at(index + GTreeView::COLUMN_FIRST_DATA_VALUE);
                ii->setText(att->toString((const CT_AbstractSingularItemDrawable*)&item, nullptr));
            }
        }
    }
    else
    {
        const CT_StandardItemGroup *group = dynamic_cast<const CT_StandardItemGroup*>(&item);

        if(group != nullptr)
        {
            const DataReferenceCollection& ref = m_dataReferencesToUse;

            group->visitChildrensForTreeView([&ref, &l](const CT_AbstractItem* child) -> bool {
                const CT_ItemAttributeList* sI = dynamic_cast<const CT_ItemAttributeList*>(child);

                if(sI != nullptr)
                {
                    const QList<CT_AbstractItemAttribute*> lIA = sI->itemAttributes();
                    QListIterator<CT_AbstractItemAttribute*> itIA(lIA);

                    while(itIA.hasNext())
                    {
                        CT_AbstractItemAttribute *att = itIA.next();
                        const int index = ref.value(att->model()->recursiveOriginalModel(), -1);

                        if(index != -1)
                        {
                            CG_CustomTreeItem* ii = l.at(index + GTreeView::COLUMN_FIRST_DATA_VALUE);

                            if(!ii->text().isEmpty())
                                ii->setText(ii->text() + " / ");

                            ii->setText(ii->text() + att->toString(sI, nullptr));
                        }
                    }
                }

                return true;
            });
        }
    }

    return l;
}

bool GTreeView::canConstructTheModel() const
{
    return !m_typeBuilder.isEmpty();
}

QList<CT_AbstractItemDrawable *> GTreeView::itemDrawableForTreeView() const
{
    return documentView()->getItemDrawable();
}

int GTreeView::nLevelToConstruct() const
{
    return m_options.nLevelFiltering();
}

QList<CT_AbstractItemDrawable *> GTreeView::expandedItem() const
{
    return m_expandedItems;
}

CG_CustomTreeItem* GTreeView::itemFromItemDrawable(const CT_AbstractItemDrawable *item) const
{
    CG_CustomTreeItem *root = m_model->invisibleRootItem();

    return recursiveItemFromItemDrawable(root, item);
}

void GTreeView::refreshHeaders()
{
    QVector<QString> head;
    head.resize(m_dataReferencesToUse.size() + COLUMN_FIRST_DATA_VALUE);

    // if you change head order or add some pre-defined column you must change => COLUMN_FIRST_DATA_VALUE
    head.replace(0, tr("Sel."));

    QHashIterator<CT_OutAbstractModel*, int> it(m_dataReferencesToUse);

    while(it.hasNext()) {
        it.next();
        head.replace(it.value() + COLUMN_FIRST_DATA_VALUE, it.key()->displayableName());
    }

    m_model->setHorizontalHeaderLabels(head.toList());

    #if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    m_treeView->header()->setResizeMode(QHeaderView::ResizeToContents);
    #else
    m_treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    #endif

    m_treeView->header()->setStretchLastSection(false);

    m_model->finishAppendRows();
}

void GTreeView::refreshExpanded()
{
    int n = m_treeView->model()->rowCount();

    for(int i=0; i<n; ++i)
    {
        QModelIndex child = m_treeView->model()->index(i, 0);

        CG_CustomTreeItem *ii = itemFromIndex(child);
        CT_AbstractItemDrawable *item = itemDrawableFromItem(ii);

        bool ex = false;

        if(item != nullptr && m_expandedItems.contains(item))
        {
            ex = true;
            m_treeView->setExpanded(child, true);
        }

        recursiveRefreshExpanded(child, ii, ex);
    }
}

DM_ActionsHandlerForTreeView* GTreeView::actionsHandlerTreeView() const
{
    return m_actionsHandler;
}

QList<CT_AbstractItemDrawable *> GTreeView::itemDrawableFromRowSelected() const
{
    QList<CT_AbstractItemDrawable*> listItem;

    QModelIndexList listSelected = m_treeView->selectionModel()->selectedRows();
    QListIterator<QModelIndex> it(listSelected);

    while(it.hasNext())
    {
        CT_AbstractItemDrawable *id = itemDrawableFromItem(itemFromIndex(it.next()));

        if(id != nullptr)
            listItem.append(id);
    }

    return listItem;
}

QMessageBox::StandardButton GTreeView::fetchAllQuestion(const QString &text, QMessageBox::StandardButtons buttons)
{
    if(m_model->canFetchMore(QModelIndex()))
    {
        return QMessageBox::question(this,
                                     tr("Question"),
                                     text,
                                     buttons);
    }

    return QMessageBox::No;
}

bool GTreeView::fetchAll()
{
    int fetchSize = m_model->invisibleRootItem()->fetchSize();

    QProgressDialog pDialog(tr("Veuillez patienter pendant le chargement de la table..."), tr("Annuler"), 0, 100, this);
    pDialog.setWindowModality(Qt::WindowModal);
    pDialog.setValue(0);
    pDialog.show();

    int size = m_model->invisibleRootItem()->nChildrens();
    int progress = 0;

    m_model->invisibleRootItem()->setFetchSize(size/15);

    while(m_model->canFetchMore(QModelIndex())
          && !pDialog.wasCanceled())
    {
        m_model->fetchMore(QModelIndex());

        int tmpProgress = (m_model->invisibleRootItem()->rowCount()*100)/size;

        if(tmpProgress != progress)
        {
            progress = tmpProgress;
            pDialog.setValue(progress);
        }

        qApp->processEvents();
    }

    bool c = pDialog.wasCanceled();

    pDialog.close();

    m_model->invisibleRootItem()->setFetchSize(fetchSize);

    return !c;
}

bool GTreeView::canAddItemDrawable(const DM_Document *document, const CT_AbstractItemDrawable *item) const
{
    Q_UNUSED(document)

    if(!isSyncedWithAnotherDocument())
        return true;

    return (item == nullptr) || item->isSelected();
}

bool GTreeView::isSyncedWithAnotherDocument() const
{
    return (syncGroup() != nullptr)
            && !syncGroup()->documentViews().isEmpty();
}

bool GTreeView::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_treeView)
    {
        if(event->type() == QEvent::DragEnter)
        {
            if(actionsHandlerTreeView()->itemDragEnterEvent((QDragEnterEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::DragMove)
        {
            if(actionsHandlerTreeView()->itemDragMoveEvent((QDragMoveEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::DragLeave)
        {
            if(actionsHandlerTreeView()->itemDragLeaveEvent((QDragLeaveEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::Drop)
        {
            if(actionsHandlerTreeView()->itemDropEvent((QDropEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::KeyPress)
        {
            if(actionsHandlerTreeView()->keyPressEvent((QKeyEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::KeyRelease)
        {
            if(actionsHandlerTreeView()->keyReleaseEvent((QKeyEvent*)event))
                return true;
        }
    }
    else if(obj == m_treeView->viewport())
    {
        if(event->type() == QEvent::MouseMove)
        {
            if(actionsHandlerTreeView()->mouseMoveEvent((QMouseEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            if(actionsHandlerTreeView()->mousePressEvent((QMouseEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if(actionsHandlerTreeView()->mouseReleaseEvent((QMouseEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            if(actionsHandlerTreeView()->mouseDoubleClickEvent((QMouseEvent*)event))
                return true;
        }
        else if(event->type() == QEvent::Wheel)
        {
            if(actionsHandlerTreeView()->wheelEvent((QWheelEvent*)event))
                return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}

QList<CT_AbstractModel *> GTreeView::getSelectedModelsToUseInColorizerMenu() const
{
    QList<CT_AbstractModel *> models;

    QList<CT_AbstractItemDrawable*> l = itemDrawableFromRowSelected();
    QListIterator<CT_AbstractItemDrawable*> it(l);

    while(it.hasNext()) {
        models.append(it.next()->model());
    }

    return models;
}

QList<CT_AbstractItemDrawable *> GTreeView::getItemDrawableToColorize() const
{
    return itemDrawableFromRowSelected();
}

CG_CustomTreeItem *GTreeView::recursiveItemFromItemDrawable(CG_CustomTreeItem *parent, const CT_AbstractItemDrawable *item) const
{
    int size = parent->rowCount();

    for(int i=0; i<size; ++i)
    {
        CG_CustomTreeItem *it = parent->child(i, 0);

        if(itemDrawableFromItem(it) == item)
            return it;

        it = recursiveItemFromItemDrawable(it, item);

        if(it != nullptr)
            return it;
    }

    return nullptr;
}

void GTreeView::initContextMenu()
{
    m_contextMenu->clear();

    QAction *action = m_contextMenu->addAction(tr("Sélectionner"));
    action->setEnabled(true);
    connect(action, SIGNAL(triggered()), this, SLOT(slotSelect()));

    action = m_contextMenu->addAction(tr("Dé-Sélectionner"));
    action->setEnabled(true);
    connect(action, SIGNAL(triggered()), this, SLOT(slotDeSelect()));

    action = m_contextMenu->addAction(tr("Inverser la sélection"));
    action->setEnabled(true);
    connect(action, SIGNAL(triggered()), this, SLOT(slotInverseSelection()));

    m_contextMenu->addSeparator();
    m_contextMenuColorAdder->initContextMenu(m_contextMenu);
    m_contextMenu->addSeparator();

    DM_DocumentMenuGenerator generator;
    m_contextMenu->addMenu(generator.createMenuXXXToDocuments(tr("Ajouter au document"), this, SLOT(slotAddSelectedToDocument()), QList<int>() << documentView()->getNumber()));
    m_contextMenu->addMenu(generator.createMenuXXXToDocuments(tr("Supprimer du document"), this, SLOT(slotRemoveSelectedFromDocument()), QList<int>() << documentView()->getNumber()));
}

void GTreeView::setValidColorForLineFilter(bool valid)
{
    m_lineFilter->setStyleSheet(QString("QLineEdit{background: ") + (valid ? "green" : "red") + ";}");

    QTimer::singleShot(500, this, SLOT(slotResetColorLineFilter()));
}

void GTreeView::reconstructReferencesToUse()
{
    DataReferenceCollection uniqueReferences;

    QList<ItemDrawableTypeResult> types = m_typeBuilder.types();
    QListIterator<ItemDrawableTypeResult> it(types);

    while(it.hasNext())
    {
        const ItemDrawableTypeResult &type = it.next();

        if(!type.isEmpty())
            recursiveAddToReferencesToUseForModel(uniqueReferences, type.type());
    }

    m_dataReferencesToUse = uniqueReferences;
}

void GTreeView::recursiveAddToReferencesToUseForModel(DataReferenceCollection& uniqueReferences,
                                                      const CT_OutAbstractModel* model)
{
    model->recursiveVisitOutChildrens([&uniqueReferences](const CT_OutAbstractModel* child) -> bool {
        if(dynamic_cast<const CT_OutAbstractSingularItemModel*>(child) != nullptr)
        {
            const CT_OutAbstractSingularItemModel* sModel = static_cast<const CT_OutAbstractSingularItemModel*>(child);

            sModel->visitAttributes([&uniqueReferences](const CT_OutAbstractItemAttributeModel* att) -> bool {
                CT_OutAbstractModel* newModel = att->recursiveOriginalModel();

                if(!uniqueReferences.contains(newModel))
                    uniqueReferences.insert(newModel, uniqueReferences.size());

                return true;
            });
        } else {
            CT_OutAbstractModel* newModel = child->recursiveOriginalModel();

            if(!uniqueReferences.contains(newModel))
                uniqueReferences.insert(newModel, uniqueReferences.size());
        }

        return true;
    });
}

void GTreeView::reconstructCompleter()
{
    QStringList comp;

    DataReferenceCollectionIterator itH(m_dataReferencesToUse);

    while(itH.hasNext())
    {
        itH.next();

        const QString dName = itH.key()->displayableName() + " : ";
        comp << dName;
        comp << (dName + ((DM_SortFilterMathProxyModel*)m_treeView->model())->variableInMathExpression());
    }

    QCompleter *lastCompleter = m_lineFilter->completer();
    QCompleter *completer = nullptr;

    if(!comp.isEmpty())
    {
        completer = new QCompleter(comp);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    }

    m_lineFilter->setCompleter(completer);

    delete lastCompleter;
}

void GTreeView::recursiveRefreshExpanded(const QModelIndex &index, CG_CustomTreeItem *item, bool expanded)
{
    if(expanded && item->canFetchMore())
        item->fetchMore(index);

    int n = item->rowCount();

    for(int i=0; i<n; ++i)
    {
        QModelIndex child = index.model()->index(i, 0, index);

        CG_CustomTreeItem *ii = itemFromIndex(child);
        CT_AbstractItemDrawable *itemDrawable = itemDrawableFromItem(ii);

        bool ex = false;

        if(itemDrawable != nullptr && m_expandedItems.contains(itemDrawable))
        {
            ex = true;
            m_treeView->setExpanded(child, true);
        }

        recursiveRefreshExpanded(child, ii, ex);
    }
}

void GTreeView::slotNewItemTypeDetected()
{
    reconstructReferencesToUse();
    reconstructCompleter();
    construct();
}

void GTreeView::slotItemTypeRemoved()
{
    reconstructReferencesToUse();
    reconstructCompleter();
    construct();
}

void GTreeView::construct()
{
    m_treeViewController.constructModel();
}
