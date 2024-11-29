#pragma once

#include "../Vec3/Vec3.hpp"


// Implements the vector equation of a line in 3D
class Ray3
{
public:
	Ray3();
	Ray3(Point3 origin, Vec3 direction);

	Point3 at(double t) const;
	const Point3& origin() const;
	const Vec3& direction() const;
private:
	Point3 m_Origin;
	Vec3 m_Direction;
};
