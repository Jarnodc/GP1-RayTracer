#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <vector>
#include "Light.h"
#include "ray_HitRecord.h"
#include "ERGBColor.h"

//-----------------------------------------------------
// LightManager Class									
//-----------------------------------------------------
class LightManager final
{
public:
	// -------------------------
	// Enum Class
	// ------------------------- 
	enum class LightMode
	{
		OnlyIrradiance,
		OnlyBRDF,
		AllCombined
	};

	~LightManager();	// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// ------------------------- 
	LightManager(const LightManager& other) = delete;
	LightManager(LightManager&& other) noexcept = delete;
	LightManager& operator=(const LightManager& other) = delete;
	LightManager& operator=(LightManager&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Update();

	void AddLight(const Light* lig);
	void SetLeftLight(const Light* leftLight);

	std::vector<const Light*> GetLights();
	RGBColor GetIrradiance(HitRecord& hitRecord) const;

	//-------------------------------------------------
	// Static Member functions						
	//-------------------------------------------------
	static LightManager* GetInstance();
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	LightManager();	// Constructor

	void FlipFlop(bool& outBool);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::vector<const Light*> m_pLights;
	const Light* m_pLeftLight;

	bool m_DirectionalLight = true;
	bool m_LeftPointLight = true;
	bool m_RightPointLight = true;
	bool m_HardShadows = true;

	LightMode mode = LightMode::AllCombined;
	
	//-------------------------------------------------
	// Static Datamembers								
	//-------------------------------------------------
	static LightManager* m_pInstance;
};

