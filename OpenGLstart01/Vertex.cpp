#include "Vertex.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 color){
	
	this->position = position;
	this->color = color;

	
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texture){

	this->texture = texture;
	this->position = position;
}

Vertex::~Vertex(){}