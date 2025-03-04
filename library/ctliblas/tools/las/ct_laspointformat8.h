#ifndef CT_LASPOINTFORMAT8_H
#define CT_LASPOINTFORMAT8_H

#include "ctliblas/tools/las/ct_laspointformat7.h"
#include "ctliblas/tools/las/ct_lasnirpacket.h"

class CTLIBLAS_EXPORT CT_LASPointFormat8 : public CT_LASPointFormat7, public CT_LASNirPacket
{
public:
    CT_LASPointFormat8();

    /**
     * @brief Return the size of the points in byte
     */
    size_t sizeInBytes() const override;

    /**
     * @brief Write the point 'globalIndex' (index in the global pointCloud)
     */
    void write(QDataStream &stream, CT_LASHeader* header, const CT_Point &p, const size_t &globalIndex) const override;

protected:
    /**
     * @brief Derivated class must return attribute types that they need to write a point
     */
    virtual QList<CT_LasDefine::LASPointAttributesType> typesToSearch() override;

    /**
     * @brief Write only the information of the point format 8
     */
    void writeInfoFormat8(QDataStream &stream, const size_t& globalIndex) const;
};

#endif // CT_LASPOINTFORMAT8_H
