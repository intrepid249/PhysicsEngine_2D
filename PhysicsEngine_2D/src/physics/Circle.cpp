#include "physics\Circle.h"
#include <Gizmos.h>
#include <Renderer2D.h>

using namespace physics;

Circle::Circle(ShapeType shape, glm::vec2 position, float radius, float mass, glm::vec4 color, bool isStatic)
	: Object(shape, position, mass, color, isStatic), m_radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::draw()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);
}

void physics::Circle::draw(aie::Renderer2D * renderer)
{
	renderer->setRenderColour(m_color.x, m_color.y, m_color.z, m_color.w);
	renderer->drawCircle(m_position.x, m_position.y, m_radius);
	// Reset the rendering colour
	renderer->setRenderColour(0xFFFFFFFF);
}

void Circle::setRadius(const float radius)
{
	m_radius = radius;
}

float Circle::getRadius()
{
	return m_radius;
}
