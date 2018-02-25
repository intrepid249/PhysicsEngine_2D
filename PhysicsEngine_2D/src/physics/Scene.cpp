#include "physics\Scene.h"
#include "physics\Object.h"

#include "ini\GlobalConfig.h"

using namespace physics;

Scene::Scene()
{
	// Set a default gravity
	m_gravity = glm::vec2(0.0f, -9.8f);

	// Default for fixed time 100fps
	m_fixedTimeStep = 0.01f;
	m_accumulatedTime = 0.0f;
}

Scene::~Scene()
{
	// Delete all objects
	for (auto object : m_objects) {
		delete object;
	}
}

void Scene::update(float deltaTime)
{
	m_accumulatedTime += deltaTime;

	// Using fixed time step for update
	while (m_accumulatedTime >= m_fixedTimeStep)
	{
		applyGravity();
		for (auto object : m_objects) {
			object->update(m_fixedTimeStep);
		}

		m_accumulatedTime -= m_fixedTimeStep;
		detectCollisions();
		resolveCollisions();
		cleanup();
	}
}

void Scene::draw()
{
	for (auto object : m_objects) {
		object->draw();
	}
}

void physics::Scene::draw(aie::Renderer2D * renderer)
{
	for (auto object : m_objects) {
		object->draw(renderer);
	}
}

void physics::Scene::setGravity(const glm::vec2 & gravity)
{
	m_gravity = gravity;
}

void physics::Scene::setGravity(const float x, const float y)
{
	m_gravity = glm::vec2(x, y);
}

const glm::vec2 & physics::Scene::getGravity()
{
	return m_gravity;
}

void physics::Scene::setGlobalForce(const glm::vec2 & gForce)
{
	m_globalForce = gForce;
}

void physics::Scene::setGlobalForce(const float x, const float y)
{
	m_globalForce = glm::vec2(x, y);
}

const glm::vec2 & physics::Scene::getGlobalForce()
{
	return m_globalForce;
}

void Scene::addObject(Object *object)
{
	m_objects.push_back(object);
}

void Scene::removeObject(Object *object)
{
	// Find the location of the object in the vector
	auto iter = std::find(m_objects.begin(), m_objects.end(), object);
	// Erase it if we found it
	if (iter != m_objects.end()) {
		m_objects.erase(iter);
	}
	delete object;
}

void Scene::applyGlobalForce()
{
	for (auto object : m_objects) {
		object->applyForce(m_globalForce);
	}
}

void Scene::applyGravity()
{
	for (auto object : m_objects) {
		// Since gravity applies force based on mass, we
		// multiply gravity by the object's mass
		object->applyForce(m_gravity * object->getMass());
	}
}

#include <iostream>
void physics::Scene::cleanup()
{
	ini_t *ini = GlobalConfig::getInstance();
	int screenWidth = ini->get("DisplayOptions", "WindowWidth", int());
	int screenHeight = ini->get("DisplayOptions", "WindowHeight", int());

	for (auto object : m_objects) {
		// Give a "200px" border outside field of view
		if (object->getPosition().x < -200 || object->getPosition().x > screenWidth + 200 ||
			object->getPosition().y < -200 || object->getPosition().y > screenHeight + 200) 
		{
			std::cout << "Object destroyed";
			removeObject(object);
		}
	}
}

void Scene::detectCollisions()
{
	// Find all the collisions and place them into the vector
	for (auto object = m_objects.begin(); object != m_objects.end(); object++)
	{
		// The second loop only checks objects after the first int the array
		for (auto object2 = object + 1; object2 != m_objects.end(); object2++)
		{
			if ((*object)->isColliding(*object2)) {
				Collision tempCollision;
				tempCollision.objA = *object;
				tempCollision.objB = *object2;
				m_collisions.push_back(tempCollision);
			}
		}
	}
}

void Scene::resolveCollisions()
{
	for (auto col : m_collisions) {
		// Create a normalised collision vector between the two shapes
		glm::vec2 collisionNormal = glm::normalize(col.objB->getPosition() - col.objA->getPosition());

		glm::vec2 relativeVelocity = col.objB->getVelocity() - col.objA->getVelocity();

		// Put together the impulse forces and calculate elasticity
		float avgElasticity = 0.8;
		float impulseScale = glm::dot(-(1 + avgElasticity) * relativeVelocity, collisionNormal) / glm::dot(collisionNormal, collisionNormal * ((1 / col.objA->getMass()) + (1 / col.objB->getMass())));
		
		// Apply the impulse forces without multiplying by delta time
		col.objA->applyImpulse(-collisionNormal * impulseScale);
		col.objB->applyImpulse(collisionNormal * impulseScale);
	}
	m_collisions.clear();
}