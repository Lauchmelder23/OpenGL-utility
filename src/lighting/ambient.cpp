#include "lighting/ambient.hpp"

namespace oglu
{
	AmbientLight::AmbientLight() :
		color(1.f, 1.f, 1.f), intensity(1.0f)
	{
	}

	AmbientLight::AmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity) :
		color(r, g, b), intensity(intensity)
	{
	}

	AmbientLight::AmbientLight(const Color& color, GLfloat intensity) :
		color(color), intensity(intensity)
	{
	}

	AmbientLight::AmbientLight(const AmbientLight& other) :
		color(other.color), intensity(other.intensity)
	{
	}
}