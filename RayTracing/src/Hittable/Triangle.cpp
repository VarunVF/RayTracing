#include "Triangle.hpp"


Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c,
	std::shared_ptr<Material> material)
	: a(a), b(b), c(c),
	AB(b - a), BC(c - b), CA(a - c),
	plane(c, cross(AB, BC), material),
	area(findArea(AB, BC)),
	m_Material(material)
{
}

bool Triangle::hit(const Ray3& ray, Interval ray_t, HitRecord& recordOut) const
{
	if (!plane.hit(ray, ray_t, recordOut))
		return false;

	// Calulate areas of sub triangles
	Vec3& OP = recordOut.p;
	double subarea1 = findArea(AB, OP - a);
	double subarea2 = findArea(BC, OP - b);
	double subarea3 = findArea(CA, OP - c);

	// Should sum to area of the whole triangle
	double difference = area - subarea1 - subarea2 - subarea3;
	constexpr auto epsilon = 1.0e-5;
	return std::abs(difference) < epsilon;
}
