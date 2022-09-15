#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EMath.h"
#include "ERGBColor.h"

using namespace Elite;

//-----------------------------------------------------
// BRDF Class									
//-----------------------------------------------------
class BRDF final
{
public:
	BRDF() = default;	// Constructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	BRDF(const BRDF& other) = delete;
	BRDF(BRDF&& other) noexcept = delete;
	BRDF& operator=(const BRDF& other) = delete;
	BRDF& operator=(BRDF&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	
	//-------------------------------------------------
	// Static Member functions						
	//-------------------------------------------------
	static RGBColor Lambert(const RGBColor& baseColor, const RGBColor& reflectance);
	static RGBColor Phong(float specularReflectance, float phongExponent, const FVector3& incomingVector, const FVector3& outGoingVector,const FVector3& normal);
};

