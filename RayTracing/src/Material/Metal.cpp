#include "Metal.hpp"
#include "Interval/Interval.hpp"


Metal::Metal(const Color3& albedo)
	: m_Albedo(albedo), m_Fuzz(0.0)
{
}

Metal::Metal(const Color3& albedo, double fuzz)
	: m_Albedo(albedo), m_Fuzz(fuzz)
{
	m_Fuzz = Interval(0.0, 1.0).clamp(fuzz);
}

bool Metal::scatter(
	const Ray3& ray, const HitRecord& record,
	Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
	Vec3 reflected = reflect(ray.direction(), record.normal);

	// Normalise the reflected vector for consistent scaling with random_unit_vector
	reflected = reflected.unit_vector() + m_Fuzz * random_unit_vector(seed);
	scatteredOut = Ray3(record.p, reflected);
	attenuationOut = m_Albedo;

	// If the ray reflects back into the object, return false
	return dot(reflected, record.normal) > 0;
}
