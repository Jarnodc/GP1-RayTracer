#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EMath.h"
#include "ERGBColor.h"
#include "BRDF.h"
#include "ray_HitRecord.h"

using namespace Elite;

//-----------------------------------------------------
// Material Class									
//-----------------------------------------------------
class Material
{
public:
	Material();		// Constructor
	Material(const RGBColor& baseColor, float diffuseReflectance);	// Constructor
	virtual ~Material() = default;				// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------   
	Material(const Material& other) = delete;
	Material(Material&& other) noexcept = delete;
	Material& operator=(const Material& other);
	Material& operator=(Material&& other) noexcept;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	virtual RGBColor Shade(const HitRecord& hitRecord, const FVector3& viewDir, const FVector3& lightDir)const;

	void SetColor(const RGBColor& color);

	const RGBColor& GetColor() const;

private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------

	//-------------------------------------------------
	// Private Datamembers								
	//-------------------------------------------------

protected:
	//-------------------------------------------------
	// Protected member functions								
	//-------------------------------------------------

	//-------------------------------------------------
	// Protected Datamembers								
	//-------------------------------------------------
	RGBColor m_Color;
	float m_DiffuseReflectance;
};

