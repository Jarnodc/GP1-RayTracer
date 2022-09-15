//---------------------------
// Includes
//---------------------------
#include "BRDF.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------

//---------------------------
// Member functions
//---------------------------
RGBColor BRDF::Lambert(const RGBColor& baseColor, const RGBColor& reflectance)
{
	return baseColor * reflectance / static_cast<float>(E_PI);
}
RGBColor BRDF::Phong(float specularReflectance, float phongExponent, const FVector3& incomingVector, const FVector3& outGoingVector, const FVector3& normal)
{

	Elite::FVector3 reflect = incomingVector - 2 * Elite::Dot(normal, incomingVector) * normal;
	float a = Elite::Dot(reflect, outGoingVector);

	float phongSpecReflect = specularReflectance * (powf(a, phongExponent));
	Elite::RGBColor phongSpecReflect_color{ phongSpecReflect, phongSpecReflect, phongSpecReflect };

	return phongSpecReflect_color;
}
