#pragma once
#include "Dependencies\glm\glm.hpp"
#include  "Dependencies\glm\gtx\transform.hpp"

class Transform{
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	
    glm::vec3 normalize(const glm::vec3);
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	glm::mat4 getModelMatrix();
    /*
        Returns the matrix which is one part of rotation matrix
        Which part it is depends on axis argument
    */
    glm::mat4 rotate(float rotation, glm::vec3 axis);
    /*
        Multiple matrix 4x4
    */
    glm::mat4 multipleMatrix(const glm::mat4 & m1, const glm::mat4 & m2);
    
    glm::mat4 translate(glm::vec3 position);
	void update();// nie zmienia nic w shaderze, jedynie tworzy modelMatrix Trzeba zrobiæ update przed pierwsztm u¿yciem, bo w konstruktorze jest tylko inicjacja parametrów,	
				  // nie towrzy siê modelMatrix
					
	
	
	
	Transform();  // inicjalizacja podstawowych parametrów, modelMatrix nie jest tworzony 
	~Transform();
};