#pragma once

#include <memory>

#include "../Ray3/Ray3.hpp"
#include "../Interval/Interval.hpp"


class Material;


class HitRecord
{
public:
	HitRecord();

	// Sets the hit record normal vector. 
	// NOTE: the parameter `outward_normal` is assumed to have unit length.
	void setFaceNormal(const Ray3& ray, const Vec3& outwardNormal);

public:
	Point3 p;
	Vec3 normal;
	std::shared_ptr<Material> material;
	double t;
	bool front_face;
};


class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const = 0;
};
