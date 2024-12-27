#include "Material.hpp"


bool Material::scatter(const Ray3& ray, const HitRecord& record,
	Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
	return false;
}
