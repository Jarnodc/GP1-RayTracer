#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "EMath.h"
#include "SDL.h"
#include "ETimer.h"

using namespace Elite;
//-----------------------------------------------------
// Camera Class									
//-----------------------------------------------------
class Camera final
{
public:
	Camera(const FPoint3& position, const FVector3& normal, const float& scalefactor = 1.f);		// Constructor
	~Camera() = default;			// Destructor
				
	// -------------------------
	// Copy/move constructors and assignment operators
	// ------------------------- 
	Camera(const Camera& other) = delete;
	Camera(Camera&& other) noexcept = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera& operator=(Camera&& other) noexcept = delete;

	//-------------------------------------------------
	// Static Member functions						
	//-------------------------------------------------
	static Camera* GetInstance();

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Update(Timer* pTimer);

	FMatrix4 GetONB();
	float GetFOV() const;
	FPoint3 GetPos() const;
private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	void MoveForward(float scaleFactor);
	void MoveRight(float scaleFactor);
	void MoveUpWorld(float scaleFactor);
	void Pitch(float scaleFactor);
	void Yaw(float scaleFactor);

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	FPoint3 m_Position;
	FVector3 m_Normal;
	float m_ScaleFactor;
	float m_Speed;

	FVector3 m_Forward;
	FVector3 m_Right;
	FVector3 m_Up;
	FVector3 m_WorldUp;

	FMatrix4 m_ONB;
	IVector2 m_MousePos;

	//-------------------------------------------------
	// Static Datamembers								
	//-------------------------------------------------
	static Camera* m_pInstance;
};

