/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere, Edited By Jarno De Cooman
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

//---------------------------
// Includes
//---------------------------
#pragma region Includes
#include <cstdint>

//Camera
#include "Camera.h"

//scenegraph
#include "SceneGraph.h"
#include "Parser.h"

//Objects
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "TriangleMesh.h"

//lights
#include "LightManager.h"
#include "PointLight.h"
#include "DirectionalLight.h"

//materials
#include "MaterialManager.h"
#include "Material_LambertPhong.h"
#include "Material_CookTorrence.h"

//Elite includes
#include "ERGBColor.h"
#include "EMatrix.h"

#pragma endregion

struct SDL_Window;
struct SDL_Surface;

namespace Elite
{
	//-----------------------------------------------------
	// Renderer Class									
	//-----------------------------------------------------
	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);	// Constructor
		~Renderer();					// Destructor

		// -------------------------------------------------
		// Copy/move constructors and assignment operators
		// ------------------------------------------------- 
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------
		void Render(Timer* pTimer);
		bool SaveBackbufferToImage() const;

	private:
		//-------------------------------------------------
		// Datamembers							
		//-------------------------------------------------
		SDL_Window* m_pWindow = nullptr;
		SDL_Surface* m_pFrontBuffer = nullptr;
		SDL_Surface* m_pBackBuffer = nullptr;
		uint32_t* m_pBackBufferPixels = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;

		//-------------------------------------------------
		// Private member functions									
		//-------------------------------------------------
		void InitMaterials();
		void InitSpheres();
		void InitPlanes();
		void InitTriangles();
		void InitBunny();
		void InitLights();

		bool HitObject(const Ray& ray, HitRecord& hitRecord);
	};
}

#endif