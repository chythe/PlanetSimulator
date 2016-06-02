#include "Mouse.h"


Mouse::Mouse(){
	horizontalAngle = 0;
	verticalAngle = 0;
}

void Mouse::moveCamera(GLFWwindow * window, Camera & camera, double elapsedTime){

	glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);
	glfwSetCursorPos(window, 800 / 2, 600 / 2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
		float mouseSpeed = 0.5f;
	
		horizontalAngle += mouseSpeed * (float)elapsedTime * float(800 / 2.0 - cursorPositionX);
		verticalAngle += mouseSpeed * (float)elapsedTime *	float(600 / 2.0 - cursorPositionY);
	/*
		if (verticalAngle < -1.57){
			verticalAngle = -1.57;
		}
			
		if (verticalAngle > 1.57){
			verticalAngle = 1.57;
		}*/
			
	
		camera.setDirectionVector(glm::vec3(cos(verticalAngle) * sin(horizontalAngle),sin(verticalAngle),cos(verticalAngle) * cos(horizontalAngle)));
		
		camera.setRightVector(glm::vec3(-cos(horizontalAngle), 0,sin(horizontalAngle)));
		
		camera.updateUpVector();
		
		camera.update();
}