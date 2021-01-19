#ifndef OPENGLU_HPP
#define OPENGLU_HPP

#include "core.hpp"
#include <glad/glad.h>

#include "color.hpp"
#include "object.hpp"

namespace oglu
{
	OGLU_API void LoadGLLoader(GLADloadproc proc);

	// Some raw, exposed OpenGL until I know where to put then
	OGLU_API void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);
	OGLU_API void ClearScreen(GLbitfield mask, Color clearColor);
}

#endif //OPENGLU_HPP
