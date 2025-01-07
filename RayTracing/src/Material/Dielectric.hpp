#pragma once

#include "Material.hpp"


class Dielectric : public Material
{
public:
	Dielectric(double refractiveIndex);
	Dielectric(double refractiveIndex, const Color3& albedo);

	bool scatter(
		const Ray3& ray, const HitRecord& record,
		Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const override;

private:
	// Schlick's approximation for reflectance
	static double reflectance(double cosine, double refractiveIndex);

private:
	double m_RefractiveIndex;
	Color3 m_Albedo;
};
