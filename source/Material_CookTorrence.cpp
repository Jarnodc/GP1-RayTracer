//---------------------------
// Includes
//---------------------------
#include "Material_CookTorrence.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Material_CookTorrence::Material_CookTorrence(const RGBColor& baseColor, float diffuseReflectance, bool metalness, float rougnessSquared)
	: Material(baseColor, diffuseReflectance)
	, m_Metalness{metalness}
	, m_RoughnessSquared{rougnessSquared}
{
}

//---------------------------
// Member functions
//---------------------------
RGBColor Material_CookTorrence::Shade(const HitRecord& hitRecord, const FVector3& viewDir, const FVector3& lightDir) const
{
	const FVector3 halfVector = (viewDir + lightDir) / Magnitude((viewDir + lightDir));

	const RGBColor F{ CalculateFresnel(halfVector, viewDir) };
	const RGBColor D{ CalculateNormalDistribution(hitRecord,halfVector) };
	const RGBColor G{ CalculateGeometry(hitRecord,halfVector,viewDir,lightDir) };

	const RGBColor CookTorrence = (D*F*G) / (4 * Dot(viewDir, hitRecord.normal) * Dot(lightDir, hitRecord.normal));

	const RGBColor kd = m_Metalness ? RGBColor(0,0,0) : (RGBColor(1, 1, 1) - F);

	return !m_Metalness ? kd * BRDF::Lambert(m_Color, RGBColor(1,1,1)) * m_DiffuseReflectance + CookTorrence : CookTorrence;
}

RGBColor Material_CookTorrence::CalculateFresnel(const FVector3& halfVector, const FVector3& viewDir) const
{
	const float hvDot{ Dot(halfVector,viewDir) };
	const RGBColor F0 = m_Metalness ? m_Color : RGBColor(0.04f, 0.04f, 0.04f);
	const RGBColor Fresnel{ F0 + (RGBColor(1, 1, 1) - F0) * powf(1 - hvDot, 5) };
	return Fresnel;
}

RGBColor Material_CookTorrence::CalculateNormalDistribution(const HitRecord& hitRecord, const FVector3& halfVector) const
{
	const float squaredAlpha = powf(m_RoughnessSquared, 2);
	const float nhSquared = powf(Dot(hitRecord.normal, halfVector), 2);
	const float bottomPart = nhSquared * (squaredAlpha - 1) + 1;
	const float D = squaredAlpha / (static_cast<float>(E_PI) * (powf(bottomPart, 2)));
	return { D,D,D };
}

RGBColor Material_CookTorrence::CalculateGeometry(const HitRecord& hitRecord, const FVector3& halfVector, const FVector3& viewDir, const FVector3& lightDir) const
{
	const float k{ powf(m_RoughnessSquared + 1,2) / 8 };
	const float nvDot{ Dot(hitRecord.normal,viewDir) };
	const float nlDot{ Dot(hitRecord.normal,lightDir) };
	const float vBottom{ nvDot * (1 - k) + k };
	const float lBottom{ nlDot * (1 - k) + k };
	float temp{ nvDot * nlDot };
	if (temp < 0)
		temp *= -1;
	const float smith = temp / (vBottom * lBottom);
	return { smith,smith,smith };
}
