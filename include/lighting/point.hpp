#ifndef POINT_HPP
#define POINT_HPP

#include <core.hpp>
#include <color.hpp>
#include <glm/glm.hpp>

namespace oglu
{
	class Transformable;

	class OGLU_API PointLight
	{
	public:
		PointLight();
		PointLight(const glm::vec3& position, const Color& color);
		PointLight(const PointLight& other);

		~PointLight();

		void LinkPositionToTransformable(Transformable& link);
		void UnlinkPositionFromTransformable();
		float* GetPositionPointer();

	public:
		Color color;


	private:
		glm::vec3* position;
		bool isLinked;
	};
}

#endif