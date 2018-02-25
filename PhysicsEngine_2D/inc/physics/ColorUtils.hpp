#pragma once
#include <glm\glm.hpp>
#include <cstdlib>

namespace physics {
	const glm::vec4 &getRandomColor() {
		// Create a random number between 50 and 255 so the color is not too dark
		// then divide it by 255 to get a float in between 0 and 1
		float g = ((rand() % 255) + 50) / 255.0f;
		float b = ((rand() % 255) + 50) / 255.0f;
		float r = ((rand() % 255) + 50) / 255.0f;
		float a = 1;

		return glm::vec4(r, g, b, a);
	}
}