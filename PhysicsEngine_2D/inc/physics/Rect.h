#pragma once
#include "Object.h"

namespace physics {
	class Rect : public Object
	{
	public:
		Rect(ShapeType shape, glm::vec2 position, glm::vec2 size, float mass, glm::vec4 color, bool isStatic);
		virtual ~Rect();
	};
}
