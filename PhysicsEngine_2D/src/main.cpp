#include "PhysicsEngine_2DApp.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

#include <GLFW\glfw3.h>

#include <ini\GlobalConfig.h>

int main() {
	srand(time(NULL));

	// Check for any memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	///OpenGL
	// initialise GLFW so we can tweak some OpenGL settings
	glfwInit();
	// disable the window resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//==========================================================


	/// Configuration
	// Load settings in from config file

	system("mkdir config"); // Ensure configuration file directory exists

	GlobalConfig::create("config/settings.ini");
	ini_t *ini = GlobalConfig::getInstance();
	ini->save();

	ini->select("DisplayOptions");

	std::string title = ini->get("WindowTitle");
	int ScreenWidth = ini->get("WindowWidth", int());
	int ScreenHeight = ini->get("WindowHeight", int());
	bool fullscreen = ini->get("Fullscreen", bool());


	// allocation
	auto app = new PhysicsEngine_2DApp();

	// initialise and loop
	app->run(title.c_str(), ScreenWidth, ScreenHeight, fullscreen);

	// deallocation
	delete app;
	GlobalConfig::destroy();

	return 0;
}