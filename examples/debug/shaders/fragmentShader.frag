#version 330 core
in vec3 oCol;

out vec4 FragColor;

uniform vec4 ourColor;

void main()
{
	FragColor = vec4(oCol, 1.0f) + ourColor;
}