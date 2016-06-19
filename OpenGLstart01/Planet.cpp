#include "Planet.h"
#include <cmath>

Planet::Planet(const Model*model, Shader * shader){
	this->model = model;
	this->shader = shader;
	transform.setPosition(glm::vec3(0, 0, 0));
	transform.update();
}

void Planet::draw(){
	model->draw();
}
Transform & Planet::getTransform(){
	return transform;
}

void Planet::updateShader(Camera&camera){
	shader->Update(&transform, &camera);
}

void Planet::updateLightningInShader(){
	shader->updateLightning(objectAmbientFactor, objectDiffuseFactor, objectSpecularFactor);
}

Shader& Planet::getShader(){
	return *shader;
}


MovementParameters & Planet::getMovementParameters(){
    return movementParameters;
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

void Planet::setStartingParameters(double vStart, double startingAngle, double startingHigh, double radius, glm::vec3 rotation){
	movementParameters.setStartingParameters(vStart, startingAngle, startingHigh, radius, rotation);
}

void Planet::calculateNewCoordinates(){
	movementParameters.calculateNewCoordinates();
}

void Planet::setTransform(){
	transform.setRotation(movementParameters.currentRotation);
	transform.setPosition(movementParameters.positionToDraw);
}

void Planet::setLightningParameters(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor){
	this->objectAmbientFactor = objectAmbientFactor;
	this->objectDiffuseFactor = objectDiffuseFactor;
	this->objectSpecularFactor = objectSpecularFactor;
}

bool Planet::collision(Planet * planet){
    if (planet != NULL)
    {
        double dx = this->getMovementParameters().positionToDraw.x - planet->getMovementParameters().positionToDraw.x;
        double dy = this->getMovementParameters().positionToDraw.y - planet->getMovementParameters().positionToDraw.y;
        double dz = this->getMovementParameters().positionToDraw.z - planet->getMovementParameters().positionToDraw.z;
        double distance = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
        if (distance <= this->getMovementParameters().radius + planet->getMovementParameters().radius)
            return true;
    }
    return false;
}