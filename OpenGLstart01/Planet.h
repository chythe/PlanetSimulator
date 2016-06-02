#pragma once
#include "Model.h"
#include "MovementParameters.h"

class Planet{

protected:
	/*
		Transformation (position, rotation etc..) handler
	*/
	Transform transform;
	
	/*
		Pointer to Model
		It is assigned, memory is not allocated in this class
	*/
	const Model * model;
	
	/*
		Pointer to Shader
		It is assigned, memory is not allocated in this class
	*/
	Shader * shader;

	/*
		Movement Parameter - describes all phisics values and calculate them during the movement
	*/
	MovementParameters movementParameters;

	

public:

	/*
	Variables referenced to lightning, maybe it should be another class
	*/
	glm::vec3 objectAmbientFactor;
	glm::vec3 objectDiffuseFactor;
	glm::vec3 objectSpecularFactor;

	Planet(const Model * model, Shader * shader);
	Transform & getTransform();
	
	/*	
	 * Updates transform, updates shader, draw model
	 */
	void drawComplex(Camera&camera);
	
	/*
		Just model->draw()
	*/
	void draw();
	
	/*
		movementParameters -> setStartingParameters()
	*/
	void setStartingParameters(double vStart, double startingAngle, double startingHigh,glm::vec3 rotation);

	/*
		movementParameters->calculateNewCoordinates()
	*/
	void calculateNewCoordinates();

	/*
		this function should be call after calculateNewCoordinates to set the new coordinates 
	*/
	void setTransform();
	void updateShader(Camera & camera);

	/*
		Function for set the variables responsible for lightning
	*/
	void setLightningParameters(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor);

	void updateLightningInShader();
	Shader & getShader();
};
