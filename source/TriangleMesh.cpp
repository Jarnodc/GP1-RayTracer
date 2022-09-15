//---------------------------
// Includes
//---------------------------
#include "TriangleMesh.h"
#include <iostream>

//---------------------------
// Constructor(s) & Destructor
//---------------------------
TriangleMesh::TriangleMesh(const FPoint3& centerPos, Material* material, const std::vector<FVector3>& vertexBuffer, const std::vector<IPoint3>& idxBuffer, const FMatrix4& matrix)
	:Object(centerPos,material)
	,m_Matrix{matrix}
	,m_VertexBuffer{vertexBuffer}
	,m_IdxBuffer{idxBuffer}
{
	const size_t size{ idxBuffer.size() };
	for (size_t i = 0; i < size; ++i)
	{
		std::vector<FVector3> vertices{ };
		vertices.push_back(vertexBuffer[idxBuffer[i].x]);
		vertices.push_back(vertexBuffer[idxBuffer[i].y]);
		vertices.push_back(vertexBuffer[idxBuffer[i].z]);
		m_Triangles.push_back(new Triangle(vertices, material));
	}
}

TriangleMesh::~TriangleMesh()
{
	for (Triangle* triangle : m_Triangles)
	{
		delete triangle;
		triangle = nullptr;
	}
}

//---------------------------
// Member functions
//---------------------------
void TriangleMesh::UpdateRotation(float deltaT)
{
	m_Matrix *= (FMatrix4)MakeRotationY(deltaT); 
	const size_t size{ m_IdxBuffer.size() };
	for (size_t i = 0; i < size; ++i)
	{
		std::vector<FVector3> vertices{};
		vertices.push_back( (m_Matrix * FVector4{m_VertexBuffer[m_IdxBuffer[i].x]}).xyz );
		vertices.push_back( (m_Matrix * FVector4{m_VertexBuffer[m_IdxBuffer[i].y]}).xyz );
		vertices.push_back( (m_Matrix * FVector4{m_VertexBuffer[m_IdxBuffer[i].z]}).xyz );
		m_Triangles[i]->SetPositionVertices(vertices);
	}
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	for (Triangle* triangle : m_Triangles)
	{
		if(triangle->Hit(ray,hitrecord))
			return true;
	}
	return false;
}