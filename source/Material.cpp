//---------------------------
// Includes
//---------------------------
#include "Material.h"
#include "LightManager.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Material::Material()
	:m_Color{RGBColor(1,1,1)}
	,m_DiffuseReflectance{1}
{
}

Material::Material(const RGBColor& baseColor, float diffuseReflectance)
	:m_Color{ baseColor }
	,m_DiffuseReflectance{diffuseReflectance}
{
	 
}
// -------------------------------------------------
// Copy/move constructors and assignment operators
// -------------------------------------------------
Material& Material::operator=(const Material& mat)
{
	m_Color = mat.m_Color;
	m_DiffuseReflectance = mat.m_DiffuseReflectance;
	return *this;
}

Material& Material::operator=(Material&& mat) noexcept
{
	m_Color = mat.m_Color;
	m_DiffuseReflectance = mat.m_DiffuseReflectance;
	return *this;

}

//---------------------------
// Member functions
//---------------------------
RGBColor Material::Shade(const HitRecord& hitRecord, const FVector3& viewDir, const FVector3& lightDir) const
{
	return BRDF::Lambert(m_Color, { m_DiffuseReflectance,m_DiffuseReflectance,m_DiffuseReflectance });
}

void Material::SetColor(const RGBColor& color)
{
	m_Color = color;
}

const RGBColor& Material::GetColor() const
{
	return m_Color;
}

