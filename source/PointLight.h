#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Light.h"

//-----------------------------------------------------
// PointLight Class									
//-----------------------------------------------------
class PointLight final : public Light
{
public:
	PointLight(const FVector3& position, const RGBColor& color, float intensity);	// Constructor
	virtual ~PointLight() override = default;			// destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	PointLight(const PointLight& other) = delete;
	PointLight(PointLight&& other) noexcept = delete;
	PointLight& operator=(const PointLight& other) = delete;
	PointLight& operator=(PointLight&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	RGBColor CalcIrradiance(const HitRecord& hitRecord) const override;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
};

