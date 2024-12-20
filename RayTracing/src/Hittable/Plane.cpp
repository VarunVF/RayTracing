#include "Plane.hpp"
#include "raytracing.hpp"


Plane::Plane(Point3 givenPoint, Vec3 normal)
	: givenPoint(givenPoint), normal(normal.unit_vector()),
	rangeX(Interval::universe), rangeY(Interval::universe), rangeZ(Interval::universe)
{
}

Plane::Plane(Point3 givenPoint, Vec3 normal, Interval rangeX, Interval rangeY, Interval rangeZ)
	: givenPoint(givenPoint), normal(normal.unit_vector()),
	rangeX(rangeX), rangeY(rangeY), rangeZ(rangeZ)
{
}

bool Plane::hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const
{
	// Check for ray parallel to plane
	constexpr auto epsilon = 1.0e-5;
	auto projection = dot(ray.direction(), normal);
	if (-epsilon < projection && projection < epsilon)  // close to zero
		return false;

	// Solve for intersection
	const auto root = dot(givenPoint - ray.origin(), normal) / dot(ray.direction(), normal);

	// Check parameter bounds
	if (!ray_t.surrounds(root))
		return false;

	// Set record details
	recordOut.t = root;
	recordOut.p = ray.at(recordOut.t);
	recordOut.setFaceNormal(ray, normal);

	// Check coordinate bounds
	const auto& intersection = recordOut.p;
	return rangeX.contains(intersection.x())
		&& rangeY.contains(intersection.y())
		&& rangeZ.contains(intersection.z());
}
