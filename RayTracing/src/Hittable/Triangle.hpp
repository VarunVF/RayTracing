#pragma once

#include "Hittable.hpp"
#include "Plane.hpp"


class Triangle : public Hittable
{
public:
	Triangle(Point3 a, Point3 b, Point3 c);
	virtual ~Triangle() = default;

	bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const override;
	
	// Area of a triangle with the two given sides as vectors
	static inline double findArea(const Vec3& x, const Vec3& y)
	{
		// 0.5 * xy * sin(Z)
		return 0.5 * cross(x, y).length();
	}


public:
	Point3 a, b, c;
	Vec3 AB, BC, CA;
	Plane plane;
	double area;
};