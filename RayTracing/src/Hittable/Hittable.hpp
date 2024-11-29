#pragma once

#include "../Ray3/Ray3.hpp"
#include "../Interval/Interval.hpp"


class HitRecord
{
public:
	// Sets the hit record normal vector. 
	// NOTE: the parameter `outward_normal` is assumed to have unit length.
	HitRecord();
	void setFaceNormal(const Ray3& ray, const Vec3& outwardNormal);

public:
	Point3 p;
	Vec3 normal;
	double t;
	bool front_face;
};


class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const = 0;
};
