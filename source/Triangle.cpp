//---------------------------
// Includes
//---------------------------
#include "Triangle.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Triangle::Triangle(const FPoint3& centerPos, Material* baseMaterial, CullMode cullMode)
	:Object(centerPos, baseMaterial)
	,m_CurCullMode{ cullMode }
{
	m_Vertices.push_back(static_cast<FVector3>(centerPos + FVector3{ -.75f,1.5f,0 }));
	m_Vertices.push_back(static_cast<FVector3>(centerPos + FVector3{ -.75f,0,0 }));
	m_Vertices.push_back(static_cast<FVector3>(centerPos + FVector3{ .75f,0,0 }));

	m_Edges.push_back(new FVector3{ m_Vertices[1] - m_Vertices[0] });
	m_Edges.push_back(new FVector3{ m_Vertices[2] - m_Vertices[1] });
	m_Edges.push_back(new FVector3{ m_Vertices[0] - m_Vertices[2] });
	m_Edges.push_back(new FVector3{-.75f,1.5f,0  });
	m_Edges.push_back(new FVector3{-.75f,0,0  });
	m_Edges.push_back(new FVector3{.75f,0,0  });
}

Triangle::Triangle(const std::vector<FVector3>& vertices, Material* baseMaterial, CullMode cullMode)
	:Object(static_cast<FPoint3>((vertices[0]+ vertices[1]+ vertices[2])/3.f),baseMaterial)
	, m_Vertices{vertices}
	, m_CurCullMode{cullMode}
{
	m_Edges.push_back(new FVector3{ m_Vertices[1] - m_Vertices[0] });
	m_Edges.push_back(new FVector3{ m_Vertices[2] - m_Vertices[1] });
	m_Edges.push_back(new FVector3{ m_Vertices[0] - m_Vertices[2] });
	m_Edges.push_back(new FVector3{-.75f,1.5f,0  });
	m_Edges.push_back(new FVector3{-.75f,0,0  });
	m_Edges.push_back(new FVector3{.75f,0,0  });
}

Triangle::~Triangle()
{
	for (FVector3* edge : m_Edges)
	{
		delete edge;
		edge = nullptr;
	}
}

//---------------------------
// Member functions
//---------------------------
void Triangle::UpdateRotation(float deltaT)
{
	const float angleSpeed{ deltaT / 4  }; // 2*pi / 2*pi = 1
	
	FMatrix3 rotMat = { MakeRotationY(angleSpeed) };
	for (FVector3* edge : m_Edges)
	{
		*edge = rotMat * (*edge);
	}
	for (size_t i = 0; i < 3; ++i)
	{
		m_Vertices[i] = static_cast<FVector3>(m_Position + *m_Edges[i + 3]);
	}				   
}
bool Triangle::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	const FVector3 a{ m_Vertices[1] - m_Vertices[0] }, b{ m_Vertices[2] - m_Vertices[0] };

	const FVector3 normal{ Cross(a,b) };
	switch (m_CurCullMode)
	{
	case Triangle::CullMode::Back_Face:
		if (Dot(normal, -ray.m_Direction) < 0)
			return false;
		break;
	case Triangle::CullMode::Front_Face:
		if (Dot(normal, -ray.m_Direction) > 0)
			return false;
		break;
	case Triangle::CullMode::No_Culling:
		if (Dot(normal, -ray.m_Direction) == 0)
			return false;
	}

	const FVector3 L = m_Position - ray.m_Origin;
	const float T = Dot(L, normal) / Dot(ray.m_Direction, normal);

	if (T < ray.m_TMin || T > ray.m_TMax)
		return false;

	const FVector3 p = static_cast<FVector3>(ray.m_Origin + (T * ray.m_Direction));

	for (size_t i = 0; i < 3; ++i)
	{
		if (Dot(normal, Cross(*m_Edges[i], p - m_Vertices[i])) < 0)
			return false;
	}

	hitrecord.hitPoint = static_cast<FPoint3>(p);
	hitrecord.material = m_Material;
	hitrecord.normal = GetNormalized(normal);
	hitrecord.tValue = T;
	return true;

}

void Triangle::SetCullMode(CullMode cullMode)
{
	m_CurCullMode = cullMode;
}
void Triangle::SetPositionVertices(const std::vector<FVector3>& vertices)
{
	m_Vertices = vertices;
	m_Position = FPoint3((vertices[0] + vertices[1] + vertices[2]) / 3.f);
	*m_Edges[0] = FVector3{m_Vertices[1] - m_Vertices[0]} ;
	*m_Edges[1] = FVector3{m_Vertices[2] - m_Vertices[1]} ;
	*m_Edges[2] = FVector3{m_Vertices[0] - m_Vertices[2]} ;
}


