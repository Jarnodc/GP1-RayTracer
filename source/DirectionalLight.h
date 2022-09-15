#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Light.h"
#include "ERGBColor.h"

//-----------------------------------------------------
// DirectionalLight Class									
//-----------------------------------------------------
class DirectionalLight final : public Light
{
public:
	DirectionalLight(const FVector3& position, const RGBColor& color, float intensity);// Constructor
	virtual ~DirectionalLight() override = default;			// destructor
	// //-----------------------------------------------------
	// Copy/move constructors and assignment operators
	// //-----------------------------------------------------    
	DirectionalLight(const DirectionalLight& other) = delete;
	DirectionalLight(DirectionalLight&& other) noexcept = delete;
	DirectionalLight& operator=(const DirectionalLight& other) = delete;
	DirectionalLight& operator=(DirectionalLight&& other) noexcept = delete;

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

