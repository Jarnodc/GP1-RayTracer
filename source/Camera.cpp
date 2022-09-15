//---------------------------
// Includes
//---------------------------
#include "Camera.h"

//---------------------------
// Static datamembers
//---------------------------
Camera* Camera::m_pInstance = nullptr;

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Camera::Camera(const FPoint3& position, const FVector3& normal, const float& scalefactor)
	:m_Position{position}
	,m_Normal{ normal }
	,m_ScaleFactor{scalefactor}
	,m_Speed{5.f}
	,m_Forward{ 0,0,-1 }
	,m_WorldUp{ 0,1,0 }
{
	m_Right = Cross(m_WorldUp, m_Forward);
	Normalize(m_Right);
	m_Up = Cross(m_Forward, m_Right);
	Normalize(m_Up);
}

//---------------------------
// Member functions
//---------------------------
Camera* Camera::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new Camera({ 0, 3, 9 }, { 0,1,0 },.5f);
	return m_pInstance;
}

void Camera::Update(Timer* pTimer)
{
	const Uint8* pState = SDL_GetKeyboardState(nullptr);

	const float speed = pState[SDL_SCANCODE_LSHIFT] ? m_Speed * 2.f : m_Speed;

	if (pState[SDL_SCANCODE_W] || pState[SDL_SCANCODE_UP])
	{
		MoveForward(speed * pTimer->GetElapsed());
	}
	if (pState[SDL_SCANCODE_A] || pState[SDL_SCANCODE_LEFT])
	{ 
		MoveRight(speed * pTimer->GetElapsed());
	}
	if (pState[SDL_SCANCODE_S] || pState[SDL_SCANCODE_DOWN])
	{
		MoveForward(-speed * pTimer->GetElapsed());
	}
	if (pState[SDL_SCANCODE_D] || pState[SDL_SCANCODE_RIGHT])
	{
		MoveRight(-speed * pTimer->GetElapsed());
	}
	if (pState[SDL_SCANCODE_Z])
	{
		MoveUpWorld(speed * pTimer->GetElapsed());
	}
	if (pState[SDL_SCANCODE_C])
	{
		MoveUpWorld(-speed * pTimer->GetElapsed());
	}
	
	const IVector2 prevMousePos{ m_MousePos };
	const Uint32 mouseState = SDL_GetMouseState(&m_MousePos.x,&m_MousePos.y);
	if (mouseState == SDL_BUTTON_LEFT)
	{
		const int horDist = m_MousePos.x - prevMousePos.x;
		Pitch(horDist * pTimer->GetElapsed() * 0.01f);
		const int verDist = m_MousePos.y - prevMousePos.y;
		MoveForward(verDist * pTimer->GetElapsed() * 0.01f);
	}
	if (mouseState == 4)
	{
		const int horDist = m_MousePos.x - prevMousePos.x;
		Pitch(horDist * pTimer->GetElapsed() * 0.01f);

		const int verDist = m_MousePos.y - prevMousePos.y;
		Yaw(verDist * pTimer->GetElapsed() * 0.01f);
	}
}

FMatrix4 Camera::GetONB()
{
	m_Right = Cross(m_WorldUp,m_Forward);
	m_Up = Cross(m_Forward, m_Right);
	m_ONB = {
		m_Right.x,m_Up.x,m_Forward.x,m_Position.x,
		m_Right.y,m_Up.y,m_Forward.y,m_Position.y,
		m_Right.z,m_Up.z,m_Forward.z,m_Position.z,
		0,0,0,1
	};
	return m_ONB;
}
float Camera::GetFOV() const
{
	return atanf(m_ScaleFactor);
}
FPoint3 Camera::GetPos() const
{
	return m_Position;
}

void Camera::MoveForward(float scaleFactor)
{
	m_Position += m_Forward * scaleFactor;
}
void Camera::MoveRight(float scaleFactor)
{
	m_Position -= m_Right * scaleFactor;
}
void Camera::MoveUpWorld(float scaleFactor)
{
	m_Position += m_WorldUp * scaleFactor;
}

void Camera::Pitch(float scaleFactor)
{
	m_Right = MakeRotationY(scaleFactor) * m_Right;
	m_Forward = Cross(m_Right, m_Up);
	m_Forward = GetNormalized(m_Forward);
}
void Camera::Yaw(float scaleFactor)
{
	m_Up = MakeRotationX(-scaleFactor) * m_Up;
	m_Forward = Cross(m_Right, m_Up);
	m_Forward = GetNormalized(m_Forward);
}
