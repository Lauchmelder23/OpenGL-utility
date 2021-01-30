#version 330 core
struct Material
{
	sampler2D tex_diffuse1;
	sampler2D tex_specular1;
};

struct SpotLight
{
	vec3 position, direction;
	float angle, outerAngle;
	float constant, linear, quadratic;
};

in vec3 oNormal;
in vec2 oUV;
in vec3 oFragPos;

out vec4 FragColor;

uniform Material material;
uniform SpotLight flashlight;

void main()
{
	vec3 lightDir = normalize(flashlight.position - oFragPos);

	float theta = dot(lightDir, normalize(-flashlight.direction));
	float epsilon = flashlight.angle - flashlight.outerAngle;
	float intensity = clamp((theta - flashlight.outerAngle) / epsilon, 0.0, 1.0);

	float diff = max(dot(oNormal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, oNormal);
	float spec = pow(max(dot(lightDir, reflectDir), 0.0), 32.0);

	float dist = length(flashlight.position - oFragPos);
	float attenuation = 1.0 / (flashlight.constant + flashlight.linear * dist + flashlight.quadratic * dist * dist);

	vec3 diffuse = vec3(1.0) * diff * vec3(texture(material.tex_diffuse1, oUV));
	vec3 specular = vec3(1.0) * spec * vec3(texture(material.tex_specular1, oUV));
	vec3 ambient = vec3(0.1) * vec3(texture(material.tex_diffuse1, oUV));

	FragColor = vec4(ambient + (diffuse + specular) * intensity * attenuation, 1.0);
	// FragColor = vec4(vec3(texture(material.tex_diffuse1, oUV)), 1.0);
}