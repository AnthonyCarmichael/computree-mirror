#include "dm_itemmodelviewsynchronizedgroup.h"

#include "ct_itemdrawable/abstract/ct_abstractitemdrawable.h"

DM_ItemModelViewSynchronizedGroup::DM_ItemModelViewSynchronizedGroup() : DM_AbstractViewSynchronizedGroup()
{
    _imv = nullptr;
}

void DM_ItemModelViewSynchronizedGroup::setOptions(const DM_ItemModelViewSynchronizedGroupOptions &newOptions)
{
    _options = newOptions;
}

void DM_ItemModelViewSynchronizedGroup::setItemModelView(const DM_DocumentView *imv)
{
    _imv = (DM_DocumentView*)imv;
}

void DM_ItemModelViewSynchronizedGroup::addDocumentView(const DM_DocumentView *dv)
{
    if(containsDocumentView(dv))
        return;

    _dvList.append((DM_DocumentView*)dv);

    connect(dv, SIGNAL(itemDrawableToBeRemoved(CT_AbstractItemDrawable&)), this, SLOT(slotItemDrawableToBeRemoved(CT_AbstractItemDrawable&)), Qt::DirectConnection);
    connect(dv, SIGNAL(itemDrawableSelectionChanged(CT_AbstractItemDrawable*,bool)), this, SLOT(slotItemDrawableSelectionChanged(CT_AbstractItemDrawable*,bool)), Qt::DirectConnection);
}

void DM_ItemModelViewSynchronizedGroup::removeDocumentView(const DM_DocumentView *dv)
{
    disconnect(dv, nullptr, this, nullptr);

    _dvList.removeOne((DM_DocumentView*)dv);
}

const DM_DocumentView* DM_ItemModelViewSynchronizedGroup::itemModelView() const
{
    return _imv;
}

bool DM_ItemModelViewSynchronizedGroup::containsDocumentView(const DM_DocumentView *dv) const
{
    return _dvList.contains((DM_DocumentView*)dv);
}

const QList<DM_DocumentView*>& DM_ItemModelViewSynchronizedGroup::documentViews() const
{
    return _dvList;
}

// PRIVATE //

void DM_ItemModelViewSynchronizedGroup::slotItemDrawableSelectionChanged(CT_AbstractItemDrawable *item, bool selected)
{
    if(_imv != nullptr)
    {
        if(selected)
            _imv->addItemDrawable(*item);
        else
            _imv->removeItemDrawable(*item);
    }
}

void DM_ItemModelViewSynchronizedGroup::slotItemDrawableToBeRemoved(CT_AbstractItemDrawable &item)
{
    if(_imv != nullptr
            && item.isSelected())
    {
        QList<DocumentInterface*> ll;

        DocumentInterface* currentDoc = static_cast<DocumentInterface*>(sender());
        DM_DocumentView*& imv = _imv;

        item.visitDocumentsWhereThisItemIs([&ll, &imv, &currentDoc](const IDocumentForModel* doc) -> bool {
            if((doc != imv) && (doc != currentDoc))
                ll.append(static_cast<DocumentInterface*>(const_cast<IDocumentForModel*>(doc)));

            return true;
        });

        if(ll.isEmpty())
            _imv->removeItemDrawable(item);
    }
}
