#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 oUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	oUV = aUV;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}