#pragma once

#include "Material.hpp"


class Lambertian : public Material
{
public:
	Lambertian(const Color3& albedo);

	bool scatter(
		const Ray3& ray, const HitRecord& record,
		Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const override;

private:
	// Albedo: fractional reflectance
	Color3 m_Albedo;
};
