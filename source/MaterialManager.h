#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Material.h"
#include <vector>
//-----------------------------------------------------
// MaterialManager Class									
//-----------------------------------------------------
class MaterialManager final
{
public:
	~MaterialManager();		// Destructor

	// -------------------------------------------------
	// Copy/move constructors and assignment operators
	// ------------------------------------------------- 
	MaterialManager(const MaterialManager& other) = delete;
	MaterialManager(MaterialManager&& other) noexcept = delete;
	MaterialManager& operator=(const MaterialManager& other) = delete;
	MaterialManager& operator=(MaterialManager&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void AddMaterial(Material* mat);
	std::vector<Material*> GetMaterials();

	//-------------------------------------------------
	// Static Member functions						
	//-------------------------------------------------
	static MaterialManager* GetInstance();
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	MaterialManager() = default;		// Constructor

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::vector<Material*> m_pMaterials;

	//-------------------------------------------------
	// Static Datamembers								
	//-------------------------------------------------
	static MaterialManager* m_pInstance;
};