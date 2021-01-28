#version 330 core
struct Material 
{
	vec3 ambient, diffuse, specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient, diffuse, specular;
	float ambientStrength;
};

in vec2 oUV;
in vec3 oNormal;
in vec3 oFragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
	// Ambient light
	vec3 ambient = light.ambient * light.ambientStrength * material.ambient;

	vec3 norm = normalize(oNormal);
	// Diffuse light
	vec3 lightDir = normalize(light.position - oFragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	// Specular light
	vec3 viewDir = normalize(viewPos - oFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * light.specular;

	vec4 objColor = mix(texture(texture1, oUV), texture(texture2, oUV), 0.2);

	FragColor = vec4(ambient + diffuse + specular, 1.0) * objColor;
}