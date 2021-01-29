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

struct Flashlight
{
	vec3 position, direction;
	float angle, outerAngle;
	vec3 diffuse, specular;

	float constant, linear, quadratic;
};

in vec2 oUV;
in vec3 oNormal;
in vec3 oFragPos;

out vec4 FragColor;

uniform vec3 viewPos;

uniform Material material;
uniform Light pointLight;
uniform Flashlight fl;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(Flashlight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 viewDir = normalize(viewPos - oFragPos);

	vec3 finalColor = vec3(0.0);
	finalColor += CalcPointLight(pointLight, oNormal, oFragPos, viewDir);
	finalColor += CalcSpotLight(fl, oNormal, oFragPos, viewDir);

	FragColor = vec4(finalColor, 1.0);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	vec3 ambient = light.ambient * light.ambientStrength * vec3(texture(material.diffuse, oUV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oUV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, oUV));

	return (ambient + (diffuse + specular) * attenuation);
}

vec3 CalcSpotLight(Flashlight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float theta = dot(lightDir, -normalize(light.direction));
	float epsilon = light.angle - light.outerAngle;
	float intensity = clamp((theta - light.outerAngle) / epsilon, 0.0, 1.0);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, oUV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, oUV));

	return ((diffuse + specular) * attenuation * intensity);
}