//External includes
#include "SDL.h"
#include "SDL_surface.h"

#include "ERenderer.h"
#include <iostream>

Elite::Renderer::Renderer(SDL_Window* pWindow)
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;

	//init Materials
	InitMaterials();

	//init objects
	InitPlanes();
	InitSpheres();
	InitTriangles();
	//InitBunny();
	
	//init lights
	InitLights();
	
	std::cout << "For world up you have to push Z - C instead of left and mouse button. The rest of the movement should work." << std::endl;
}

Elite::Renderer::~Renderer()
{
	delete SceneGraph::GetInstance();
	delete LightManager::GetInstance();
	delete MaterialManager::GetInstance();
	delete Parser::GetInstance();
	delete Camera::GetInstance();
}

void Elite::Renderer::Render(Timer* pTimer)
{
	SDL_LockSurface(m_pBackBuffer);

	Camera::GetInstance()->Update(pTimer);
	LightManager::GetInstance()->Update();
	SceneGraph::GetInstance()->Update(pTimer->GetElapsed());

	//Loop over all the pixels
	const float aspectRatio{ static_cast<float> (m_Width) / static_cast<float> (m_Height) };
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			const float x{ (2 * ((c + 0.5f) / m_Width) - 1.f) * aspectRatio * Camera::GetInstance()->GetFOV() };
			const float y{ ((1 - (2 * (r + 0.5f)) / m_Height)) * Camera::GetInstance()->GetFOV() };

			const FPoint4 pwp{ x,y,1,0 };

			const FPoint4 tpwp{ Camera::GetInstance()->GetONB() * pwp };
			const FPoint4 rayOrigin{ Camera::GetInstance()->GetPos() };

			const FVector4 rayDirection{ tpwp - rayOrigin };

			const Ray ray(Camera::GetInstance()->GetPos(), static_cast<FVector3>(rayDirection));
			HitRecord hitRecord{};

			//CalcFinalColor
			const RGBColor finalColor = HitObject(ray, hitRecord) ? LightManager::GetInstance()->GetIrradiance(hitRecord) : RGBColor(0,0,0);
			m_pBackBufferPixels[c + (r * m_Width)] = GetSDL_ARGBColor(finalColor);

		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
	}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

void Elite::Renderer::InitMaterials()
{
	MaterialManager::GetInstance()->AddMaterial(new Material_CookTorrence(RGBColor(.75f, .75f, .75f), .9f, true, .01f));		// RoughtMetal		- 0
	MaterialManager::GetInstance()->AddMaterial(new Material_CookTorrence(RGBColor(.75f, .75f, .75f), .9f, true, .16f));		// MediumMetal		- 1
	MaterialManager::GetInstance()->AddMaterial(new Material_CookTorrence(RGBColor(.75f, .75f, .75f), .9f, true, 1));			// SmoothMetal		- 2
	MaterialManager::GetInstance()->AddMaterial(new Material_CookTorrence(RGBColor(.972f, .960f, .915f), .9f, false, .01f));	// RoughPlastic		- 3
	MaterialManager::GetInstance()->AddMaterial(new Material_CookTorrence(RGBColor(.972f, .960f, .915f), .9f, false, .36f));	// MediumPlastic	- 4
	MaterialManager::GetInstance()->AddMaterial(new Material_CookTorrence(RGBColor(.972f, .960f, .915f), .9f, false, 1));		// SmoothPlastic	- 5
	MaterialManager::GetInstance()->AddMaterial(new Material(RGBColor(0.49f, 0.57f, 0.57f), 1));								// LambertGreyBlue	- 6
	MaterialManager::GetInstance()->AddMaterial(new Material(RGBColor(1.f, 1.f, 1.f), 1));										// LambertWhite		- 7
	MaterialManager::GetInstance()->AddMaterial(new Material(RGBColor(99/255.f, 44 / 255.f, 99 / 255.f), 1));								// LambertGreyBlue	- 6
	MaterialManager::GetInstance()->AddMaterial(new Material(RGBColor(207 / 255.f, 181 / 255.f, 59 / 255.f), 1));								// LambertGreyBlue	- 6
}

void Elite::Renderer::InitSpheres()
{
	SceneGraph::GetInstance()->AddObject(new Sphere(FPoint3(-1.75f, 1.f, 0.f), .75f, MaterialManager::GetInstance()->GetMaterials()[0]));
	SceneGraph::GetInstance()->AddObject(new Sphere(FPoint3(0.f, 1.f, 0.f), .75f, MaterialManager::GetInstance()->GetMaterials()[1]));
	SceneGraph::GetInstance()->AddObject(new Sphere(FPoint3(1.75f, 1.f, 0.f), .75f, MaterialManager::GetInstance()->GetMaterials()[2]));
	SceneGraph::GetInstance()->AddObject(new Sphere(FPoint3(-1.75f, 3.f, 0.f), .75f, MaterialManager::GetInstance()->GetMaterials()[3]));
	SceneGraph::GetInstance()->AddObject(new Sphere(FPoint3(0.f, 3.f, 0.f), .75f, MaterialManager::GetInstance()->GetMaterials()[4]));
	SceneGraph::GetInstance()->AddObject(new Sphere(FPoint3(1.75f, 3.f, 0.f), .75f, MaterialManager::GetInstance()->GetMaterials()[5]));
}

void Elite::Renderer::InitPlanes()
{
	SceneGraph::GetInstance()->AddObject(new Plane(FPoint3(0, 0, 0), FVector3{ 0,1,0 }, MaterialManager::GetInstance()->GetMaterials()[6]));
	SceneGraph::GetInstance()->AddObject(new Plane(FPoint3(0, 0, -10), FVector3{ 0,0,1 }, MaterialManager::GetInstance()->GetMaterials()[6]));
	SceneGraph::GetInstance()->AddObject(new Plane(FPoint3(0, 10, 0), FVector3{ 0,-1,0 }, MaterialManager::GetInstance()->GetMaterials()[6]));
	SceneGraph::GetInstance()->AddObject(new Plane(FPoint3(5, 0, 0), FVector3{ -1,0,0 }, MaterialManager::GetInstance()->GetMaterials()[8]));
	SceneGraph::GetInstance()->AddObject(new Plane(FPoint3(-5, 0, 0), FVector3{ 1,0,0 }, MaterialManager::GetInstance()->GetMaterials()[9]));
}

void Elite::Renderer::InitTriangles()
{
	SceneGraph::GetInstance()->AddObject(new Triangle(FPoint3(-1.75f, 4.5f, 0.f), MaterialManager::GetInstance()->GetMaterials()[7], Triangle::CullMode::Back_Face));
	SceneGraph::GetInstance()->AddObject(new Triangle(FPoint3(0.f, 4.5f, 0.f), MaterialManager::GetInstance()->GetMaterials()[7], Triangle::CullMode::Front_Face));
	SceneGraph::GetInstance()->AddObject(new Triangle(FPoint3(1.75f, 4.5f, 0.f), MaterialManager::GetInstance()->GetMaterials()[7], Triangle::CullMode::No_Culling));
}

void Elite::Renderer::InitBunny()
{
	SceneGraph::GetInstance()->AddObject(Parser::GetInstance()->GetTriangleMesh("lowpoly_bunny.obj"));
}

void Elite::Renderer::InitLights()
{
	const PointLight* leftlight{ new PointLight(FVector3(0.f, 5.f, -5.f),RGBColor(1.f, .61f, .45f),50.f) };
	LightManager::GetInstance()->AddLight(leftlight);
	LightManager::GetInstance()->AddLight(new PointLight(FVector3(-2.5f, 5.f, 5.f), RGBColor(1.f, .8f, .45f), 70.f));
	LightManager::GetInstance()->AddLight(new PointLight(FVector3(.5f, 2.5f, 5.f), RGBColor(.34f, .47f, .68f), 50.f));
	LightManager::GetInstance()->SetLeftLight(leftlight);
}

bool Elite::Renderer::HitObject(const Ray& ray, HitRecord& hitRecord)
{	
	hitRecord.tValue = FLT_MAX;
	bool hit{ false };
	for (const Object* pObj : SceneGraph::GetInstance()->GetObjects())
	{
		HitRecord tempH;
		if (pObj->Hit(ray, tempH))
		{
			hit = true;
			if (tempH.tValue < hitRecord.tValue)
			{
				hitRecord = tempH;
			}
		}
	}
	return hit;
}
