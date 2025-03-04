#ifndef PLANE_H
#define PLANE_H

#include <Eigen/Dense>

/**
 * @brief Represent a plane
 */
template<typename Scalar>
class PlaneT
{
public:
    typedef Eigen::Matrix<Scalar, 3, 1> EigenVec3Type;
    typedef Eigen::Matrix<Scalar, 4, 1> EigenVec4Type;

    /**
     * @brief Construct a empty plane
     */
    PlaneT() {}

    /**
     * @brief Construct a plane by 4 points
     */
    PlaneT(const Eigen::Vector3d& v1,
          const Eigen::Vector3d& v2,
          const Eigen::Vector3d& v3,
          const Eigen::Vector3d& v4)
    {
        set(v1, v2, v3, v4);
    }

    /**
     * @brief Construct by equation
     */
    PlaneT(const Eigen::Vector4d &equation)
    {
        set(equation);
    }

    /**
     * @brief Modify the plane by 4 points
     */
    void set(const Eigen::Vector3d& v1,
             const Eigen::Vector3d& v2,
             const Eigen::Vector3d& v3,
             const Eigen::Vector3d& v4)
    {
        Eigen::Vector3d norm = (v2-v1).cross(v3-v2);
        const double length = norm.norm();

        if (length>1e-6)
            norm /= length;
        else
            norm.setZero();

        m_fv[0] = norm[0];
        m_fv[1] = norm[1];
        m_fv[2] = norm[2];
        m_fv[3] = -v1.dot(norm);

        m_vertex[0] = EigenVec3Type(v1.x(), v1.y(), v1.z());
        m_vertex[1] = EigenVec3Type(v2.x(), v2.y(), v2.z());
        m_vertex[2] = EigenVec3Type(v3.x(), v3.y(), v3.z());
        m_vertex[3] = EigenVec3Type(v4.x(), v4.y(), v4.z());
    }

    /**
     * @brief Modify the plane by 4 points
     */
    template<typename OtherScalar>
    void set(const Eigen::Matrix<OtherScalar, 3, 1> &v1,
             const Eigen::Matrix<OtherScalar, 3, 1> &v2,
             const Eigen::Matrix<OtherScalar, 3, 1> &v3,
             const Eigen::Matrix<OtherScalar, 3, 1> &v4)
    {
        set(Eigen::Vector3d(v1[0], v1[1], v1[2]),
            Eigen::Vector3d(v2[0], v2[1], v2[2]),
            Eigen::Vector3d(v3[0], v3[1], v3[2]),
            Eigen::Vector3d(v4[0], v4[1], v4[2]));

    }

    /**
     * @brief Modify the equation
     */
    template<typename OtherScalar>
    void set(const Eigen::Matrix<OtherScalar, 4, 1> &equation)
    {
        m_fv = equation.template cast<Scalar>();
    }

    /**
     * @brief Returns the distance between this plan and the point
     */
    double distance(const Eigen::Vector3d& point) const
    {
        return m_fv[0] * point[0] +
               m_fv[1] * point[1] +
               m_fv[2] * point[2] +
               m_fv[3];
    }

    /**
     * @brief Returns the distance between this plan and the point
     */
    double distance(const float* point) const
    {
        return m_fv[0] * point[0] +
               m_fv[1] * point[1] +
               m_fv[2] * point[2] +
               m_fv[3];
    }

    /**
     * @brief Returns the distance between this plan and the point
     */
    double distance(const double* point) const
    {
        return m_fv[0] * point[0] +
               m_fv[1] * point[1] +
               m_fv[2] * point[2] +
               m_fv[3];
    }

    /**
     * @brief Returns the distance between this plan and the point
     */
    double distance(const double &x, const double &y, const double &z) const
    {
        return m_fv[0] * x +
               m_fv[1] * y +
               m_fv[2] * z +
               m_fv[3];
    }

    /**
     * @brief Returns the plane transformed
     */
    PlaneT<Scalar> getTransformed(const Eigen::Matrix4d &matrix) const
    {
        Eigen::Matrix4d inverted = matrix.inverse();

        Eigen::Vector4d vertex[4];
        vertex[0] = inverted * Eigen::Vector4d(m_vertex[0][0], m_vertex[0][1], m_vertex[0][2], 1);
        vertex[1] = inverted * Eigen::Vector4d(m_vertex[1][0], m_vertex[1][1], m_vertex[1][2], 1);
        vertex[2] = inverted * Eigen::Vector4d(m_vertex[2][0], m_vertex[2][1], m_vertex[2][2], 1);
        vertex[3] = inverted * Eigen::Vector4d(m_vertex[3][0], m_vertex[3][1], m_vertex[3][2], 1);

        PlaneT<Scalar> p;
        p.set(EigenVec3Type(vertex[0][0], vertex[0][1], vertex[0][2]),
              EigenVec3Type(vertex[1][0], vertex[1][1], vertex[1][2]),
              EigenVec3Type(vertex[2][0], vertex[2][1], vertex[2][2]),
              EigenVec3Type(vertex[3][0], vertex[3][1], vertex[3][2]));

        return p;
    }

    /**
     * @brief Returns the equation of this plan
     */
    EigenVec4Type getEquation() const
    {
        return m_fv;
    }

    template<typename NewScalar>
    PlaneT<NewScalar> cast() const
    {
        PlaneT<NewScalar> thisCast;
        thisCast.m_vertex[0] = m_vertex[0].template cast<NewScalar>();
        thisCast.m_vertex[1] = m_vertex[1].template cast<NewScalar>();
        thisCast.m_vertex[2] = m_vertex[2].template cast<NewScalar>();
        thisCast.m_vertex[3] = m_vertex[3].template cast<NewScalar>();
        thisCast.set(m_fv);

        return thisCast;
    }

    EigenVec3Type m_vertex[4];

private:
    EigenVec4Type m_fv;
};

typedef PlaneT<double>  Plane;
typedef PlaneT<float>   PlaneF;

#endif // PLANE_H
