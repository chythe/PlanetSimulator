#include "Keyboard.h"

void Keyboard::moveCamera(Camera & camera, GLFWwindow * window, double elapsedTime){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);

	//bool cameraMoved = false;
	float moveSpeed = 15.5f;

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera.setPositionByRightVector((-float(elapsedTime)*moveSpeed));
		camera.update();
		//cameraMoved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera.setPositionByRightVector((float(elapsedTime)*moveSpeed));
		camera.update();
		//cameraMoved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera.setPositionByDirection(float(elapsedTime)*moveSpeed);
		camera.update();
		//cameraMoved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera.setPositionByDirection(-(float(elapsedTime)*moveSpeed));
		camera.update();
		//cameraMoved = true;
	}

	
}


// When a user presses the escape key, we set the WindowShouldClose property to true, 
// closing the application
//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//{
//	glfwSetWindowShouldClose(window, GL_TRUE);
//	return;
//}
//
//float move_speed = 50.0f;
//
//if (key == GLFW_KEY_W){
//	camera.setPositionByDirection(float(elapsedTime)*move_speed);
//	camera.update();
//}
//if (key == GLFW_KEY_S){
//	camera.setPositionByDirection(-(float(elapsedTime)*move_speed));
//	camera.update();
//}
//if (key == GLFW_KEY_A){
//	camera.setPositionByRightVector(-(float(elapsedTime)*move_speed));
//	camera.update();
//}
//if (key == GLFW_KEY_D){
//	camera.setPositionByRightVector(+(float(elapsedTime)*move_speed));
//	camera.update();
//}