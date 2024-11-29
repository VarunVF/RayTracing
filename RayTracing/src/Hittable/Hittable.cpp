#include "Hittable.hpp"


HitRecord::HitRecord()
	: p(), normal(), t(0.0), front_face(true)
{
}

void HitRecord::setFaceNormal(const Ray3& ray, const Vec3& outwardNormal)
// Sets the hit record normal vector. 
// NOTE: the parameter `outward_normal` is assumed to have unit length.
{
	front_face = dot(ray.direction(), outwardNormal) < 0;
	normal = front_face ? outwardNormal : -outwardNormal;
}