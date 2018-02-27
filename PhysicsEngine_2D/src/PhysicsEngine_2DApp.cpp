#include "PhysicsEngine_2DApp.h"

#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include <Gizmos.h>

#include "physics\Circle.h"
#include "physics\Scene.h"

#include "physics\MouseController.h"

#include <glm\ext.hpp>

PhysicsEngine_2DApp::PhysicsEngine_2DApp() {

}

PhysicsEngine_2DApp::~PhysicsEngine_2DApp() {

}

bool PhysicsEngine_2DApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// Initialise the gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000);


	// Crete an instance of the physics scene
	m_scene = new physics::Scene();
	m_scene->setGlobalForce(glm::vec2(1.0f, 0.0f));
	m_scene->setGravity(glm::vec2());


	// Initialise the mouse controller
	m_mouseController = new physics::MouseController();
	m_mouseController->setActiveScene(m_scene);


	// Create a 'Heavy' ball
	physics::Circle *ball = new physics::Circle(physics::CIRCLE, glm::vec2(100, 100), 30, 10, glm::vec4(0.2f, 0.1f, 0.7f, 0.9f), false);
	ball->setVelocity(glm::vec2(300.0f, 0.0f));
	m_scene->addObject(ball);

	// Create a 'Light' ball
	physics::Circle *ball2 = new physics::Circle(physics::CIRCLE, glm::vec2(230, 100), 15, 1, glm::vec4(0.0f, 0.6f, 0.7f, 0.6f), false);
	m_scene->addObject(ball2);

	return true;
}

void PhysicsEngine_2DApp::shutdown() {
	delete m_scene;
	delete m_font;
	delete m_2dRenderer;
	aie::Gizmos::destroy();
}

void PhysicsEngine_2DApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_mouseController->update(deltaTime);

	m_scene->update(deltaTime);
}

void PhysicsEngine_2DApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();


	m_scene->draw(m_2dRenderer);
	m_mouseController->draw(m_2dRenderer);

	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();


	//// GIZMOS
	//m_scene->draw();

	//// Draw all of the gizmos and update perspective based on the screen size
	//aie::Gizmos::draw2D(glm::perspective(glm::radians(45.0f), (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f));
}