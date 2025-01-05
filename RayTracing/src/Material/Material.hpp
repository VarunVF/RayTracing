#pragma once

#include "Hittable/Hittable.hpp"
#include "Color3/Color3.hpp"


class Material
{
public:
	virtual ~Material() = default;
	
	virtual Color3 emitted(const Ray3& ray, uint32_t& seed) const;
	virtual bool scatter(
		const Ray3& ray, const HitRecord& record,
		Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const;
};
