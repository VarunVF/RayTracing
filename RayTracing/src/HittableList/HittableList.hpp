#pragma once

#include <memory>
#include <vector>

#include "Hittable/Hittable.hpp"


// A collection of Hittable objects
class HittableList
{
public:
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);

	void add(std::shared_ptr<Hittable> object);
	void clear();
	bool hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};
