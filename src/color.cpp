#include "color.hpp"

namespace oglu
{
	const Color Color::Black(0.f, 0.f, 0.f, 1.f);
	const Color Color::White(1.f, 1.f, 1.f, 1.f);
	const Color Color::Red(1.f, 0.f, 0.f, 1.f);
	const Color Color::Green(0.f, 1.f, 0.f, 1.f);
	const Color Color::Blue(0.f, 0.f, 1.f, 1.f);
	const Color Color::Yellow(1.f, 1.f, 0.f, 1.f);
	const Color Color::Magenta(1.f, 0.f, 1.f, 1.f);
	const Color Color::Cyan(0.f, 1.f, 1.f, 1.f);
	const Color Color::Transparent(0.f, 0.f, 0.f, 0.f);

	Color::Color() :
		r(0.f), g(0.f), b(0.f), a(0.f)
	{
	}

	Color::Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) :
		r(red), g(green), b(blue), a(alpha)
	{
	}

	bool operator==(const Color& left, const Color& right)
	{
		return
			(
				(left.r == right.r) &&
				(left.g == right.g) &&
				(left.b == right.b) &&
				(left.a == right.a)
			);
	}

	bool operator!=(const Color& left, const Color& right)
	{
		return !(left == right);
	}

	Color operator+(const Color& left, const Color& right)
	{
		return Color(
			left.r + right.r,
			left.g + right.g,
			left.b + right.b,
			left.a + right.a
		);
	}

	Color operator-(const Color& left, const Color& right)
	{
		return Color(
			left.r - right.r,
			left.g - right.g,
			left.b - right.b,
			left.a - right.a
		);
	}

	Color operator*(const Color& left, const Color& right)
	{
		return Color(
			left.r * right.r,
			left.g * right.g,
			left.b * right.b,
			left.a * right.a
		);
	}

	Color& operator+=(Color& left, const Color& right)
	{
		left = left + right;
		return left;
	}

	Color& operator-=(Color& left, const Color& right)
	{
		left = left - right;
		return left;
	}

	Color& operator*=(Color& left, const Color& right)
	{
		left = left * right;
		return left;
	}
}
