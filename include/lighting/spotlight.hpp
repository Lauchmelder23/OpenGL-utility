#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include <core.hpp>
#include <glm/glm.hpp>

#include <lighting/point.hpp>

namespace oglu
{
	class OGLU_API SpotLight : public PointLight
	{
	public:
		SpotLight();
		SpotLight(const glm::vec3& position, const glm::vec3& direction, float angle, const Color& diffusionColor = Color::White, const Color& specularColor = Color::White);
		SpotLight(const SpotLight& other);

		float angle;
		float outerAngle;
		glm::vec3 direction;

	private:
		
	};
}

#endif