#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Object.h"
#include "Material.h"

//-----------------------------------------------------
// Sphere Class									
//-----------------------------------------------------
class Sphere final : public Object
{
public:
	explicit Sphere(const FPoint3& centerPos,const float& radius, Material* baseMaterial);	// Constructor
	explicit Sphere();	// Constructor
	virtual ~Sphere() override = default;				// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	Sphere(const Sphere& other) = delete;
	Sphere(Sphere&& other) noexcept = delete;
	Sphere& operator=(const Sphere& other) = delete;
	Sphere& operator=(Sphere&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord) const override;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	const float m_Radius;
};

