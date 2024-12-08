#pragma once

#include "Hittable.hpp"
#include "../Vec3/Vec3.hpp"
#include "../Interval/Interval.hpp"


class Plane : public Hittable
{
public:
	Plane(Point3 givenPoint, Vec3 direction);
	Plane(Point3 givenPoint, Vec3 direction, Interval rangeX, Interval rangeY, Interval rangeZ);

	bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const override;

public:
	Point3 givenPoint;
	Vec3 normal;
	Interval rangeX, rangeY, rangeZ;
};