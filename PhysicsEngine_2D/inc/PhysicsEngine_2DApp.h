#pragma once

#include "Application.h"
#include "Renderer2D.h"

namespace physics {
	class Scene;
	class MouseController;
}

class PhysicsEngine_2DApp : public aie::Application {
public:

	PhysicsEngine_2DApp();
	virtual ~PhysicsEngine_2DApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*			m_2dRenderer;
	aie::Font*					m_font;

	physics::Scene				*m_scene = nullptr;
	physics::MouseController	*m_mouseController = nullptr;
};