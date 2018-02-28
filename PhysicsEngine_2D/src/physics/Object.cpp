#include "physics\Object.h"
#include "physics\Circle.h"
#include "physics\Plane.h"

using namespace physics;

Object::Object(ShapeType shape, glm::vec2 position, float mass, glm::vec4 color, bool isStatic)
	: m_shape(shape), m_position(position), m_mass(mass), m_color(color), m_isStatic(isStatic)
{
	m_velocity = glm::vec2();
	m_acceleration = glm::vec2();
}

Object::~Object()
{
}

void Object::update(float deltaTime)
{
	if (!m_isStatic)
	{
		applyForce(-m_velocity * m_friction);

		m_velocity += m_acceleration * deltaTime;
		m_position += m_velocity * deltaTime;

		m_acceleration = glm::vec2();
	}
}

void Object::applyForce(const glm::vec2 & force)
{
	// Force = mass * acceleration
	m_acceleration += force / m_mass;
}

void Object::applyImpulse(const glm::vec2 & force)
{
	m_velocity += force / m_mass;
}

bool Object::isColliding(Collision &col)
{
	switch (m_shape)
	{
	case CIRCLE:
		switch (col.objB->getShapeType())
		{
		case CIRCLE:
			return isCollidingCirCir(col);
			break;
		case PLANE:
			return isCollidingCirPlane(col);
			break;
		case AABB:
			break;
		}
		break;

	case PLANE:
		switch (col.objB->getShapeType())
		{
		case CIRCLE:
			return isCollidingCirPlane(col);
			break;
		}

	case AABB:
		switch (col.objB->getShapeType())
		{
		case CIRCLE:
			break;
		case PLANE:
			break;
		case AABB:
			break;
		}
		break;
	}

	// This is a catch for if the objects can't be identified
	return false;
}

#pragma region Getters and Setters

void Object::setPosition(const glm::vec2 & position)
{
	m_position = position;
}

void Object::setPosition(const float x, const float y)
{
	m_position = glm::vec2(x, y);
}

const glm::vec2 & Object::getPosition()
{
	return m_position;
}

void Object::setVelocity(const glm::vec2 & velocity)
{
	m_velocity = velocity;
}

void Object::setVelocity(const float x, const float y)
{
	m_velocity = glm::vec2(x, y);
}

const glm::vec2 & Object::getVelocity()
{
	return m_velocity;
}

void Object::setAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration = acceleration;
}

void Object::setAcceleration(const float x, const float y)
{
	m_acceleration = glm::vec2(x, y);
}

const glm::vec2 & Object::getAcceleration()
{
	return m_acceleration;
}

void Object::setMass(const float mass)
{
	m_mass = mass;
}

const float Object::getMass()
{
	return m_mass;
}

void Object::setFriction(const float friction)
{
	m_friction = friction;
}

const float physics::Object::getFriction()
{
	return m_friction;
}

void Object::setElasticity(const float elasticity)
{
	m_elasticity = elasticity;
}

const float Object::getElasticity()
{
	return m_elasticity;
}

const ShapeType physics::Object::getShapeType()
{
	return m_shape;
}

const bool Object::isStatic()
{
	return m_isStatic;
}

#pragma endregion

bool physics::Object::isCollidingCirCir(Collision &col)
{
	// Assumptions are being made that these are both circles
	assert(col.objA != nullptr);
	assert(col.objB != nullptr);

	// find the distance between centres
	float distance = glm::distance(col.objA->getPosition(), col.objB->getPosition());

	// Add the two radii
	float radii = ((physics::Circle*)col.objA)->getRadius() + ((physics::Circle*)col.objB)->getRadius();

	col.normal = glm::normalize(col.objB->getPosition() - col.objA->getPosition());

	col.penetration = radii - distance;

	// Is the distance smaller than the radius length?
	return distance < radii;
}

bool physics::Object::isCollidingCirPlane(Collision & col)
{
	physics::Circle *obj = nullptr;
	physics::Plane *other = nullptr;

	if (col.objA->getShapeType() == CIRCLE) {
		 obj = (physics::Circle*)col.objA;
		 other = (physics::Plane*)col.objB;
	}
	else {
		obj = (physics::Circle*)col.objB;
		other = (physics::Plane*)col.objA;
	}

	glm::vec2 c = obj->getPosition(); // get the centre position of the circle
	glm::vec2 p;

	col.normal = other->getNormal();

	// Calculate the closest point on the plane
	if (other->getNormal().x != 0) // x-aligned axis
		p = glm::vec2(other->getPosition().x, c.y);
	if (other->getNormal().y != 0) // y-aligned axis
		p = glm::vec2(c.x, other->getPosition().y);


	// Calculate object penetration
	col.penetration = obj->getRadius() - glm::distance(c, p);


	if (glm::distance(c, p) < obj->getRadius())
		return true;
	return false;
}
