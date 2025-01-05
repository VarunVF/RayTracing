#include "DiffuseLight.hpp"


DiffuseLight::DiffuseLight(const Color3& light)
    : m_Light(light)
{
}

Color3 DiffuseLight::emitted(const Ray3& ray, uint32_t& seed) const
{
    return m_Light;
}

bool DiffuseLight::scatter(
    const Ray3& ray, const HitRecord& record,
    Color3& attenuationOut, Ray3& scatteredOut, uint32_t& seed) const
{
    return false;
}
