#version 330 core
struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient, diffuse, specular;
	float ambientStrength;

	float constant, linear, quadratic;
};

in vec2 oUV;
in vec3 oNormal;
in vec3 oFragPos;

out vec4 FragColor;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
	// Ambient light
	vec3 ambient = light.ambient * light.ambientStrength * vec3(texture(material.diffuse, oUV));

	vec3 norm = normalize(oNormal);
	// Diffuse light
	vec3 lightDir = normalize(light.position - oFragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oUV));

	// Specular light
	vec3 viewDir = normalize(viewPos - oFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, oUV));

	float dist = length(light.position - oFragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	FragColor = vec4((ambient + diffuse + specular) * attenuation, 1.0);
}