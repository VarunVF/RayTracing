#pragma once

#include "Material/Material.hpp"


class Metal : public Material
{
public:
	// Fuzz factor will be set to 0.0 by default
	Metal(const Color3& albedo);

	// Fuzz factor will be clamped to the range [0.0, 1.0]
	Metal(const Color3& albedo, double fuzz);

	bool scatter(
		const Ray3& ray, const HitRecord& record,
		Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const override;
	
private:
	Color3 m_Albedo;
	double m_Fuzz;
};
