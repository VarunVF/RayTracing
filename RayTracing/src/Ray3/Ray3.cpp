#include "Ray3.hpp"


Ray3::Ray3()
    : m_Origin(), m_Direction()
{
}

Ray3::Ray3(Point3 origin, Vec3 direction)
    : m_Origin(origin), m_Direction(direction)
{
}

Point3 Ray3::at(double t) const
{
    return m_Origin + (t * m_Direction);
}

const Point3& Ray3::origin() const
{
    return m_Origin;
}

const Vec3& Ray3::direction() const
{
    return m_Direction;
}
