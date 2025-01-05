#pragma once

#include "Material.hpp"
#include "Color3/Color3.hpp"


class DiffuseLight : public Material
{
public:
	DiffuseLight(const Color3& light);

	Color3 emitted(const Ray3& ray, uint32_t& seed) const override;
	bool scatter(
		const Ray3& ray, const HitRecord& record,
		Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const override;

private:
	Color3 m_Light;
};
