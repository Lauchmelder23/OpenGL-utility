#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <core.hpp>

namespace oglu
{
	void ActiveTexture(GLubyte index);

	class OGLU_API AbstractTexture
	{
	public:
		AbstractTexture(const AbstractTexture& other);
		~AbstractTexture();

		friend std::shared_ptr<AbstractTexture> OGLU_API MakeTexture(const char* filename);

		void Bind();
		void Unbind();

	private:
		AbstractTexture(const char* filename);

	private:
		int width, height, nrChannels;
		GLuint texture;
	};

	typedef std::shared_ptr<AbstractTexture> Texture;
}

#endif