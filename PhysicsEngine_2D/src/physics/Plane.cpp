#include "physics\Plane.h"
#include "ini\GlobalConfig.h"

#include <Renderer2D.h>

using namespace physics;

Plane::Plane(ShapeType shape, float offset, char axis, glm::vec4 color, bool positiveNormal) : Object(shape, glm::vec2(0, 0), 0, color, true)
{
	// The plane will always be a static object
	switch (axis)
	{
	case 'x': // Vertical line
		m_position = glm::vec2(offset, 0);
		if (positiveNormal)
			m_normal = glm::vec2(1, 0);
		else
			m_normal = glm::vec2(-1, 0);
		break;
	case 'y': // Horizontal line
		m_position = glm::vec2(0, offset);
		if (positiveNormal)
			m_normal = glm::vec2(0, 1);
		else
			m_normal = glm::vec2(0, -1);
		break;
	default:
		break;
	}
}


Plane::~Plane()
{
}

void Plane::draw()
{
}

void Plane::draw(aie::Renderer2D * renderer)
{
	// Draw the plane
	renderer->setRenderColour(m_color.x, m_color.y, m_color.z, m_color.w);
	// Get some screen information
	ini_t *ini = GlobalConfig::getInstance();
	int screenWidth = ini->get("DisplayOptions", "WindowWidth", int());
	int screenHeight = ini->get("DisplayOptions", "WindowHeight", int());

	if (m_normal.x != 0) // x-aligned plane
		renderer->drawLine(m_position.x, -10, m_position.x, screenHeight + 10);
	if (m_normal.y != 0) // y-aligned plane
		renderer->drawLine(-10, m_position.y, screenWidth + 10, m_position.y);

	// Draw the normal
	renderer->setRenderColour(0xFF0000FF);
	float scaleNormal = 10.0f;
	if (m_normal.x != 0) // x-aligned plane
		renderer->drawLine(m_position.x, m_position.y + screenHeight / 2, m_position.x + m_normal.x * scaleNormal, m_position.y + screenHeight / 2);
	if (m_normal.y != 0) // y-aligned plane
		renderer->drawLine(m_position.x + screenWidth / 2, m_position.y, m_position.x + screenWidth / 2, m_position.y + m_normal.y * scaleNormal);

	renderer->setRenderColour(0xFFFFFFFF);
}

const glm::vec2 & Plane::getNormal()
{
	return m_normal;
}
