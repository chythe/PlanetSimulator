#pragma once
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\transform.hpp"


/*
	Camera handler
	Allows to set position and direction
*/
class Camera{
	glm::mat4 viewMatrix;
	glm::mat4 perspectiveMatrix;
	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 directionVector;
	glm::vec3 position;


public:
	/*
		Acualize the view Matrix
	*/
	void update(); 
	void setPositionByDirection(float value);
	void setPositionByRightVector(float value);
	void setDirectionVector(glm::vec3 value);
	void setUpVector();
	void setRightVector(glm::vec3 value);
	/*
		Update the up vector as a cross product of two vectors: directionVector and rightVector
	*/
	void updateUpVector();
	glm::mat4 getViewMatrix();
	glm::mat4 getPerspectiveMatrix();
	/*
		View Matrix and Perspective Matrix are creates with default values
		Performing the update before using Camera object (after its creation) is not obligatory
	*/
	Camera();   
	~Camera();
};