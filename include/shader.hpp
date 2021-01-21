#ifndef SHADER_HPP
#define SHADER_HPP

#include <core.hpp>
#include <glad/glad.h>

namespace oglu
{
	class Color;

	class OGLU_API AbstractShader
	{
	public:
		friend std::shared_ptr<AbstractShader> OGLU_API MakeShader(const char* vertexShaderFile, const char* fragmentShaderFile);
		AbstractShader(const AbstractShader& other);
		~AbstractShader();

		void Use();

		GLint GetUniformLocation(const GLchar* name);

#pragma region Uniforms
		void SetUniform(const GLchar* name,	GLfloat v0);
		void SetUniform(GLint location,		GLfloat v0);
			 
		void SetUniform(const GLchar* name,	GLfloat v0, GLfloat v1);
		void SetUniform(GLint location,		GLfloat v0, GLfloat v1);
			 
		void SetUniform(const GLchar* name,	GLfloat v0, GLfloat v1, GLfloat v2);
		void SetUniform(GLint location,		GLfloat v0, GLfloat v1, GLfloat v2);
			 
		void SetUniform(const GLchar* name,	GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		void SetUniform(GLint location,		GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
			 
		void SetUniform(const GLchar* name,	GLint v0);
		void SetUniform(GLint location,		GLint v0);
			  
		void SetUniform(const GLchar* name,	GLint v0, GLint v1);
		void SetUniform(GLint location,		GLint v0, GLint v1);
			  
		void SetUniform(const GLchar* name,	GLint v0, GLint v1, GLint v2);
		void SetUniform(GLint location,		GLint v0, GLint v1, GLint v2);
			 
		void SetUniform(const GLchar* name,	GLint v0, GLint v1, GLint v2, GLint v3);
		void SetUniform(GLint location,		GLint v0, GLint v1, GLint v2, GLint v3);

		void SetUniform(const GLchar* name,	GLuint v0);
		void SetUniform(GLint location,		GLuint v0);
						
		void SetUniform(const GLchar* name,	GLuint v0, GLuint v1);
		void SetUniform(GLint location,		GLuint v0, GLuint v1);
						
		void SetUniform(const GLchar* name,	GLuint v0, GLuint v1, GLuint v2);
		void SetUniform(GLint location,		GLuint v0, GLuint v1, GLuint v2);
						
		void SetUniform(const GLchar* name,	GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		void SetUniform(GLint location,		GLuint v0, GLuint v1, GLuint v2, GLuint v3);

		void SetUniform(const GLchar* name, const Color* v0, bool ignoreAlpha = false);
		void SetUniform(GLint location,		const Color* v0, bool ignoreAlpha = false);

		void SetUniform1fv(const GLchar* name,	GLsizei count, const GLfloat* value);
		void SetUniform1fv(GLint location,		GLsizei count, const GLfloat* value);
						 
		void SetUniform2fv(const GLchar* name,	GLsizei count, const GLfloat* value);
		void SetUniform2fv(GLint location,		GLsizei count, const GLfloat* value);
						 
		void SetUniform3fv(const GLchar* name,	GLsizei count, const GLfloat* value);
		void SetUniform3fv(GLint location,		GLsizei count, const GLfloat* value);
						 
		void SetUniform4fv(const GLchar* name,	GLsizei count, const GLfloat* value);
		void SetUniform4fv(GLint location,		GLsizei count, const GLfloat* value);

		void SetUniform1iv(const GLchar* name,	GLsizei count, const GLint* value);
		void SetUniform1iv(GLint location,		GLsizei count, const GLint* value);
						
		void SetUniform2iv(const GLchar* name,	GLsizei count, const GLint* value);
		void SetUniform2iv(GLint location,		GLsizei count, const GLint* value);
						
		void SetUniform3iv(const GLchar* name,	GLsizei count, const GLint* value);
		void SetUniform3iv(GLint location,		GLsizei count, const GLint* value);
						
		void SetUniform4iv(const GLchar* name,	GLsizei count, const GLint* value);
		void SetUniform4iv(GLint location,		GLsizei count, const GLint* value);

		void SetUniform1uiv(const GLchar* name, GLsizei count, const GLuint* value);
		void SetUniform1uiv(GLint location,		GLsizei count, const GLuint* value);
						
		void SetUniform2uiv(const GLchar* name, GLsizei count, const GLuint* value);
		void SetUniform2uiv(GLint location,		GLsizei count, const GLuint* value);
						
		void SetUniform3uiv(const GLchar* name, GLsizei count, const GLuint* value);
		void SetUniform3uiv(GLint location,		GLsizei count, const GLuint* value);
						
		void SetUniform4uiv(const GLchar* name,	GLsizei count, const GLuint* value);
		void SetUniform4uiv(GLint location,		GLsizei count, const GLuint* value);

		void SetUniformMatrix2fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix2fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix3fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix3fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix4fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix4fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix2x3fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix2x3fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix3x2fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix3x2fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix2x4fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix2x4fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix4x2fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix4x2fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix3x4fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix3x4fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);

		void SetUniformMatrix4x3fv(const GLchar* name,	GLsizei count, GLboolean transpose, const GLfloat* value);
		void SetUniformMatrix4x3fv(GLint location,		GLsizei count, GLboolean transpose, const GLfloat* value);
#pragma endregion Uniforms

	private:
		AbstractShader(const char* vertexShaderFile, const char* fragmentShaderFile);

		void LoadShaderSource(const char* filename, char** buffer);

	private:
		GLuint program;
	};

	typedef std::shared_ptr<AbstractShader> Shader;
}

#endif