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
uniform Light light;
uniform Flashlight fl;

void main()
{
	vec3 lightDir = normalize(fl.position - oFragPos);
	float theta = dot(lightDir, normalize(-fl.direction));
	float epsilon = fl.angle - fl.outerAngle;
	float intensity = clamp((theta - fl.outerAngle) / epsilon, 0.0, 1.0);

	vec3 norm = normalize(oNormal);
	// Diffuse light

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = fl.diffuse * diff * vec3(texture(material.diffuse, oUV));

	// Specular light
	vec3 viewDir = normalize(viewPos - oFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = fl.specular * spec * vec3(texture(material.specular, oUV));

	float dist = length(fl.position - oFragPos);
	float attenuation = 1.0 / (fl.constant + fl.linear * dist + fl.quadratic * (dist * dist));

	// Ambient light
	vec3 ambient = light.ambient * light.ambientStrength * vec3(texture(material.diffuse, oUV));

	FragColor = vec4(ambient + ((diffuse + specular) * attenuation * intensity), 1.0);
}