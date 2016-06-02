#pragma once
#include "Dependencies\glm\glm.hpp"



class Vertex{
	

public:

	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
	Vertex(glm::vec3 position, glm::vec3 color);
	Vertex(glm::vec3 position, glm::vec2 texture);
	Vertex(){}
	~Vertex();
};