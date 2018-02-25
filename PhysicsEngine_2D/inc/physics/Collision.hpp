#pragma once
#include <glm\glm.hpp>

namespace physics 
{
	class Object;

	struct Collision
	{
		Object *objA;
		Object *objB;

		float penetration;
		glm::vec2 normal;
	};
}