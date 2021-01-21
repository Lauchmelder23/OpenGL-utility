/*****************************************************************//**
 * @file   color.hpp
 * @brief  Contains convenience for working with colors.
 * 
 * @author Robert
 * @date   January 2021
 *********************************************************************/

#ifndef COLOR_HPP
#define COLOR_HPP

#include <core.hpp>
#include <glad/glad.h>

namespace oglu
{
	/**
	 * Convenience class for storing and working with color
	 */
	class OGLU_API Color
	{
	public:
		/**
		 * Constructs a transparent black
		 */
		Color();

		/**
		 * Constructs a new color
		 * 
		 * @param red	Red component
		 * @param blue	Blue component
		 * @param green Green component
		 * @param alpha Red component
		 */
		Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 255);
		
	public:
		GLfloat r;	///< Red channel
		GLfloat g;	///< Green channel
		GLfloat b;	///< Blue channel
		GLfloat a;	///< Alpha channel

		static const Color Black;			///< Predefined Black
		static const Color White;			///< Predefined White
		static const Color Red;				///< Predefined Red
		static const Color Green;			///< Predefined Green
		static const Color Blue;			///< Predefined Blue
		static const Color Yellow;			///< Predefined Yellow
		static const Color Magenta;			///< Predefined Magenta
		static const Color Cyan;			///< Predefined Cyan
		static const Color Transparent;		///< Predefined Transparent
	};

	/**
	 * @relates Color
	 * @brief Checks if two colors are equal.
	 * 
	 * @param left Left operand
	 * @param right Right operand
	 * 
	 * @returns True if every color channel is equal
	 */
	OGLU_API bool operator==(const Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Checks if two colors are different.
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns True if not every color channel is equal
	 */
	OGLU_API bool operator!=(const Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Sums two colors
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns The sum of @p left and @p right. The result is clamped to the OpenGL color range.
	 */
	OGLU_API Color operator+(const Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Subtracts two colors
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns The difference of @p left and @p right. The result is clamped to the OpenGL color range.
	 */
	OGLU_API Color operator-(const Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Multiplies two colors component-wise
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns The componen-wise product of @p left and @p right.
	 */
	OGLU_API Color operator*(const Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Sums two colors
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns Reference to @p left
	 */
	OGLU_API Color& operator+=(Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Subtracts two colors
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns Reference to @p left
	 */
	OGLU_API Color& operator-=(Color& left, const Color& right);

	/**
	 * @relates Color
	 * @brief Multiplies two colors component-wise
	 *
	 * @param left Left operand
	 * @param right Right operand
	 *
	 * @returns Reference to @p left
	 */
	OGLU_API Color& operator*=(Color& left, const Color& right);
}

#endif