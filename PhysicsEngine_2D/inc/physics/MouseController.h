#pragma once
#include <glm\glm.hpp>

namespace aie {
	class Renderer2D;
}

namespace physics {
	class Scene;
	class Circle;

	class MouseController
	{
	public:
		MouseController();
		~MouseController();

		/** Update members and actions each frame cycle*/
		void update(float deltaTime);

		/** Debugging display for behaviours*/
		void draw(aie::Renderer2D *renderer);

		void setActiveScene(Scene *scene);

	private:
		enum Shape { CIRCLE, PLANE, AABB };

		void updateControls();

		Scene * m_activeScene = nullptr;

		bool doOnce = true;
		bool showLine = false;

		// Select which shape is the active one to generate
		Shape m_selectedShape;

		glm::vec2 startMouse, deltaMouse;
	};
}
