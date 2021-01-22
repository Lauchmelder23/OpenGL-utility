#version 330 core
in vec2 oUV;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, oUV), texture(texture2, oUV), 0.2);
}