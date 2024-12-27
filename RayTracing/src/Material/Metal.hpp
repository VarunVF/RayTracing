#pragma once

#include "Material/Material.hpp"


class Metal : public Material
{
public:
	Metal(const Color3& albedo);

	bool scatter(
		const Ray3& ray, const HitRecord& record,
		Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const override;
	
private:
	Color3 m_Albedo;
};
