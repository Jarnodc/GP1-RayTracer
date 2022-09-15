#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Material.h"

//-----------------------------------------------------
// Material_LambertPhong Class									
//-----------------------------------------------------
class Material_LambertPhong final : public Material
{
public:
    Material_LambertPhong( const RGBColor& baseColor,float specularReflectance, float diffuseReflectance, float exponent);  // Constructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	Material_LambertPhong(const Material_LambertPhong& other) = delete;
	Material_LambertPhong(Material_LambertPhong&& other) noexcept = delete;
	Material_LambertPhong& operator=(const Material_LambertPhong& other) = delete;
	Material_LambertPhong& operator=(Material_LambertPhong&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
    RGBColor Shade(const HitRecord& hitRecord, const FVector3& viewDir, const FVector3& lightDir)const override;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
    const float m_Exponent;
    const float m_SpecularReflectance;
};

