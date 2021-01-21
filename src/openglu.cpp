#include "openglu.hpp"

#include <iostream>
#include <exception>

namespace oglu
{
	void LoadGLLoader(GLADloadproc proc)
	{
		if (!gladLoadGLLoader(proc))
		{
			throw std::runtime_error("Failed to initialize GLAD");
		}
	}

	void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glViewport(x, y, width, height);
	}

	void ClearScreen(GLbitfield mask, Color clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(mask);
	}
}
