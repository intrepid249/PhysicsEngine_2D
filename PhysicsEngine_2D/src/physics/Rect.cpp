#include "physics\Rect.h"

using namespace physics;

Rect::Rect(ShapeType shape, glm::vec2 position, glm::vec2 size, float mass, glm::vec4 color, bool isStatic) : Object(shape, position, mass, color, isStatic)
{
}


Rect::~Rect()
{
}
