/****************************************************************************

 Copyright (C) 2010-2012 the Office National des Forêts (ONF), France
                     and the Association de Recherche Technologie et Sciences (ARTS), Ecole Nationale Suprieure d'Arts et Métiers (ENSAM), Cluny, France.
                     All rights reserved.

 Contact : alexandre.piboule@onf.fr

 Developers : MichaÃ«l KREBS (ARTS/ENSAM)

 This file is part of Computree version 2.0.

 Computree is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Computree is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Computree.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/


#include "gdocumentmanagerview.h"

#include "dm_guimanager.h"

#include "gdocumentviewforgraphics.h"
#include "gdocumentviewforitemmodel.h"
#include "view/DocumentView/ItemModelViews/gtreeview.h"
#include "view/DocumentView/GraphicsViews/3D/ggraphicsviewimp.h"
#include "view/DocumentView/GraphicsViews/ggraphicsviewsynchronizedgroup.h"

#include "ct_result/abstract/ct_abstractresult.h"
#include "ct_iterator/ct_singlemodeliteratorstdstyleforresultgroup.h"

#include <QMdiSubWindow>

GDocumentManagerView::GDocumentManagerView(QWidget *parent) : QMdiArea(parent), DM_DocumentManagerView()
{
    m_mutex = new QMutex(QMutex::Recursive);
    m_windowCount = 0;
    m_timer.setInterval(100);
    m_syncMan = nullptr;
    m_lastDocumentActivated = nullptr;
    m_manualModeEnabled = false;
    m_manualModeEnabledByStep = nullptr;

    connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(subWindowHasBeenActivated(QMdiSubWindow*)));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(verifyNumberWindow()));
}

GDocumentManagerView::~GDocumentManagerView()
{
    delete m_mutex;
}

void GDocumentManagerView::setSyncManager(const GGraphicsViewSynchronizedGroup *syncMan)
{
    m_syncMan = (GGraphicsViewSynchronizedGroup*)syncMan;
}

void GDocumentManagerView::addDocumentView(GDocumentView &view, bool fromGui, bool inLoadConfigurationFromMainWindow)
{
    view.getSubWindow()->setParent(this);
    view.setDocumentCloseFilter(this);
    view.addDocumentAddFilter(this);

    if(inLoadConfigurationFromMainWindow) {
        view.getSubWindow()->showNormal();
    } else {
        if(subWindowList().isEmpty())
        {
            view.getSubWindow()->showMaximized();
        }
        else
        {
            if((activeSubWindow() != nullptr)
                && activeSubWindow()->isMaximized())
                activeSubWindow()->showNormal();

            view.getSubWindow()->showNormal();
            tileSubWindows();
        }
    }

    connect(&view, SIGNAL(closed(DM_DocumentView*)), this, SIGNAL(documentToBeClosed(DM_DocumentView*)), Qt::DirectConnection);
    connect(&view, SIGNAL(destroyed()), this, SLOT(slotDocumentDestroyed()), Qt::DirectConnection);
    connect(&view, SIGNAL(destroyed()), &m_timer, SLOT(start()));

    if(m_manualModeEnabled)
    {
        m_docToCloseAfterQuitManualMode.append(&view);

        if(fromGui)
            m_docFromGuiAddedInManualMode.append(&view);
    }
    else
    {
        m_docAddedInNormalMode.append(&view);
    }

    emit documentAdded(&view);
    ++m_windowCount;

    m_lastDocumentActivated = view.getSubWindow();
    setActiveSubWindow(view.getSubWindow());

    emit documentActivated(&view);
}

bool GDocumentManagerView::addAllItemDrawableOfResultToActiveDocument(CT_AbstractResult &res, DM_AsynchroneProgress &progress)
{
    DM_DocumentView *activeDoc = getActiveDocumentView();

    return addAllItemDrawableOfResultToDocument(res, activeDoc, progress);
}

bool GDocumentManagerView::addAllItemDrawableOfModelToDocument(CT_AbstractResult &res, CT_OutAbstractItemModel &model, DM_DocumentView *doc, DM_AsynchroneProgress &progress)
{
    if((doc != nullptr)
            && !res.isBusy())
    {
        progress.setProgress(0);

        res.setBusy(true);

        auto iterator = CT_SingleModelIteratorStdStyleForResultGroup<CT_AbstractItemDrawable>::createCompleteIterator(&model);

        //const int n = 299;
        const int n = iterator.count();

        if(n != 0)
        {
            int i = 0;

            if(n > 1)
                doc->beginAddMultipleItemDrawable();

            for(CT_AbstractItemDrawable* item : iterator) {

                if(item != nullptr)
                    doc->addItemDrawable(*item);

                ++i;
                progress.setProgress(((float)(i*100))/n);
            }


            if(n > 1)
                doc->endAddMultipleItemDrawable();

            doc->redrawGraphics();
        }

        progress.setProgress(100);

        res.setBusy(false);

        return true;
    }

    return false;
}

bool GDocumentManagerView::addAllItemDrawableOfResultToDocument(CT_AbstractResult &res, DM_DocumentView *doc, DM_AsynchroneProgress &progress)
{
    if((doc != nullptr)
            && !res.isBusy())
    {
        progress.setProgress(0);

        res.setBusy(true);

        const int n = res.nChildrens();

        if(n != 0)
        {
            int i = 0;

            if(n > 1)
                doc->beginAddMultipleItemDrawable();

            res.visitChildrens([&doc, &i, &progress, &n](const CT_AbstractItem* child) -> bool {
                CT_AbstractItemDrawable* item = dynamic_cast<CT_AbstractItemDrawable*>(const_cast<CT_AbstractItem*>(child));

                if(item != nullptr)
                    doc->addItemDrawable(*item);

                ++i;
                progress.setProgress(((float)(i*100))/n);

                return true;
            });

            if(n > 1)
                doc->endAddMultipleItemDrawable();

            doc->redrawGraphics();
        }

        progress.setProgress(100);

        res.setBusy(false);

        return true;
    }

    return false;
}

bool GDocumentManagerView::addAllItemDrawableOfListToActiveDocument(QList<CT_AbstractItemDrawable*> &itemList, DM_AsynchroneProgress &progress)
{
    DM_DocumentView *activeDoc = getActiveDocumentView();

    return addAllItemDrawableOfListToDocument(itemList, activeDoc, progress);
}

bool GDocumentManagerView::addAllItemDrawableOfListToDocument(QList<CT_AbstractItemDrawable*> &itemList, DM_DocumentView *doc, DM_AsynchroneProgress &progress)
{
    if(doc != nullptr)
    {
        progress.setProgress(0);

        if(!itemList.isEmpty())
        {
            int n = itemList.size();
            int i = 0;

            QListIterator<CT_AbstractItemDrawable*> it(itemList);

            if(n > 1)
                doc->beginAddMultipleItemDrawable();

            while(it.hasNext())
            {
                doc->addItemDrawable(*(it.next()));

                ++i;
                progress.setProgress(((float)(i*100))/n);
            }

            if(n > 1)
                doc->endAddMultipleItemDrawable();

            doc->redrawGraphics();
        }

        progress.setProgress(100);

        return true;
    }

    return false;
}

bool GDocumentManagerView::removeAllItemDrawableOfResultFromDocuments(CT_AbstractResult &res, DM_AsynchroneProgress &progress)
{
    progress.setProgress(0);

    QList<QMdiSubWindow *> list = subWindowList();
    QListIterator<QMdiSubWindow *> it(list);

    int i = 0;
    int n = list.size();

    while(it.hasNext())
    {
        DM_DocumentView *dv = ((MyQMdiSubWindow*)it.next())->getDocumentView();
        dv->removeAllItemDrawableOfResult(res);

        ++i;
        progress.setProgress(((float)(i*100))/n);
    }

    progress.setProgress(100);

    return true;
}

bool GDocumentManagerView::removeAllItemDrawableOfModelFromDocuments(CT_OutAbstractItemModel &model, DM_AsynchroneProgress &progress)
{
    progress.setProgress(0);

    QList<QMdiSubWindow *> list = subWindowList();
    QListIterator<QMdiSubWindow *> it(list);

    int i = 0;
    int n = list.size();

    while(it.hasNext())
    {
        DM_DocumentView *dv = ((MyQMdiSubWindow*)it.next())->getDocumentView();
        dv->removeAllItemDrawableOfModel(model);

        ++i;
        progress.setProgress(((float)(i*100))/n);
    }

    progress.setProgress(100);

    return true;
}

bool GDocumentManagerView::removeAllItemDrawableOfModelFromDocument(CT_OutAbstractItemModel &model, DM_DocumentView *doc, DM_AsynchroneProgress &progress)
{
    progress.setProgress(0);

    if(doc != nullptr)
        doc->removeAllItemDrawableOfModel(model);

    progress.setProgress(100);

    return true;
}

bool GDocumentManagerView::removeAllItemDrawableOfListFromDocuments(QList<CT_AbstractItemDrawable *> &itemList, DM_AsynchroneProgress &progress)
{
    progress.setProgress(0);

    if(!itemList.isEmpty())
    {
        int i = 0;
        int n = itemList.size();

        QListIterator<CT_AbstractItemDrawable*> itItem(itemList);

        while(itItem.hasNext())
        {
            CT_AbstractItemDrawable *item = itItem.next();

            if(item->isDisplayed())
            {
                QList<DocumentInterface*> itemDocList;

                item->visitDocumentsWhereThisItemIs([&itemDocList](const IDocumentForModel* doc) -> bool {
                    itemDocList.append(static_cast<DocumentInterface*>(const_cast<IDocumentForModel*>(doc)));
                    return true;
                });

                QListIterator<DocumentInterface*> itDoc(itemDocList);

                while(itDoc.hasNext())
                    itDoc.next()->removeItemDrawable(*item);
            }

            ++i;
            progress.setProgress(((float)(i*100))/n);
        }
    }

    progress.setProgress(100);

    return true;
}

bool GDocumentManagerView::removeAllItemDrawableOfListFromDocument(QList<CT_AbstractItemDrawable *> &itemList, DM_DocumentView *doc, DM_AsynchroneProgress &progress)
{
    progress.setProgress(0);

    if(!itemList.isEmpty())
    {
        int i = 0;
        int n = itemList.size();

        QListIterator<CT_AbstractItemDrawable*> itItem(itemList);

        while(itItem.hasNext())
        {
            CT_AbstractItemDrawable *item = itItem.next();

            if(item->isDisplayed() && item->isInDocument(doc))
                doc->removeItemDrawable(*item);

            ++i;
            progress.setProgress(((float)(i*100))/n);
        }
    }

    progress.setProgress(100);

    return true;
}

DM_DocumentView* GDocumentManagerView::getActiveDocumentView()
{
    if(activeSubWindow() == nullptr)
    {
        QList<QMdiSubWindow *> list = subWindowList();

        if((m_lastDocumentActivated != nullptr)
                && list.contains(m_lastDocumentActivated))
        {
            setActiveSubWindow(m_lastDocumentActivated);
        }
        else if(!list.isEmpty())
        {
            m_lastDocumentActivated = list.first();
            setActiveSubWindow(m_lastDocumentActivated);
        }
    }

    if(activeSubWindow() != nullptr)
    {
        m_lastDocumentActivated = activeSubWindow();

        return ((MyQMdiSubWindow*)activeSubWindow())->getDocumentView();
    }
    else
    {
        m_lastDocumentActivated = nullptr;
    }

    return nullptr;
}

DM_DocumentView* GDocumentManagerView::getDocumentView(int index) const
{
    QList<QMdiSubWindow *> list = subWindowList();

    if((index >=0) && (index < list.size()))
        return ((MyQMdiSubWindow*)list.at(index))->getDocumentView();

    return nullptr;
}

int GDocumentManagerView::nbDocumentView() const
{
    return subWindowList().size();
}

bool GDocumentManagerView::containsDocument(DM_Document *document) const
{
    QList<QMdiSubWindow *> list = subWindowList();
    QListIterator<QMdiSubWindow *> it(list);

    while(it.hasNext())
    {
        if(((MyQMdiSubWindow*)it.next())->getDocumentView() == document)
            return true;
    }

    return false;
}

void GDocumentManagerView::redrawAllDocument()
{
    m_mutex->lock();

    QList<QMdiSubWindow*> list = subWindowList();
    QListIterator<QMdiSubWindow*> it(list);

    while(it.hasNext())
        ((MyQMdiSubWindow*)it.next())->getDocumentView()->redrawGraphics();

    m_mutex->unlock();
}

DocumentInterface *GDocumentManagerView::new3DDocument(bool fromGui, bool inLoadConfigurationFromMainWindow, float pointSize, bool orthographic, QColor *color)
{
    GDocumentViewForGraphics *doc = new GDocumentViewForGraphics(*this, tr("Document %1").arg(GDocumentView::NUMBER), "NORMAL");
    doc->init();

    GGraphicsViewImp *graphics = new GGraphicsViewImp(doc, doc->getSubWindow());
    doc->addGraphics(graphics);

    if(!fromGui) {
        DM_GraphicsViewOptions opt = doc->getOptions();
        opt.setPointSize(pointSize);

        if (color != nullptr)
            opt.setBackgroudColor(*color);

        if (orthographic)
            opt.setCameraType(CameraInterface::ORTHOGRAPHIC);
        else
            opt.setCameraType(CameraInterface::PERSPECTIVE);

        doc->setOptions(opt);
    }

    connect(doc, SIGNAL(syncEnabled(const GDocumentViewForGraphics*)), m_syncMan, SLOT(addAllGraphicsFromDocumentView(const GDocumentViewForGraphics*)));
    connect(doc, SIGNAL(syncDisabled(const GDocumentViewForGraphics*)), m_syncMan, SLOT(removeDocumentView(const GDocumentViewForGraphics*)), Qt::DirectConnection);

    addDocumentView(*doc, fromGui, inLoadConfigurationFromMainWindow);

    return doc;
}

DocumentInterface *GDocumentManagerView::new2DDocument(bool fromGui, bool inLoadConfigurationFromMainWindow)
{
    GDocumentViewForGraphics *doc = new GDocumentViewForGraphics(*this, tr("Document %1 (2D)").arg(GDocumentView::NUMBER), "2D");
    doc->init();
    GGraphicsViewImp *graphics = new GGraphicsViewImp(doc, doc->getSubWindow());
    graphics->active2DView(true);

    doc->addGraphics(graphics);

    connect(doc, SIGNAL(syncEnabled(const GDocumentViewForGraphics*)), m_syncMan, SLOT(addAllGraphicsFromDocumentView(const GDocumentViewForGraphics*)));
    connect(doc, SIGNAL(syncDisabled(const GDocumentViewForGraphics*)), m_syncMan, SLOT(removeDocumentView(const GDocumentViewForGraphics*)));

    addDocumentView(*doc, fromGui, inLoadConfigurationFromMainWindow);

    return doc;
}

DocumentInterface *GDocumentManagerView::newTreeViewDocument(bool fromGui, bool inLoadConfigurationFromMainWindow)
{
    GDocumentViewForItemModel *doc = new GDocumentViewForItemModel(*this, tr("Document %1 (ItemModel)").arg(GDocumentView::NUMBER));
    doc->init();
    GTreeView *treeView = new GTreeView(doc->getSubWindow());

    doc->addView(treeView);

    treeView->init();

    connect(treeView, SIGNAL(syncWith(const GItemModelView*)), m_syncMan, SLOT(syncItemModelWith(const GItemModelView*)));
    connect(treeView, SIGNAL(newGradientSelected(QLinearGradient)), this, SLOT(newGradientSelected(QLinearGradient)));

    addDocumentView(*doc, fromGui, inLoadConfigurationFromMainWindow);

    return doc;
}

DocumentInterface* GDocumentManagerView::new3DDocument(float pointSize, bool orthographic, QColor *color)
{
    return new3DDocument(false, false, pointSize, orthographic, color);
}

DocumentInterface* GDocumentManagerView::new2DDocument()
{
    return new2DDocument(false, false);
}

DocumentInterface* GDocumentManagerView::newTreeViewDocument()
{
    return newTreeViewDocument(false, false);
}

int GDocumentManagerView::nDocuments() const
{
    return nbDocumentView();
}

DocumentInterface* GDocumentManagerView::documentAt(const int &index) const
{
    return getDocumentView(index);
}

QList<DocumentInterface*> GDocumentManagerView::documents() const
{
    QList<QMdiSubWindow*> list = subWindowList();
    QList<DocumentInterface*> lRet;

    while(!list.isEmpty())
    {
        lRet.append(((MyQMdiSubWindow*)list.takeFirst())->getDocumentView());
    }

    return lRet;
}

DocumentInterface* GDocumentManagerView::activeDocument()
{
    return getActiveDocumentView();
}

void GDocumentManagerView::activateDocument(DocumentInterface *doc)
{
    QMdiSubWindow *subW = subWindowFromDocument(doc);

    if(subW != nullptr)
        setActiveSubWindow(subW);
}

bool GDocumentManagerView::closeDocument(DocumentInterface *doc)
{
    QMdiSubWindow *subW = subWindowFromDocument(doc);

    if(subW != nullptr)
        return subW->close();

    return true;
}

bool GDocumentManagerView::closeDocument(const int &index)
{
    return subWindowList().at(index)->close();
}

bool GDocumentManagerView::canClose(const DM_Document *document) const
{
    if(m_manualModeEnabled)
    {
        if(m_docAddedInNormalMode.contains((GDocumentView*)document))
            return (m_docAddedInNormalMode.size() > 1);

        if(m_docFromGuiAddedInManualMode.contains((GDocumentView*)document))
            return true;

        if(m_docToCloseAfterQuitManualMode.contains((GDocumentView*)document))
            return false;
    }

    return (nbDocumentView() > 1);
}

bool GDocumentManagerView::canAddItemDrawable(const DM_Document *document, const CT_AbstractItemDrawable *item) const
{
    Q_UNUSED(item)

    return ((DM_DocumentView*)document)->isVisible();
}

QColor GDocumentManagerView::intermediateColorFromSelectedGradient(double key)
{
    return m_colorLinearInterpolator.intermediateColor(key);
}

QMdiSubWindow* GDocumentManagerView::subWindowFromDocument(DocumentInterface *doc) const
{
    QList<QMdiSubWindow*> list = subWindowList();

    while(!list.isEmpty())
    {
        MyQMdiSubWindow *w = (MyQMdiSubWindow*)list.takeFirst();

        if(w->getDocumentView() == doc)
            return w;
    }

    return nullptr;
}

void GDocumentManagerView::stepRequiredManualMode(CT_VirtualAbstractStep *step)
{
    if((m_manualModeEnabledByStep != nullptr)
            && (m_manualModeEnabledByStep != step))
    {
        stepFinished(m_manualModeEnabledByStep);
    }

    if(m_manualModeEnabledByStep == nullptr)
    {
        m_manualModeEnabled = true;
        m_manualModeEnabledByStep = step;

        // hide all documents
        QListIterator<GDocumentView*> it(m_docAddedInNormalMode);

        while(it.hasNext())
        {
            GDocumentView *dView = it.next();
            dView->getSubWindow()->showNormal();
            dView->getSubWindow()->hide();

            emit documentHidden(dView);
        }
    }
}

void GDocumentManagerView::stepFinished(CT_VirtualAbstractStep *step)
{
    if((m_manualModeEnabledByStep != nullptr)
            && (m_manualModeEnabledByStep == step))
    {
        // close all documents added in manual mode
        while(!m_docToCloseAfterQuitManualMode.isEmpty())
            m_docToCloseAfterQuitManualMode.takeFirst()->getSubWindow()->close();

        m_docFromGuiAddedInManualMode.clear();

        // show all documents
        QListIterator<GDocumentView*> it(m_docAddedInNormalMode);

        while(it.hasNext())
        {
            GDocumentView *dView = it.next();
            dView->getSubWindow()->show();

            emit documentShowned(dView);
        }

        m_manualModeEnabledByStep = nullptr;
        m_manualModeEnabled = false;
    }
}

void GDocumentManagerView::slotDocumentDestroyed()
{
    m_docToCloseAfterQuitManualMode.removeOne((GDocumentView*)sender());
    m_docFromGuiAddedInManualMode.removeOne((GDocumentView*)sender());
    m_docAddedInNormalMode.removeOne((GDocumentView*)sender());
}

void GDocumentManagerView::subWindowHasBeenActivated(QMdiSubWindow *window)
{
    Q_UNUSED(window)

    emit documentActivated(getActiveDocumentView());
}

void GDocumentManagerView::verifyNumberWindow()
{
    if(m_windowCount != nbDocumentView())
    {
        m_windowCount = nbDocumentView();
        m_timer.stop();
        emit documentRemoved();
    }
    else
    {
        m_timer.start();
    }
}

void GDocumentManagerView::newGradientSelected(QLinearGradient gradient)
{
    m_colorLinearInterpolator.constructFromQGradient(gradient);
}
