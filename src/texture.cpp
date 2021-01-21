#include "texture.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <exception>

namespace oglu
{
	void ActiveTexture(GLubyte index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
	}

	AbstractTexture::AbstractTexture(const AbstractTexture& other) :
		width(other.width), height(other.height), nrChannels(other.nrChannels), texture(other.texture)
	{
		
	}

	AbstractTexture::~AbstractTexture()
	{
		glDeleteBuffers(1, &texture);
	}

	AbstractTexture::AbstractTexture(const char* filename)
	{
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(filename, &width, &height, &nrChannels, 0);
		if (data == nullptr)
		{
			std::string err = std::string(stbi_failure_reason());
			throw std::runtime_error(err);
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLenum pixelFormat;
		switch (nrChannels)
		{
		case 3: pixelFormat = GL_RGB; break;
		case 4:	pixelFormat = GL_RGBA; break;
		default:
			glDeleteTextures(1, &texture);
			stbi_image_free(data);
			throw std::runtime_error(std::string("Texture has unsupported pixel format: " + std::string(filename)));
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	Texture MakeTexture(const char* filename)
	{
		return std::shared_ptr<AbstractTexture>(new AbstractTexture(filename));
	}

	void AbstractTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void AbstractTexture::BindAs(GLbyte index)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void AbstractTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
