#include "Lambertian.hpp"

Lambertian::Lambertian(const Color3& albedo)
	: m_Albedo(albedo)
{
}

bool Lambertian::scatter(
	const Ray3& ray, const HitRecord& record,
	Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
	auto scatterDirection = record.normal + random_unit_vector(seed);

	if (scatterDirection.near_zero())
		scatterDirection = record.normal;

	scatteredOut = Ray3(record.p, scatterDirection);
	attenuationOut = m_Albedo;
	
	return true;
}
