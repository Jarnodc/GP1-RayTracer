//---------------------------
// Includes
//---------------------------
#include "Material_LambertPhong.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Material_LambertPhong::Material_LambertPhong(const RGBColor& baseColor,float specularReflectance, float diffuseReflectance, float exponent)
	: Material(baseColor, diffuseReflectance)
	, m_SpecularReflectance{specularReflectance}
	, m_Exponent{exponent}
{
}

//---------------------------
// Member functions
//---------------------------
RGBColor Material_LambertPhong::Shade(const HitRecord& hitRecord, const FVector3& viewDir, const FVector3& lightDir) const
{
	return BRDF::Lambert(m_Color, { m_DiffuseReflectance,m_DiffuseReflectance,m_DiffuseReflectance })
		+ BRDF::Phong(m_SpecularReflectance, m_Exponent, viewDir, lightDir, hitRecord.normal);
}
