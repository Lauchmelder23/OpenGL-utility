/*****************************************************************//**
 * \file   shader.hpp
 * \brief  Contains functions and objects relevant to shading
 * 
 * \author Robert
 * \date   January 2021
 *********************************************************************/

#ifndef SHADER_HPP
#define SHADER_HPP

#include <core.hpp>

namespace oglu
{
	class Color;
	class AbstractTexture;
	class Transformable;

	typedef std::shared_ptr<AbstractTexture> Texture;

	class AbstractShader;

	typedef std::shared_ptr<AbstractShader> Shader;

	/**
	 * @brief An object representing an OpenGL Shader Program.
	 * 
	 * This class contains the OpenGL Shader Program and supplies the user
	 * with functions to operate on this program.
	 * 
	 * This class cannot be instantiated, this should be done via MakeShader(const char* vertexShaderFile, const char* fragmentShaderFile).
	 */
	class OGLU_API AbstractShader
	{
	public:
		/**
		 * @brief Constructs a new shader program.
		 * 
		 * Use this function to create new shaders.
		 * 
		 * @param[in] vertexShaderFile Filepath to the vertex shader
		 * @param[in] fragmentShaderFile Filepath to the fragment shader
		 * 
		 * @return A shared pointer to the shader program.
		 */
		friend Shader OGLU_API MakeShader(const char* vertexShaderFile, const char* fragmentShaderFile);
		
		/**
		 * @brief Copy constructor.
		 * 
		 * Copying a shader is generally possible. Since the user is given a shared pointer the
		 * shader program is only deleted once every instance has been deconstructed.
		 * 
		 * @param[in] other Shader to copy from
		 */
		AbstractShader(const AbstractShader& other);
		~AbstractShader();

		/**
		 * @brief Use this shader.
		 */
		void Use();

		/**
		 * @brief Get the uniform location within the program.
		 * 
		 * @param[in] name Name of the uniform
		 * 
		 * @return Location of the uniform.
		 */
		GLint GetUniformLocation(const GLchar* name);

#pragma region Uniforms
		/**
		 * @brief Set uniform float.
		 * 
		 * @param[in] name Name of the uniform
		 * @param[in] v0 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLfloat v0);

		/**
		 * @brief Set uniform float.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLfloat v0);
			 
		/**
		 * @brief Set uniform vec2.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLfloat v0, GLfloat v1);

		/**
		 * @brief Set uniform vec2.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLfloat v0, GLfloat v1);
			 
		/**
		 * @brief Set uniform vec3.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1, v2 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLfloat v0, GLfloat v1, GLfloat v2);

		/**
		 * @brief Set uniform vec3.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1, v2 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLfloat v0, GLfloat v1, GLfloat v2);
			 
		/**
		 * @brief Set uniform vec4.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1, v2, v3 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

		/**
		 * @brief Set uniform vec4.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1, v2, v3 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
			 
		/**
		 * @brief Set uniform int.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLint v0);

		/**
		 * @brief Set uniform int.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLint v0);
			  
		/**
		 * @brief Set uniform ivec2.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLint v0, GLint v1);

		/**
		 * @brief Set uniform ivec2.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLint v0, GLint v1);
			  
		/**
		 * @brief Set uniform ivec3.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1, v2 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLint v0, GLint v1, GLint v2);

		/**
		 * @brief Set uniform ivec3.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1, v2 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLint v0, GLint v1, GLint v2);
			 
		/**
		 * @brief Set uniform ivec4.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1, v2, v3 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLint v0, GLint v1, GLint v2, GLint v3);

		/**
		 * @brief Set uniform ivec4.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1, v2, v3 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLint v0, GLint v1, GLint v2, GLint v3);

		/**
		 * @brief Set uniform uint.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLuint v0);

		/**
		 * @brief Set uniform uint.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLuint v0);
						
		/**
		 * @brief Set uniform uvec2.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLuint v0, GLuint v1);

		/**
		 * @brief Set uniform uvec2.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLuint v0, GLuint v1);
						
		/**
		 * @brief Set uniform uvec3.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1, v2 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLuint v0, GLuint v1, GLuint v2);

		/**
		 * @brief Set uniform uvec3.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1, v2 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLuint v0, GLuint v1, GLuint v2);

		/**
		 * @brief Set uniform uvec4.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0, v1, v2, v3 Value to set the uniform to
		 */
		void SetUniform(const GLchar* name,	GLuint v0, GLuint v1, GLuint v2, GLuint v3);

		/**
		 * @brief Set uniform uvec4.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0, v1, v2, v3 Value to set the uniform to
		 */
		void SetUniform(GLint location,		GLuint v0, GLuint v1, GLuint v2, GLuint v3);

		/**
		 * @brief Set uniform color.
		 * 
		 * Sets either a uniform vec3 or vec4, depending on wether alpha is enabled.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0 Value to set the uniform to
		 * @param[in] ignoreAlpha Toggles the alpha channel
		 */
		void SetUniform(const GLchar* name, const Color& v0, bool ignoreAlpha = false);

		/**
		 * @brief Set uniform color.
		 *
		 * Sets either a uniform vec3 or vec4, depending on wether alpha is enabled.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0 Value to set the uniform to
		 * @param[in] ignoreAlpha Toggles the alpha channel
		 */
		void SetUniform(GLint location,		const Color& v0, bool ignoreAlpha = false);

		/**
		 * @brief Set uniform sampler2D.
		 *
		 * Activates and binds the given texture, then sets the uniform.
		 * Note: In many cases, using AbstractTexture::BindAs(GLbyte index) to activate and bind the textures 
		 * seperately and then using SetUniform(GLint location, GLint v0) to set the uniform might
		 * be more efficient.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0 Value to set the uniform to
		 * @param[in] index Index of the texture unit
		 */
		void SetUniformTexture(const GLchar* name, const Texture& v0, GLbyte index = 0);

		/**
		 * @brief Set uniform color.
		 *
		 * Activates and binds the given texture, then sets the uniform
		 * Note: In many cases, using AbstractTexture::BindAs(GLbyte index) to activate and bind the textures 
		 * seperately and then using SetUniform(const GLchar* name, GLint v0) to set the uniform might
		 * be more efficient.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0 Value to set the uniform to
		 * @param[in] index Index of the texture unit
		 */
		void SetUniformTexture(GLint location, const Texture& v0, GLbyte index = 0);

		/**
		 * @brief Set uniform mat4.
		 *
		 * Sets the specified uniform to the transformation matrix of a
		 * Transformable object
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] v0 Value to set the uniform to
		 * @param[in] transpose Transpose matrix before setting the uniform
		 */
		void SetUniform(const GLchar* name, Transformable& v0, GLboolean transpose = GL_FALSE);

		/**
		 * @brief Set uniform mat4.
		 *
		 * Sets the specified uniform to the transformation matrix of a
		 * Transformable object
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] v0 Value to set the uniform to
		 * @param[in] transpose Transpose matrix before setting the uniform
		 */
		void SetUniform(GLint location, Transformable& v0, GLboolean transpose = GL_FALSE);

		/**
		 * @brief Set array of uniform float.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform1fv(const GLchar* name,	GLsizei count, const GLfloat* value);

		/**
		 * @brief Set array of uniform float.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform1fv(GLint location,		GLsizei count, const GLfloat* value);
		
		/**
		 * @brief Set array of uniform vec2.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform2fv(const GLchar* name,	GLsizei count, const GLfloat* value);

		/**
		 * @brief Set array of uniform vec2.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform2fv(GLint location,		GLsizei count, const GLfloat* value);
						 
		/**
		 * @brief Set array of uniform vec3.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform3fv(const GLchar* name,	GLsizei count, const GLfloat* value);

		/**
		 * @brief Set array of uniform vec3.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform3fv(GLint location,		GLsizei count, const GLfloat* value);
						 
		/**
		 * @brief Set array of uniform vec4.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform4fv(const GLchar* name,	GLsizei count, const GLfloat* value);

		/**
		 * @brief Set array of uniform vec4.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform4fv(GLint location,		GLsizei count, const GLfloat* value);

		/**
		 * @brief Set array of uniform int.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform1iv(const GLchar* name,	GLsizei count, const GLint* value);

		/**
		 * @brief Set array of uniform int.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform1iv(GLint location,		GLsizei count, const GLint* value);
						
		/**
		 * @brief Set array of uniform ivec2.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform2iv(const GLchar* name,	GLsizei count, const GLint* value);

		/**
		 * @brief Set array of uniform ivec2.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform2iv(GLint location,		GLsizei count, const GLint* value);
						
		/**
		 * @brief Set array of uniform ivec3.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform3iv(const GLchar* name,	GLsizei count, const GLint* value);

		/**
		 * @brief Set array of uniform ivec3.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform3iv(GLint location,		GLsizei count, const GLint* value);
						
		/**
		 * @brief Set array of uniform ivec4.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform4iv(const GLchar* name,	GLsizei count, const GLint* value);

		/**
		 * @brief Set array of uniform ivec4.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform4iv(GLint location,		GLsizei count, const GLint* value);

		/**
		 * @brief Set array of uniform uint.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform1uiv(const GLchar* name, GLsizei count, const GLuint* value);

		/**
		 * @brief Set array of uniform uint.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform1uiv(GLint location,		GLsizei count, const GLuint* value);
						
		/**
		 * @brief Set array of uniform uvec2.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform2uiv(const GLchar* name, GLsizei count, const GLuint* value);

		/**
		 * @brief Set array of uniform uvec2.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform2uiv(GLint location,		GLsizei count, const GLuint* value);
						
		/**
		 * @brief Set array of uniform uvec3.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform3uiv(const GLchar* name, GLsizei count, const GLuint* value);

		/**
		 * @brief Set array of uniform uvec3.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform3uiv(GLint location,		GLsizei count, const GLuint* value);
						
		/**
		 * @brief Set array of uniform uvec4.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform4uiv(const GLchar* name,	GLsizei count, const GLuint* value);

		/**
		 * @brief Set array of uniform uvec4.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniform4uiv(GLint location,		GLsizei count, const GLuint* value);

		/**
		 * @brief Set (array of) uniform 2x2 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix2fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 2x2 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix2fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 3x3 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix3fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 3x3 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix3fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 4x4 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix4fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 4x4 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix4fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 2x3 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix2x3fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 2x3 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix2x3fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 3x2 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix3x2fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 3x2 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix3x2fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 2x4 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix2x4fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 2x4 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix2x4fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 4x2 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix4x2fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 4x2 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix4x2fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 3x4 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix3x4fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 3x4 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix3x4fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 4x3 matrix.
		 *
		 * @param[in] name Name of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix4x3fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);

		/**
		 * @brief Set (array of) uniform 4x3 matrix.
		 *
		 * @param[in] location Location of the uniform
		 * @param[in] count Amount of elements to set
		 * @param[in] transpose Wether to transpose the supplied matrix
		 * @param[in] value Values to set uniforms to
		 */
		void SetUniformMatrix4x3fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);
#pragma endregion Uniforms

	private:
		/**
		 * @brief Construct a shader program.
		 * 
		 * To avoid accidental deletion of shader programs while they're still in use, 
		 * this constructor has been made private. To create a shader program use
		 * MakeShader(const char* vertexShaderFile, const char* fragmentShaderFile).
		 * 
		 * @param[in] vertexShaderFile Filepath to the vertex shader
		 * @param[in] fragmentShaderFile Filepath to the fragment shader
		 */
		AbstractShader(const char* vertexShaderFile, const char* fragmentShaderFile);

		/**
		 * @brief Loads a shader file from disk
		 *
		 * @param[in] filename Filepath to the shader
		 * @param[out] buffer Contents of the shader file
		 */
		void LoadShaderSource(const char* filename, char** buffer);

	private:
		GLuint program;	///< Handle to the Shader program
	};

	Shader OGLU_API MakeShader(const char* vertexShaderFile, const char* fragmentShaderFile);
}

#endif