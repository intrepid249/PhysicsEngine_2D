#pragma once
#include "Object.h"

namespace physics {
	class Plane : public Object
	{
	public:
		/* Axis aligned plane constructor
		* Only needs to know distance from origin and the axis it is aligned to
		* Axis - Will be the axis the plane's normal is facing
		*	x aligned will be vertical
		*	y aligned will be horizontal
		* positiveNormal - Defines whether the plane is facing in the negative or positive direction*/
		Plane(ShapeType shape, float offset, char axis, glm::vec4 color, bool positiveNormal);
		virtual ~Plane();

		void draw();
		void draw(aie::Renderer2D *renderer);

		const glm::vec2 &getNormal();

	public:
		glm::vec2 m_normal;
	};
}
