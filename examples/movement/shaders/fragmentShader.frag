#version 330 core
in vec2 oUV;
in vec3 oNormal;
in vec3 oFragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float ambientStrength;
uniform vec3 ambientColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	vec3 ambient = ambientColor * ambientStrength;
	vec3 norm = normalize(oNormal);
	vec3 lightDir = normalize(lightPos - oFragPos);

	float diff = max(dot(norm, lightDir), 0.0) * 2.0;
	diff *= min(1.0 / pow(length(lightPos - oFragPos), 2), 2.0);
	
	vec3 diffuse = diff * lightColor;

	vec4 objColor = mix(texture(texture1, oUV), texture(texture2, oUV), 0.2);

	FragColor = vec4(ambient + diffuse, 1.0) * objColor;
}