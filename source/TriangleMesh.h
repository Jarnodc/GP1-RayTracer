#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <vector>
#include "EMath.h"
#include "Object.h"
#include "Triangle.h"

using namespace Elite;

//-----------------------------------------------------
// TriangleMesh Class									
//-----------------------------------------------------
class TriangleMesh final : public Object
{
public:
	TriangleMesh(const FPoint3& centerPos,Material* material, const std::vector<FVector3>& vertexBuffer,const std::vector<IPoint3>& idxBuffer,const FMatrix4& matrix);	// Constructor
	virtual ~TriangleMesh() override;	// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// -------------------------------------------------    
	TriangleMesh(const TriangleMesh& other) = delete;
	TriangleMesh(TriangleMesh&& other) noexcept = delete;
	TriangleMesh& operator=(const TriangleMesh& other) = delete;
	TriangleMesh& operator=(TriangleMesh&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void UpdateRotation(float deltaT);
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord) const override;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::vector<Triangle*> m_Triangles;
	std::vector<FVector3> m_VertexBuffer;
	std::vector<IPoint3> m_IdxBuffer;
	FMatrix4 m_Matrix;
};

