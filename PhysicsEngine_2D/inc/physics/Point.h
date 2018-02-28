#pragma once
#include "physics\Object.h"

namespace physics {
	class Point : public Object
	{
	public:
		Point(ShapeType shape, glm::vec2 position);
		virtual ~Point();
	};
}
