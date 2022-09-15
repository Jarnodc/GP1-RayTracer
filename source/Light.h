#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "ERGBColor.h"
#include "EMath.h"
#include "ray_HitRecord.h"

using namespace Elite;

//-----------------------------------------------------
// Light Class									
//-----------------------------------------------------
class Light
{
public:
	Light(const FVector3& position,const RGBColor& color, float intensity); // Constructor
	virtual ~Light() = default; // Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Light(const Light& other) = delete;
	Light(Light&& other) noexcept = delete;
	Light& operator=(const Light& other) = delete;
	Light& operator=(Light&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	virtual RGBColor CalcIrradiance(const HitRecord& hitRecord) const = 0;
	const FVector3 GetPosition() const;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------

	//-------------------------------------------------
	// Private Datamembers								
	//-------------------------------------------------
protected:
	//-------------------------------------------------
	// protected member functions								
	//-------------------------------------------------

	//-------------------------------------------------
	// protected Datamembers								
	//-------------------------------------------------
	const FVector3 m_Position;
	const RGBColor m_Color;
	const float m_Intensity;
};

