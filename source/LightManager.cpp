//---------------------------
// Includes
//---------------------------
#include "LightManager.h"
#include "SceneGraph.h"
#include "Sphere.h"
#include "Plane.h"
#include "SDL.h"
#include "PointLight.h"
#include "DirectionalLight.h"

//---------------------------
// Static datamembers
//---------------------------
LightManager* LightManager::m_pInstance = nullptr;

//---------------------------
// Constructor(s) & Destructor
//---------------------------
LightManager::LightManager()
    :m_pLeftLight{nullptr}
{
}

LightManager::~LightManager()
{
	for (const Light* lig : m_pLights)
	{
		delete lig;
		lig = nullptr;
	}
}

//---------------------------
// Member functions
//---------------------------
LightManager* LightManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new LightManager();
	return m_pInstance;
}

void LightManager::Update()
{
    const Uint8* pState = SDL_GetKeyboardState(nullptr);

    if (pState[SDL_SCANCODE_Q])
        FlipFlop(m_HardShadows);
    if (pState[SDL_SCANCODE_K])
        FlipFlop(m_LeftPointLight);
    if (pState[SDL_SCANCODE_L])
        FlipFlop(m_RightPointLight);
    if (pState[SDL_SCANCODE_J])
        FlipFlop(m_DirectionalLight);
    if (pState[SDL_SCANCODE_E])
    {
        switch (mode)
        {
        case LightManager::LightMode::OnlyIrradiance:
            mode = LightMode::OnlyBRDF;
            break;
        case LightManager::LightMode::OnlyBRDF:
            mode = LightMode::AllCombined;
            break;
        case LightManager::LightMode::AllCombined:
            mode = LightMode::OnlyIrradiance;
            break;
        default:
            mode = LightMode::AllCombined;
            break;
        }
    }

}
void LightManager::FlipFlop(bool& outBool)
{
    if (outBool)
        outBool = false;
    else
        outBool = true;
}

void LightManager::AddLight(const Light* lig)
{
	m_pLights.push_back(lig);
}
void LightManager::SetLeftLight(const Light* leftLight)
{
    m_pLeftLight = leftLight;
}

std::vector<const Light*> LightManager::GetLights()
{
	return m_pLights;
}
RGBColor LightManager::GetIrradiance(HitRecord& hitRecord) const
{
    RGBColor finalColor{  };
    for (const Light* pLight : m_pLights)
    {
        if (!m_DirectionalLight)
            if (typeid(*pLight) == typeid(DirectionalLight))
                continue;
        if (!m_LeftPointLight && !m_RightPointLight)
            if (typeid(*pLight) == typeid(PointLight))
                continue;
        if(!m_LeftPointLight)
            if (pLight == m_pLeftLight)
                continue;
        if (!m_RightPointLight)
            if (typeid(*pLight) != typeid(DirectionalLight) && pLight != m_pLeftLight)
                continue;

        bool LightBlocked{ false };

        FVector3 direction{ hitRecord.hitPoint - pLight->GetPosition() };
        direction = GetNormalized(direction);
        if (m_HardShadows)
        {
            const Ray shadowRay{ static_cast<FPoint3>(pLight->GetPosition()),direction };
            HitRecord h1;
            for (Object* pObj : SceneGraph::GetInstance()->GetObjects())
            {
                if (typeid(*pObj) != typeid(Plane))
                {
                    if (pObj->Hit(shadowRay, h1))
                    {
                        if (Magnitude(h1.hitPoint - hitRecord.hitPoint) > .001f)
                            LightBlocked = true;
                    }
                }
            }
        }
        if (!LightBlocked)
        {
            FVector3 outDirection{ Project(direction, hitRecord.normal) };
            float dot{ Dot(direction, hitRecord.normal) };
            if (dot < 0)
            {
                direction *= -1;
                outDirection *= -1;
                dot *= -1;
            }
            switch (mode)
            {
            case LightManager::LightMode::OnlyIrradiance:
                finalColor += pLight->CalcIrradiance(hitRecord) * dot;
                break;
            case LightManager::LightMode::OnlyBRDF:
                finalColor += hitRecord.material->Shade(hitRecord, direction, outDirection) * dot;
                break;
            case LightManager::LightMode::AllCombined:
                finalColor += pLight->CalcIrradiance(hitRecord) * hitRecord.material->Shade(hitRecord, direction, outDirection) * dot;
            }
         }
    }
    finalColor.MaxToOne();
    return finalColor;
}



