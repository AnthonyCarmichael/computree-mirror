#ifndef DM_ABSTRACTATTRIBUTES_H
#define DM_ABSTRACTATTRIBUTES_H

#include <QString>
#include "tools/worker/dm_abstractworker.h"

class GDocumentViewForGraphics;
class CT_AbstractAttributes;
class CT_OutAbstractModel;

class DM_AbstractAttributes : public DM_AbstractWorker
{
    Q_OBJECT
public:
    /**
     * @brief Create new instance
     * @param local : Set to true if this attribute must be applied to only
     *        local points/faces/edges or false to use the complete cloud of attributes
     */
    DM_AbstractAttributes(bool local);
    virtual ~DM_AbstractAttributes();

    /**
     * @brief Set the model that correspond to this attribute
     */
    void setModel(const CT_OutAbstractModel* model);

    /**
     * @brief Returns the model that correspond to this attribute
     */
    const CT_OutAbstractModel* model() const;

    /**
     * @brief Set a displayable name
     */
    void setDisplayableName(const QString &name);

    /**
     * @brief Get the displayable name
     */
    QString displayableName() const;

    /**
     * @brief Get the Attributes
     */
    CT_AbstractAttributes* abstractAttributes() const;

    /**
     * @brief Set if he must be displayed alone
     */
    void setDisplayAlone(bool val);

    /**
     * @brief Must be displayed alone ?
     */
    bool isDisplayedAlone() const;

    /**
     * @brief Returns true if this attribute must be applied to only
     *        local points/faces/edges or false to use the complete cloud of attributes
     */
    bool mustApplyToLocalIndex() const;

    /**
     * @brief Set the document where apply the attributes
     */
    void setDocument(const GDocumentViewForGraphics *doc);

    /**
     * @brief Set the document where the attributes must be applied
     */
    GDocumentViewForGraphics* document() const;

    /**
     * @brief Check if the doc has the necessary cloud or set it if not
     */
    virtual void checkAndSetNecessaryCloudToDoc() = 0;

public slots:

    /**
     * @brief Apply the attributes to the document.
     */
    void apply();

private:
    QString                     m_name;
    bool                        m_displayAlone;
    GDocumentViewForGraphics    *m_doc;
    CT_AbstractAttributes       *m_attributes;
    const CT_OutAbstractModel*  mModel;
    const bool                  mLocalOnly;

protected:

    virtual bool process(GDocumentViewForGraphics *doc) = 0;
    void setAttributes(const CT_AbstractAttributes *att);
    virtual void attributesDeleted() = 0;

private slots:
    void slotAttributesDeleted();
};

#endif // DM_ABSTRACTATTRIBUTES_H
