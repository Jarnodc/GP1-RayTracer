//---------------------------
// Includes
//---------------------------
#include "Object.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Object::Object(const FPoint3& centerPos, Material* baseMaterial)
	:m_Position{centerPos}
	,m_Material{ baseMaterial }
{

}

Object::Object()
	:m_Position{ 0,0,0 }
	,m_Material{ }
{

}

//---------------------------
// Member functions
//---------------------------