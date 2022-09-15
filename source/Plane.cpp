//---------------------------
// Includes
//---------------------------
#include "Plane.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Plane::Plane(const FPoint3& pos, const FVector3& normal, Material* baseMaterial) 
	:Object(pos, baseMaterial)
	,m_Normal{normal}
{

}

Plane::Plane()
	:Object()
	,m_Normal{0,0,0}
{

}

//---------------------------
// Member functions
//---------------------------
bool Plane::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	const float t{ Dot((m_Position - ray.m_Origin),m_Normal) / (Dot(ray.m_Direction,m_Normal)) };

	if (t >= ray.m_TMin && t <= ray.m_TMax)
	{
		hitrecord.hitPoint = ray.m_Origin + t * ray.m_Direction;
		hitrecord.normal = Elite::GetNormalized(m_Normal);
		hitrecord.material = m_Material;
		hitrecord.tValue = t;
		return true;
	}
	return false;
}

