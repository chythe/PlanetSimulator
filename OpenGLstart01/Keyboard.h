#pragma once
#include "Camera.h"
#include "Dependencies\glfw\glfw3.h"

class Keyboard{


public:
	void moveCamera(Camera & camera, GLFWwindow * window, double elapsedTime);
};