//---------------------------
// Includes
//---------------------------
#include "DirectionalLight.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
DirectionalLight::DirectionalLight(const FVector3& position, const RGBColor& color, float intensity)
	:Light(position, color, intensity)
{

}

//---------------------------
// Member functions
//---------------------------
RGBColor DirectionalLight::CalcIrradiance(const HitRecord& hitRecord) const
{
	return m_Color * m_Intensity;
}