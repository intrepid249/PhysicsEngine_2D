#pragma once
#include "Object.h"

namespace physics {
	class Circle : public Object
	{
	public:
		Circle(ShapeType shape, glm::vec2 position, float radius, float mass, glm::vec4 color, bool isStatic);
		virtual ~Circle();

		void draw();
		void draw(aie::Renderer2D *renderer);

		void setRadius(const float radius);
		float getRadius();

	protected:
		float m_radius;
	};
}
