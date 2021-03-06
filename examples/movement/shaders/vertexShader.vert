#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec2 oUV;
out vec3 oNormal;
out vec3 oFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;

void main()
{
	oUV = aUV;
	oNormal = normal * aNormal;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	oFragPos = vec3(model * vec4(aPos, 1.0));
}