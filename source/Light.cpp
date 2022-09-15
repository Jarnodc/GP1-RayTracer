//---------------------------
// Includes
//---------------------------
#include "Light.h"

//---------------------------
// Constructor(s) & Destructor
//---------------------------
Light::Light(const FVector3& position, const RGBColor& color, float intensity)
	:m_Position{position}
	,m_Color{color}
	,m_Intensity{intensity}
{

}

//---------------------------
// Member functions
//---------------------------
const FVector3 Light::GetPosition() const
{
	return m_Position;
}
