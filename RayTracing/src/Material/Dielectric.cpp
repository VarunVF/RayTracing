#include "Dielectric.hpp"
#include "raytracing.hpp"


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
	// At most 1.0, ensure sqrt of positive number
	double cosTheta = std::fmin(dot(-unitDirection, record.normal), 1.0);
	double sinTheta = std::sqrt(1 - cosTheta * cosTheta);

	bool cannotRefract = index * sinTheta > 1.0;
	Vec3 direction;

	if (cannotRefract || reflectance(cosTheta, index) > random_double(seed))
		direction = reflect(unitDirection, record.normal);
	else
		direction = refract(unitDirection, record.normal, index);

	scatteredOut = Ray3(record.p, direction);
	return true;
}

double Dielectric::reflectance(double cosine, double refractiveIndex)
{
	double r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
	r0 *= r0;
	double x = 1 - cosine;
	return r0 + (1 - r0) * (x * x * x * x * x);
}
