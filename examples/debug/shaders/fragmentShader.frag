#version 330 core
in vec3 oCol;
in vec2 oUV;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, oUV) * vec4(oCol, 1.0);
}