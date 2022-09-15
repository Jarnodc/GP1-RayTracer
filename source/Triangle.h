#pragma once
//---------------------------
// Includes
//---------------------------
#include "Object.h"
#include <vector>

//-----------------------------------------------------
// Triangle Class									
//-----------------------------------------------------
class Triangle final : public Object
{
public:
	// -------------------------
	// Enum Class
	// ------------------------- 
	enum class CullMode
	{
		Back_Face,
		Front_Face,
		No_Culling
	};
	Triangle(const FPoint3& centerPos, Material* baseMaterial, CullMode cullMode = CullMode::No_Culling);				// Constructor
	Triangle(const std::vector<FVector3>& vertices, Material* baseMaterial, CullMode cullMode = CullMode::Back_Face);	// Constructor
	Triangle() = default;																								// Constructor
	virtual ~Triangle() override;	// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	Triangle(const Triangle& other) = delete;
	Triangle(Triangle&& other) noexcept = delete;
	Triangle& operator=(const Triangle& other) = delete;
	Triangle& operator=(Triangle&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void UpdateRotation(float deltaT);
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord) const override;

	void SetCullMode(CullMode cullMode);
	void SetPositionVertices(const std::vector<FVector3>& vertices);
	
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	CullMode m_CurCullMode;
	std::vector<FVector3> m_Vertices;
	std::vector<FVector3*> m_Edges;
};

