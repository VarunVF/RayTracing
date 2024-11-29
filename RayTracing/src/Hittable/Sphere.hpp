#pragma once

#include "Hittable.hpp"
#include "../Vec3/Vec3.hpp"
#include "../Interval/Interval.hpp"


class Sphere : public Hittable
{
public:
	Sphere(const Point3& center, double radius);

	bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const override;

private:
	Point3 m_Center;
	double m_Radius;
};