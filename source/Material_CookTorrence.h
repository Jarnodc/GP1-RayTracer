#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Material.h"

//-----------------------------------------------------
// Material_CookTorrence Class									
//-----------------------------------------------------
class Material_CookTorrence final : public Material
{
public:
	Material_CookTorrence(const RGBColor& baseColor, float diffuseReflectance, bool metalness, float rougnessSquared);	// Constructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	Material_CookTorrence(const Material_CookTorrence& other) = delete;
	Material_CookTorrence(Material_CookTorrence&& other) noexcept = delete;
	Material_CookTorrence& operator=(const Material_CookTorrence& other) = delete;
	Material_CookTorrence& operator=(Material_CookTorrence&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	RGBColor Shade(const HitRecord& hitRecord, const FVector3& viewDir, const FVector3& lightDir)const override;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	RGBColor CalculateFresnel(const FVector3& halfVector, const FVector3& viewDir)const;
	RGBColor CalculateNormalDistribution(const HitRecord& hitRecord,const FVector3& halfVector)const;
	RGBColor CalculateGeometry(const HitRecord& hitRecord, const FVector3& halfVector, const FVector3& viewDir, const FVector3& lightDir)const;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	const bool m_Metalness;
	const float m_RoughnessSquared;
};

