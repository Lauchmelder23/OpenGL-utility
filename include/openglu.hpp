/*****************************************************************//**
 * @file   openglu.hpp
 * @brief  Basic includes and some exposed OpenGL
 * 
 * @author Lauchmelder
 * @date   January 2021
 *********************************************************************/
#ifndef OPENGLU_HPP
#define OPENGLU_HPP

#include <color.hpp>
#include <vertexArray.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <object.hpp>
#include <material.hpp>
#include <camera.hpp>

#include <lighting/ambient.hpp>
#include <lighting/point.hpp>

namespace oglu
{
	/**
	 * @brief Loads the GL Loader to be used by OGLU.
	 * 
	 * OpenGL function addresses can vary across platforms and drivers, so we
	 * need to know where these functions are in order to work properly.
	 * 
	 * @param[in] proc A pointer to a function that returns the addresses of OpenGL functions
	 */
	OGLU_API void LoadGLLoader(GLADloadproc proc);

	/**
	 * @brief Wrapper of glViewport.
	 * 
	 * @param[in] x Horizontal Position of the viewport
	 * @param[in] y Vertical Position of the viewport
	 * @param[in] width Width of the viewport
	 * @param[in] height Height of the viewport
	 */
	OGLU_API void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	/**
	 * @brief Convenience function for glClear
	 * 
	 * Sets the clear color and then clears the screen.
	 * 
	 * @param[in] mask Buffers to be cleared
	 * @param[in] clearColor Color to clear the screen with
	 */
	OGLU_API void ClearScreen(GLbitfield mask, Color clearColor);

	/**
	 * @brief Wrapper for glEnable.
	 * 
	 * @param[in] cap A GL capability
	 */
	OGLU_API void Enable(GLenum cap);

	/**
	 * @brief Wrapper for glDisable.
	 *
	 * @param[in] cap A GL capability
	 */
	OGLU_API void Disable(GLenum cap);

	/**
	 * @brief Wrapper for glEnablei.
	 *
	 * @param[in] cap A GL capability
	 * @param[in] index Index of the switch
	 */
	OGLU_API void Enable(GLenum cap, GLuint index);

	/**
	 * @brief Wrapper for glDisablei.
	 *
	 * @param[in] cap A GL capability
	 * @param[in] index Index of the switch
	 */
	OGLU_API void Disable(GLenum cap, GLuint index);

	/**
	 * @brief Wrapper for glPolygonMode.
	 * 
	 * @param[in] face Type of polygon to apply @p mode to
	 * @param[in] mode Type of rasterization for polygons
	 */
	OGLU_API void PolygonMode(GLenum face, GLenum mode);
}

#endif //OPENGLU_HPP
