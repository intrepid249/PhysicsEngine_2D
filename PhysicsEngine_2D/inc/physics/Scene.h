#pragma once
#include <vector>
#include <glm\glm.hpp>

#include "physics\Collision.hpp"

namespace aie {
	class Renderer2D;
}

namespace physics {
	class Object;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);
		void draw();
		void draw(aie::Renderer2D *renderer);

		void setGravity(const glm::vec2 &gravity);
		void setGravity(const float x, const float y);
		const glm::vec2 &getGravity();

		void setGlobalForce(const glm::vec2 &gForce);
		void setGlobalForce(const float x, const float y);
		const glm::vec2 &getGlobalForce();

		void addObject(Object *object);
		void removeObject(Object *object);

		void applyGlobalForce();

	protected:
		std::vector<Object*> m_objects;
		glm::vec2 m_gravity;
		glm::vec2 m_globalForce;

		std::vector<Collision> m_collisions;

		float m_fixedTimeStep;
		float m_accumulatedTime;

	private:
		void applyGravity();
		void cleanup();
		void detectCollisions();
		void resolveCollisions();
	};
}