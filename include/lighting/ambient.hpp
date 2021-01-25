#ifndef AMBIENT_HPP
#define AMBIENT_HPP

#include <core.hpp>
#include <color.hpp>

namespace oglu
{
	class OGLU_API AmbientLight
	{
	public:
		AmbientLight();
		AmbientLight(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity);
		AmbientLight(const Color& color, GLfloat intensity);
		AmbientLight(const AmbientLight& other);

		GLfloat intensity;
		Color color;
	};
}

#endif