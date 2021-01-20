#include <shader.hpp>

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

namespace oglu
{
	Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile) :
		vertexShader(0), fragmentShader(0)
	{
		// Load vertex shader
		char* source = nullptr;
		LoadShaderSource(vertexShaderFile, &source);
		
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
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

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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

	Shader::~Shader()
	{
		
	}

	void Shader::Use()
	{
		glUseProgram(program);
	}

	void Shader::LoadShaderSource(const char* filename, char** buffer)
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