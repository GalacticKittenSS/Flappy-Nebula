#pragma once

#include <Nebula.h>

class Colour {
public:
	void Update();
	Nebula::vec3 GetRGB() { return { red, green, blue }; }
private:
	float hue = 0.0f;
	float red = 1.0f, green = 0.0f, blue = 0.0f;

	float hueSpeed = 3.5f;
};