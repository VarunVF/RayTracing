#include "Dielectric.hpp"


Dielectric::Dielectric(double refractiveIndex)
	: m_RefractiveIndex(refractiveIndex), m_Albedo(1.0, 1.0, 1.0)
{
}

Dielectric::Dielectric(double refractiveIndex, const Color3& albedo)
	: m_RefractiveIndex(refractiveIndex), m_Albedo(albedo)
{
}

bool Dielectric::scatter(
	const Ray3& ray, const HitRecord& record,
	Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
	attenuationOut = m_Albedo;
	double index = record.front_face ? (1.0 / m_RefractiveIndex) : m_RefractiveIndex;

	Vec3 unitDirection = ray.direction().unit_vector();
	Vec3 refractDirection = refract(unitDirection, record.normal, index);

	scatteredOut = Ray3(record.p, refractDirection);
	return true;
}
