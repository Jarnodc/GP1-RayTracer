//---------------------------
// Includes
//---------------------------
#include "PointLight.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
PointLight::PointLight(const FVector3& position, const RGBColor& color, float intensity)
	:Light(position, color, intensity)
{

}

//---------------------------
// Member functions
//---------------------------
RGBColor PointLight::CalcIrradiance(const HitRecord& hitRecord) const
{
	return m_Color * (m_Intensity / SqrDistance(hitRecord.hitPoint, FPoint3(m_Position)));
}