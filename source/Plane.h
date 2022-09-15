#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EMath.h"
#include "Material.h"
#include "Object.h"

//-----------------------------------------------------
// Plane Class									
//-----------------------------------------------------
class Plane final : public Object
{
public:
	explicit Plane(const FPoint3& pos, const FVector3& normal,  Material* baseMaterial);	// Constructor
	explicit Plane();				// Constructor
	virtual ~Plane() override = default;				// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	Plane(const Plane& other) = delete;
	Plane(Plane&& other) noexcept = delete;
	Plane& operator=(const Plane& other) = delete;
	Plane& operator=(Plane&& other) noexcept = delete;

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
	const FVector3 m_Normal;
};


