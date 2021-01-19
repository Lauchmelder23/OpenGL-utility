#ifndef SHADER_HPP
#define SHADER_HPP

#include <core.hpp>
#include <glad/glad.h>

namespace oglu
{
	class OGLU_API Shader
	{
	public:
		Shader(const char* vertexShaderFile, const char* fragmentShaderFile);

	private:
		void LoadShaderSource(const char* filename, char** buffer);

	private:
		GLuint vertexShader, fragmentShader;
	};
}

#endif