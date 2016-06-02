#include "Planet.h"

Planet::Planet(const Model*model, Shader * shader){
	this->model = model;
	this->shader = shader;
	transform.setPosition(glm::vec3(0, 0, 0));
	transform.update();
}

void Planet::draw(){
	model->draw();
}
Transform & Planet:: getTransform(){
	return transform;
}

void Planet::updateShader(Camera&camera){
	shader->Update(&transform, &camera);
}

void Planet::updateLightningInShader(){
	shader->updateLightning(objectAmbientFactor, objectDiffuseFactor, objectSpecularFactor);
}

Shader& Planet:: getShader(){
	return *shader;
}

/*
	If we will use more than one shader program, there should be a line shader->bind();
*/
void Planet::drawComplex(Camera&camera){
	transform.update();
	shader->Update(&transform, &camera);
	shader->updateLightning(objectAmbientFactor, objectDiffuseFactor, objectSpecularFactor);
	model->draw();
}

void Planet::setStartingParameters(double vStart, double startingAngle, double startingHigh,glm::vec3 rotation){
	movementParameters.setStartingParameters(vStart, startingAngle, startingHigh,rotation);
}

void Planet::calculateNewCoordinates(){
	movementParameters.calculateNewCoordinates();
}

void Planet::setTransform(){
	transform.setRotation(movementParameters.currentRotation);
	transform.setPosition(movementParameters.positionToDraw);
}

void Planet:: setLightningParameters(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor){
	this->objectAmbientFactor = objectAmbientFactor;
	this->objectDiffuseFactor = objectDiffuseFactor;
	this->objectSpecularFactor = objectSpecularFactor;
}