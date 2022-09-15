#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EMath.h"
#include "ray_HitRecord.h"
#include "Material.h"

using namespace Elite;

//-----------------------------------------------------
// Object Class									
//-----------------------------------------------------
class Object
{
public:
	explicit Object(const FPoint3& centerPos, Material* baseMaterial);	// Constructor
	explicit Object();	// Constructor
	virtual ~Object() = default;	// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	Object(const Object& other) = delete;
	Object(Object&& other) noexcept = delete;
	Object& operator=(const Object& other) = delete;
	Object& operator=(Object&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord) const = 0;

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
	FPoint3 m_Position;
	Material* m_Material;
};

