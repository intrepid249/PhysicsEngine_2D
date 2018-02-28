#include "..\..\inc\physics\Point.h"

using namespace physics;

Point::Point(ShapeType shape, glm::vec2 position) : Object(shape, position, 0, glm::vec4(1, 1, 1, 1), true)
{
}


Point::~Point()
{
}
