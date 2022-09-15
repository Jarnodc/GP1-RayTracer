//---------------------------
// Includes
//---------------------------
#include "SceneGraph.h"

//---------------------------
// Static datamembers
//---------------------------
SceneGraph* SceneGraph::m_pInstance = nullptr;

//---------------------------
// Constructor(s) & Destructor
//---------------------------

SceneGraph::~SceneGraph()
{
	for (Object* obj : m_pObjects)
	{
		delete obj;
		obj = nullptr;
	}
}

//---------------------------
// Member functions
//---------------------------
void SceneGraph::Update(float deltaT)
{
	for (Object* pObj : m_pObjects)
	{
		if (typeid(*pObj) == typeid(Triangle))
		{
			Triangle* triangle = static_cast<Triangle*>(pObj);
			triangle->UpdateRotation(deltaT);
		}
		else if (typeid(*pObj) == typeid(TriangleMesh))
		{
			TriangleMesh* triangle = static_cast<TriangleMesh*>(pObj);
			triangle->UpdateRotation(deltaT);
		}
	}
}

void SceneGraph::AddObject(Object* obj)
{
	m_pObjects.push_back(obj);
}
std::vector<Object*> SceneGraph::GetObjects()
{
	return m_pObjects;
}

SceneGraph* SceneGraph::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new SceneGraph();
	return m_pInstance;
}
