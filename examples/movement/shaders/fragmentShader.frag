#version 330 core
struct Material 
{
	vec3 ambient, diffuse, specular;
	float shininess;
};

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

uniform vec3 viewPos;

uniform Material material;

void main()
{
	// Ambient light
	vec3 ambient = ambientColor * ambientStrength * material.ambient;

	vec3 norm = normalize(oNormal);
	// Diffuse light
	vec3 lightDir = normalize(lightPos - oFragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * lightColor;

	// Specular light
	vec3 viewDir = normalize(viewPos - oFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * lightColor;

	vec4 objColor = mix(texture(texture1, oUV), texture(texture2, oUV), 0.2);

	FragColor = vec4(ambient + diffuse + specular, 1.0) * objColor;
}