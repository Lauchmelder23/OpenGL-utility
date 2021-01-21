#include <shader.hpp>

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

#include <color.hpp>

namespace oglu
{
	AbstractShader::AbstractShader(const AbstractShader& other) :
		program(other.program)
	{

	}

	Shader MakeShader(const char* vertexShaderFile, const char* fragmentShaderFile)
	{
		AbstractShader* tmp = new AbstractShader(vertexShaderFile, fragmentShaderFile);
		return Shader(tmp);
	}

	AbstractShader::AbstractShader(const char* vertexShaderFile, const char* fragmentShaderFile) :
		program(0)
	{
		// Load vertex shader
		char* source = nullptr;
		LoadShaderSource(vertexShaderFile, &source);
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &source, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			delete source;
			throw std::exception(std::string("Failed to compile shader " + std::string(vertexShaderFile) + "\n" + infoLog).c_str());
		}
		delete source;

		// Load Fragment shader
		LoadShaderSource(fragmentShaderFile, &source);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &source, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			delete source;
			throw std::exception(std::string("Failed to compile shader " + std::string(fragmentShaderFile) + "\n" + infoLog).c_str());
		}
		delete source;

		// Link into program
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			throw std::exception(std::string("Failed to link program.\n" + std::string(infoLog)).c_str());
		}

		// Dispose of shader objects
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
	}

	AbstractShader::~AbstractShader()
	{
		glDeleteProgram(program);
	}

	void AbstractShader::Use()
	{
		glUseProgram(program);
	}

	GLint AbstractShader::GetUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(program, name);
	}

#pragma region Uniforms
	void AbstractShader::SetUniform(const GLchar* name, GLfloat v0)
	{
		glUniform1f(glGetUniformLocation(program, name), v0);
	}

	void AbstractShader::SetUniform(GLint location, GLfloat v0)
	{
		glUniform1f(location, v0);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLfloat v0, GLfloat v1)
	{
		glUniform2f(glGetUniformLocation(program, name), v0, v1);
	}

	void AbstractShader::SetUniform(GLint location, GLfloat v0, GLfloat v1)
	{
		glUniform2f(location, v0, v1);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		glUniform3f(glGetUniformLocation(program, name), v0, v1, v2);
	}

	void AbstractShader::SetUniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		glUniform3f(location, v0, v1, v2);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		glUniform4f(glGetUniformLocation(program, name), v0, v1, v2, v3);
	}

	void AbstractShader::SetUniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		glUniform4f(location, v0, v1, v2, v3);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLint v0)
	{
		glUniform1i(glGetUniformLocation(program, name), v0);
	}

	void AbstractShader::SetUniform(GLint location, GLint v0)
	{
		glUniform1i(location, v0);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLint v0, GLint v1)
	{
		glUniform2i(glGetUniformLocation(program, name), v0, v1);
	}

	void AbstractShader::SetUniform(GLint location, GLint v0, GLint v1)
	{
		glUniform2i(location, v0, v1);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLint v0, GLint v1, GLint v2)
	{
		glUniform3i(glGetUniformLocation(program, name), v0, v1, v2);
	}

	void AbstractShader::SetUniform(GLint location, GLint v0, GLint v1, GLint v2)
	{
		glUniform3i(location, v0, v1, v2);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		glUniform4i(glGetUniformLocation(program, name), v0, v1, v2, v3);
	}

	void AbstractShader::SetUniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		glUniform4i(location, v0, v1, v2, v3);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLuint v0)
	{
		glUniform1ui(glGetUniformLocation(program, name), v0);
	}

	void AbstractShader::SetUniform(GLint location, GLuint v0)
	{
		glUniform1ui(location, v0);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLuint v0, GLuint v1)
	{
		glUniform2ui(glGetUniformLocation(program, name), v0, v1);
	}

	void AbstractShader::SetUniform(GLint location, GLuint v0, GLuint v1)
	{
		glUniform2ui(location, v0, v1);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLuint v0, GLuint v1, GLuint v2)
	{
		glUniform3ui(glGetUniformLocation(program, name), v0, v1, v2);
	}

	void AbstractShader::SetUniform(GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		glUniform3ui(location, v0, v1, v2);
	}

	void AbstractShader::SetUniform(const GLchar* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		glUniform4ui(glGetUniformLocation(program, name), v0, v1, v2, v3);
	}

	void AbstractShader::SetUniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		glUniform4ui(location, v0, v1, v2, v3);
	}

	void AbstractShader::SetUniform(const GLchar* name, const Color* v0, bool ignoreAlpha)
	{
		SetUniform(glGetUniformLocation(program, name), v0, ignoreAlpha);
	}

	void AbstractShader::SetUniform(GLint location, const Color* v0, bool ignoreAlpha)
	{
		if (ignoreAlpha)
			glUniform3f(location, v0->r, v0->g, v0->b);
		else
			glUniform4f(location, v0->r, v0->g, v0->b, v0->a);
	}

	void AbstractShader::SetUniform1fv(const GLchar* name, GLsizei count, const GLfloat* value)
	{
		glUniform1fv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform1fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform1fv(location, count, value);
	}

	void AbstractShader::SetUniform2fv(const GLchar* name, GLsizei count, const GLfloat* value)
	{
		glUniform2fv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform2fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform2fv(location, count, value);
	}

	void AbstractShader::SetUniform3fv(const GLchar* name, GLsizei count, const GLfloat* value)
	{
		glUniform3fv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform3fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform3fv(location, count, value);
	}

	void AbstractShader::SetUniform4fv(const GLchar* name, GLsizei count, const GLfloat* value)
	{
		glUniform4fv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform4fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform4fv(location, count, value);
	}

	void AbstractShader::SetUniform1iv(const GLchar* name, GLsizei count, const GLint* value)
	{
		glUniform1iv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform1iv(GLint location, GLsizei count, const GLint* value)
	{
		glUniform1iv(location, count, value);
	}

	void AbstractShader::SetUniform2iv(const GLchar* name, GLsizei count, const GLint* value)
	{
		glUniform2iv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform2iv(GLint location, GLsizei count, const GLint* value)
	{
		glUniform2iv(location, count, value);
	}

	void AbstractShader::SetUniform3iv(const GLchar* name, GLsizei count, const GLint* value)
	{
		glUniform3iv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform3iv(GLint location, GLsizei count, const GLint* value)
	{
		glUniform3iv(location, count, value);
	}

	void AbstractShader::SetUniform4iv(const GLchar* name, GLsizei count, const GLint* value)
	{
		glUniform4iv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform4iv(GLint location, GLsizei count, const GLint* value)
	{
		glUniform4iv(location, count, value);
	}

	void AbstractShader::SetUniform1uiv(const GLchar* name, GLsizei count, const GLuint* value)
	{
		glUniform1uiv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform1uiv(GLint location, GLsizei count, const GLuint* value)
	{
		glUniform1uiv(location, count, value);
	}

	void AbstractShader::SetUniform2uiv(const GLchar* name, GLsizei count, const GLuint* value)
	{
		glUniform2uiv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform2uiv(GLint location, GLsizei count, const GLuint* value)
	{
		glUniform2uiv(location, count, value);
	}

	void AbstractShader::SetUniform3uiv(const GLchar* name, GLsizei count, const GLuint* value)
	{
		glUniform3uiv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform3uiv(GLint location, GLsizei count, const GLuint* value)
	{
		glUniform3uiv(location, count, value);
	}

	void AbstractShader::SetUniform4uiv(const GLchar* name, GLsizei count, const GLuint* value)
	{
		glUniform4uiv(glGetUniformLocation(program, name), count, value);
	}

	void AbstractShader::SetUniform4uiv(GLint location, GLsizei count, const GLuint* value)
	{
		glUniform4uiv(location, count, value);
	}

	void AbstractShader::SetUniformMatrix2fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix2fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix2fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix3fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix3fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix3fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix2x3fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix2x3fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix3x2fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix3x2fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix2x4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix2x4fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix4x2fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4x2fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix3x4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix3x4fv(location, count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix4x3fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(program, name), count, transpose, value);
	}

	void AbstractShader::SetUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4x3fv(location, count, transpose, value);
	}
#pragma endregion Uniforms

	void AbstractShader::LoadShaderSource(const char* filename, char** buffer)
	{
		std::ifstream file(filename);
		if (!file.good())
		{
			file.close();
			throw std::exception(std::string("Failed to open shader file: " + std::string(filename)).c_str());
		}

		std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		(*buffer) = (char*)malloc(str.size() + 1);
		memcpy(*buffer, str.c_str(), str.size());
		(*buffer)[str.size()] = '\x00';
	}
}