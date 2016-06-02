#pragma once
#include "Camera.h"
#include "Dependencies\glfw\glfw3.h"
class Mouse{
protected:
	double cursorPositionX;
	double cursorPositionY;
	float horizontalAngle;
	float verticalAngle;
public:
	void moveCamera(GLFWwindow * window, Camera&camera,  double elapsedTime);
	Mouse();
};