#include "Metal.hpp"


Metal::Metal(const Color3& albedo)
	: m_Albedo(albedo)
{
}

bool Metal::scatter(const Ray3& ray, const HitRecord& record,
	Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
	Vec3 reflected = reflect(ray.direction(), record.normal);
	scatteredOut = Ray3(record.p, reflected);
	attenuationOut = m_Albedo;
	return true;
}
