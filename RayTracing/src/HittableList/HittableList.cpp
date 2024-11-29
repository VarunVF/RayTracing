#include "HittableList.hpp"


HittableList::HittableList()
	: objects()
{
}

HittableList::HittableList(std::shared_ptr<Hittable> object)
	: objects()
{
	add(object);
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

void HittableList::clear()
{
	objects.clear();
}

bool HittableList::hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	auto closestSoFar = ray_t.max;

	for (const auto object : objects)
		if (object->hit(ray, Interval(ray_t.min, closestSoFar), tempRecord))
		{
			hitAnything = true;
			closestSoFar = tempRecord.t;
			recordOut = tempRecord;
		}

	return hitAnything;
}
