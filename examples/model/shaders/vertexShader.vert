#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 oNormal;
out vec2 oUV;
out vec3 oFragPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	oNormal = aNormal;
	oUV = aUV;

	gl_Position = projection * view * vec4(aPos, 1.0);
	oFragPos = aPos;
}