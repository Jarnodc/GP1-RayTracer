#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EMath.h"
class Material;

using namespace Elite;

//-----------------------------------------------------
// Ray struct									
//-----------------------------------------------------
struct Ray
{
	// Constructor
	Ray(const FPoint3& origin, const FVector3& direction)
		:m_Origin{ origin }
		,m_Direction{ direction }
	{

	}

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	const FPoint3 m_Origin = {};
	const FVector3 m_Direction = {};
	const float m_TMin = 0.0001f;
	const float m_TMax = FLT_MAX;
};

//-----------------------------------------------------
// HitRecord struct									
//-----------------------------------------------------
struct HitRecord
{
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	FPoint3 hitPoint{};
	FVector3 normal{};
	Material* material{};
	float tValue{};
};