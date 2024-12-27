#pragma once

#include <memory>

#include "Hittable.hpp"
#include "../Vec3/Vec3.hpp"
#include "../Interval/Interval.hpp"


class Sphere : public Hittable
{
public:
	Sphere(const Point3& center, double radius, std::shared_ptr<Material> material);

	bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const override;

private:
	Point3 m_Center;
	double m_Radius;
	std::shared_ptr<Material> m_Material;
};