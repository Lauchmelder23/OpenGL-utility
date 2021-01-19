#ifndef COLOR_HPP
#define COLOR_HPP

#include "core.hpp"
#include <glad/glad.h>

namespace oglu
{
	class OGLU_API Color
	{
	public:
		Color();
		Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 255);
		
	public:
		GLfloat r, g, b, a;

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
	};

	OGLU_API bool operator==(const Color& left, const Color& right);
	OGLU_API bool operator!=(const Color& left, const Color& right);
	OGLU_API Color operator+(const Color& left, const Color& right);
	OGLU_API Color operator-(const Color& left, const Color& right);
	OGLU_API Color operator*(const Color& left, const Color& right);
	OGLU_API Color& operator+=(Color& left, const Color& right);
	OGLU_API Color& operator-=(Color& left, const Color& right);
	OGLU_API Color& operator*=(Color& left, const Color& right);
}

#endif