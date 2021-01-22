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

	void Enable(GLenum cap)
	{
		glEnable(cap);
	}

	void Disable(GLenum cap)
	{
		glDisable(cap);
	}

	void Enable(GLenum cap, GLuint index)
	{
		glEnablei(cap, index);
	}

	void Disable(GLenum cap, GLuint index)
	{
		glDisablei(cap, index);
	}

	void PolygonMode(GLenum face, GLenum mode)
	{
		glPolygonMode(face, mode);
	}
}
