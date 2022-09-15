//---------------------------
// Includes
//---------------------------
#include "Sphere.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Sphere::Sphere(const FPoint3& centerPos, const float& radius, Material* baseMaterial)
	:Object(centerPos, baseMaterial)
	,m_Radius{ radius }
{

}

Sphere::Sphere()
	:Object()
	,m_Radius{ 1.f }
{

}

//---------------------------
// Member functions
//---------------------------
bool Sphere::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	const float a{ Dot(ray.m_Direction,ray.m_Direction) };
	const float b{ Dot(2* ray.m_Direction, ray.m_Origin-m_Position) };
	const float c{ Dot(ray.m_Origin - m_Position, ray.m_Origin - m_Position) - Square(m_Radius)};

	const float discriminant{ (Square(b)) - (4 * a * c) };
	if (discriminant > 0)
	{
		const float t1{ (-b - sqrtf(discriminant)) / (2 * a) }, t2{ (-b + sqrtf(discriminant)) / (2 * a) };
		float small{ t1 }, big{ t2 };
		if (t1 >t2)
		{
			small = t2;
			big = t1;
		}
		if (small > ray.m_TMin && small < ray.m_TMax)
		{
			hitrecord.hitPoint = ray.m_Origin + small * ray.m_Direction;
			hitrecord.normal = Elite::GetNormalized(FVector3(m_Position - hitrecord.hitPoint));
			hitrecord.material = m_Material;
			hitrecord.tValue = small;
			return true;
		}
		else if (big > ray.m_TMin && big < ray.m_TMax)
		{
			hitrecord.hitPoint = ray.m_Origin + big * ray.m_Direction;
			hitrecord.normal = Elite::GetNormalized(FVector3(m_Position - hitrecord.hitPoint));
			hitrecord.material = m_Material;
			hitrecord.tValue = big;
			return true;
		}
	}
	return false;
}

