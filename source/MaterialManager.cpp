//---------------------------
// Includes
//---------------------------
#include "MaterialManager.h"

//---------------------------
// Static datamembers
//---------------------------
MaterialManager* MaterialManager::m_pInstance = nullptr;

//---------------------------
// Constructor(s) & Destructor
//---------------------------
MaterialManager::~MaterialManager()
{
	for (Material* mat : m_pMaterials)
	{
		delete mat;
		mat = nullptr;
	}
}

//---------------------------
// Member functions
//---------------------------
MaterialManager* MaterialManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new MaterialManager();
	return m_pInstance;
}

void MaterialManager::AddMaterial(Material* mat)
{
	m_pMaterials.push_back(mat);
}

std::vector<Material*> MaterialManager::GetMaterials()
{
	return m_pMaterials;
}