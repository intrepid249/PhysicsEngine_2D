#pragma once
#include <glm\glm.hpp>

#include "physics\Collision.hpp"

namespace aie {
	class Renderer2D;
}

namespace physics {

	enum ShapeType { CIRCLE, PLANE, AABB };

	class Circle;

	class Object
	{
	protected:
		Object(ShapeType shape, glm::vec2 position, float mass, glm::vec4 color, bool isStatic);

	public:
		virtual ~Object() = 0;

		void update(float deltaTime);
		virtual void draw() = 0;
		virtual void draw(aie::Renderer2D *renderer) = 0;

		void applyForce(const glm::vec2 &force);
		void applyImpulse(const glm::vec2 &force);

		bool isColliding(Collision &col);

		/*GETTERS AND SETTERS*/
		void setPosition(const glm::vec2 &position);
		void setPosition(const float x, const float y);
		const glm::vec2 &getPosition();

		void setVelocity(const glm::vec2 &velocity);
		void setVelocity(const float x, const float y);
		const glm::vec2 &getVelocity();

		void setAcceleration(const glm::vec2 &acceleration);
		void setAcceleration(const float x, const float y);
		const glm::vec2 &getAcceleration();

		void setMass(const float mass);
		const float getMass();

		void setFriction(const float friction);
		const float getFriction();

		void setElasticity(const float elasticity);
		const float getElasticity();

		const ShapeType getShapeType();
		const bool isStatic();

	protected:
		glm::vec2 m_position;
		glm::vec2 m_velocity;
		glm::vec2 m_acceleration;

		ShapeType m_shape;
		glm::vec4 m_color;

		bool m_isStatic;

		float m_mass = 1.0f;
		float m_friction = 0.3f;
		float m_elasticity = 1.0f;

		/*
		* Check if two circles are colliding with each other
		*/
		bool isCollidingCirCir(Collision &col);
		bool isCollidingCirPlane(Collision &col);
	};
}
