#ifndef GITEMMODELVIEW_H
#define GITEMMODELVIEW_H

#include "dm_itemmodelviewsynchronizedgroup.h"
#include "view/DocumentView/gdocumentview.h"
#include "treeviewinterface.h"

class CT_AbstractActionForTreeView;

class GItemModelView : public TreeViewInterface
{
public:
    GItemModelView();
    ~GItemModelView();

    void setDocument(const GDocumentView *doc);

    virtual void init() = 0;

    virtual void beginAddMultipleItemDrawable() {}
    virtual void endAddMultipleItemDrawable() {}

    virtual void beginRemoveMultipleItemDrawable() {}
    virtual void endRemoveMultipleItemDrawable() {}

    void setCurrentAction(CT_AbstractActionForTreeView *action);
    void setDefaultAction(CT_AbstractActionForTreeView *action);

    void setSyncGroup(const DM_ItemModelViewSynchronizedGroup *group);
    DM_ItemModelViewSynchronizedGroup* syncGroup() const;

    virtual DM_ActionsHandler* actionsHandler() const = 0;

    virtual QWidget* getViewWidget() const = 0;

    GDocumentView* documentView() const;

    /**
     * @brief Returns the document that contains this graphics view
     */
    DocumentInterface* document() const;

private:
    GDocumentView                           *m_doc;
    DM_ItemModelViewSynchronizedGroup       *m_syncGroup;
};

#endif // GITEMMODELVIEW_H
