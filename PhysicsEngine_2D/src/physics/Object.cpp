#include "physics\Object.h"
#include "physics\Circle.h"

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

bool Object::isColliding(Object * other)
{
	switch (m_shape)
	{
	case CIRCLE:
		switch (other->getShapeType())
		{
		case CIRCLE:
			return isCollidingCirCir((Circle*)this, (Circle*)other);
			break;
		case PLANE:
			break;
		case AABB:
			break;
		}
		break;

	case PLANE:
		switch (other->getShapeType())
		{
		case CIRCLE:
			break;
		case PLANE:
			// Left blank because planes will never collide with other planes?
			break;
		case AABB:
			break;
		}
		break;

	case AABB:
		switch (other->getShapeType())
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

const ShapeType physics::Object::getShapeType()
{
	return m_shape;
}

const bool Object::isStatic()
{
	return m_isStatic;
}

#pragma endregion

bool physics::Object::isCollidingCirCir(Circle *objA, Circle * objB)
{
	// Assumptions are being made that these are both circles
	assert(objA != nullptr);
	assert(objB != nullptr);

	// find the distance between centres
	float distance = glm::distance(objA->getPosition(), objB->getPosition());

	// Add the two radii
	float radii = objA->getRadius() + objB->getRadius();

	// Is the distance smaller than the radius length?
	return distance < radii;
}
