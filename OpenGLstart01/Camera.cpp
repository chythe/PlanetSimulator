#include "Camera.h"

Camera::Camera(){
	/*
		vector indicating forward direction
	*/
	directionVector = glm::vec3(0.0f, 0.0f, 1.0f);  
	/*
		vector indicating right direction
	*/
	rightVector = glm::vec3(1.0f, 0.0f, 0.0f);  
	/*
		vector indicating up direction 
		vector with size given by the product of two vectors: directionVector and rightVector
	*/
	upVector = glm::cross(rightVector, directionVector);  
	/*
		Means tha translaction vector which move the camera to the right position
	*/
	position = glm::vec3(0.0f,0.0f,0.0f);  // wektor translacji który przesunie kamerê w odpowiednie miejsce
	/*
		View Matrix 
	*/
	viewMatrix = glm::lookAt(position, position + directionVector, upVector);//definicja macierzy kamery - widoku

	/*
		Perspective Matrix
	*/
	perspectiveMatrix = glm::perspective(glm::radians(67.0f), (float)800 / (float)600, 0.1f, 1000.0f);   
}
Camera::~Camera(){

}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

void Camera::update(){
	viewMatrix = glm::lookAt(position, position + directionVector, upVector);
}

glm::mat4 Camera::getPerspectiveMatrix(){
	return perspectiveMatrix;
}

void Camera::setPositionByDirection(float value){
	position += directionVector*value;
}

void Camera::setPositionByRightVector(float value){
	position += rightVector*value;
}
void Camera::setDirectionVector(glm::vec3 value){
	directionVector = value;
}

void Camera::setRightVector(glm::vec3 value){
	rightVector = value;
}

void Camera::updateUpVector(){
	upVector=glm::cross(rightVector, directionVector);
}