#include "physics\MouseController.h"
#include "physics\Circle.h"
#include "physics\Scene.h"

#include "physics\ColorUtils.h"

#include <Renderer2D.h>
#include <Input.h>

using namespace physics;

MouseController::MouseController()
{
	m_selectedShape = CIRCLE;
}


MouseController::~MouseController()
{
}

void MouseController::update(float deltaTime)
{
	updateControls();
}

void MouseController::draw(aie::Renderer2D * renderer)
{
#ifdef _DEBUG // Only show this if we are running in debug mode
	if (showLine) {
		renderer->setRenderColour(0xFF0000FF);
		renderer->drawLine(startMouse.x, startMouse.y, deltaMouse.x, deltaMouse.y);
		renderer->setRenderColour(0xFFFFFFFF);
	}
#endif
}

void MouseController::setActiveScene(physics::Scene * scene)
{
	m_activeScene = scene;
}

void MouseController::updateControls()
{
	aie::Input *input = aie::Input::getInstance();

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		showLine = true;

		// Calculate a slingshot.
		int mX, mY;
		input->getMouseXY(&mX, &mY);

		if (doOnce) {
			startMouse = glm::vec2(mX, mY);
			doOnce = false;
		}

		deltaMouse = glm::vec2(mX, mY);
	}

	if (input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		showLine = false;

		// Reset the doOnce for future mouse clicks
		doOnce = true;

		// Create a ball when the mouse is released, and apply a force calculated from deltaMouse - startMouse
		switch (m_selectedShape)
		{
		case CIRCLE:
			int minRadius = 15, maxRadius = 75;
			float radius = (rand() % maxRadius) + minRadius;

			// Scale the mass according to the size
			float mass = radius * 0.5;

			Circle *c = new physics::Circle(physics::CIRCLE, startMouse, radius, mass, getRandomColor(), false);

			// Pick a random angle and convert the polar coordinates to cartesian to push the object in a random direction
			float angle = atan2f(startMouse.y - deltaMouse.y, startMouse.x - deltaMouse.x);

			float magnitude = glm::distance(startMouse, deltaMouse) * 50;

			glm::vec2 force = glm::vec2(magnitude * cosf(angle), magnitude * sinf(angle));

			c->applyImpulse(force);
			m_activeScene->addObject(c);

			break;
		}
	}

	// Create a new static shape where the mouse button is clicked
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		// TODO: Drag the mouse to size and scale the mass according to size
		glm::vec2 startPos;
		int startX, startY;
		input->getMouseXY(&startX, &startY);
		startPos = glm::vec2(startX, startY);

		switch (m_selectedShape)
		{
		case physics::CIRCLE:
			int minRadius = 15, maxRadius = 75;
			float radius = (rand() % maxRadius) + minRadius;

			// Scale the mass according to the size
			float mass = radius * 0.5;

			physics::Circle *c = new physics::Circle(physics::CIRCLE, startPos, radius, mass, getRandomColor(), true);

			m_activeScene->addObject(c);

			break;
		}
	}
}
