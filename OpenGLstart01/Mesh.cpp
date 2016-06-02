#include "Mesh.h"
#include <vector>
#include<iostream>

Mesh::Mesh(VerticesGroup verticesGroup){


	this->verticesType = verticesGroup.getVerticesType();
	this->verticesCount = verticesGroup.getCount();

	std::vector<glm::vec3> verticesPosition;
	
	
	
	if (verticesType==VERTICES_TYPE::texture){
		
		std::vector<glm::vec2> verticesTexture;
		
		for (int i = 0; i < verticesCount; i++){
			verticesPosition.push_back(verticesGroup.getVertices()[i].position);
			verticesTexture.push_back(verticesGroup.getVertices()[i].texture);
		}
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		std::cout << "BUFFER NUMBER: " << vertexBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *verticesCount, &verticesPosition[0], GL_STATIC_DRAW);

		glGenBuffers(1, &textureCoordinationsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureCoordinationsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*verticesCount, &verticesTexture[0], GL_STATIC_DRAW);


	}
	else if (verticesType == VERTICES_TYPE::color){
		
		std::vector<glm::vec3> verticesColor;

		for (int i = 0; i < verticesCount; i++){
			verticesPosition.push_back(verticesGroup.getVertices()[i].position);
			verticesColor.push_back(verticesGroup.getVertices()[i].color);
		}
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		std::cout << "BUFFER NUMBER: " << vertexBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *verticesCount, &verticesPosition[0], GL_STATIC_DRAW);

		glGenBuffers(1, &colorBuffer);
		std::cout << "BUFFER NUMBER: " << colorBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *verticesCount, &verticesColor[0], GL_STATIC_DRAW);
	}
	
	
}

Mesh::~Mesh(){
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &textureCoordinationsBuffer);
	
}

void Mesh::draw(){
	glBindVertexArray(vertexArray);
	
	
	if (verticesType==VERTICES_TYPE::texture){
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, textureCoordinationsBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	else if (verticesType == VERTICES_TYPE::color){
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);   // JAK ZAKOMENTUJE TA LINIJKE, ALBO OSTATNIA LINIJKE Z MAIN TO BLEDU NIE MA !
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glDrawArrays(GL_TRIANGLES, 0, verticesCount);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

