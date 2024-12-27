#include "Sphere.hpp"
#include "../Interval/Interval.hpp"


Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> material)
	: m_Center(center), m_Radius(std::fmax(0.0, radius)), m_Material(material)
{
}

bool Sphere::hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const
{
	auto& dir = ray.direction();
	auto oc = m_Center - ray.origin();

	// Solve quadratic equation ax^2 + bx + c = 0
	double a = dot(dir, dir);
	double h = dot(dir, oc);							// h = b / -2
	double c = dot(oc, oc) - m_Radius * m_Radius;

	double discriminant = h*h - a*c;
	if (discriminant < 0)
		// No intersection
		return false;

	auto sqrt_d = std::sqrt(discriminant);

	// Find the nearest root that lies in [ray_tmin, ray_tmax]
	auto root = (h - sqrt_d) / a;
	if (!ray_t.surrounds(root))			// out of bounds, try again
	{
		root = (h + sqrt_d) / a;
		if (!ray_t.surrounds(root))		// still out of bounds
			return false;
	}

	recordOut.t = root;
	recordOut.p = ray.at(recordOut.t);
	Vec3 outwardNormal = (recordOut.p - m_Center) / m_Radius;
	recordOut.setFaceNormal(ray, outwardNormal);
	recordOut.material = m_Material;

	return true;
}
