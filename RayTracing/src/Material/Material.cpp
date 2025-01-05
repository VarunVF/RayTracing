#include "Material.hpp"


Color3 Material::emitted(const Ray3& ray, uint32_t& seed) const
{
	return Color3(0.0, 0.0, 0.0);
}

bool Material::scatter(
	const Ray3& ray, const HitRecord& record,
	Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
	return false;
}
