#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <vector>
#include "Object.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include <typeinfo>

//-----------------------------------------------------
// SceneGraph Class									
//-----------------------------------------------------
class SceneGraph final
{
public:
	~SceneGraph();	// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// ------------------------------------------------- 
	SceneGraph(const SceneGraph& other) = delete;
	SceneGraph(SceneGraph&& other) noexcept = delete;
	SceneGraph& operator=(const SceneGraph& other) = delete;
	SceneGraph& operator=(SceneGraph&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Update(float deltaT);

	void AddObject(Object* obj);
	std::vector<Object*> GetObjects();

	//-------------------------------------------------
	// Static Member functions						
	//-------------------------------------------------
	static SceneGraph* GetInstance();

 private:
	 //-------------------------------------------------
	 // Private member functions								
	 //-------------------------------------------------
	SceneGraph() = default;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::vector<Object*> m_pObjects;


	//-------------------------------------------------
	// Static Datamembers								
	//-------------------------------------------------
	static SceneGraph* m_pInstance;
};

