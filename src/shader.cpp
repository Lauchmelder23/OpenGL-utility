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
		std::cout << "jkskdjks" << std::endl;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		char* source = nullptr;
		LoadShaderSource(vertexShaderFile, &source);
		std::cout << source << std::endl;
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
		std::cout << "dsnskdnksdnk" << std::endl;
		memcpy(*buffer, str.c_str(), str.size());
		std::cout << "diufoisdufo34" << std::endl;
		(*buffer)[str.size()] = '\x00';
	}
}