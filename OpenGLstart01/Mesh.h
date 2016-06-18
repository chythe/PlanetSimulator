#pragma once 
#include "Dependencies\glew\glew.h"
#include "VerticesGroup.h"


// DEPRECATED
class Mesh{
	unsigned int verticesCount;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint vertexArray;
	GLuint textureCoordinationsBuffer;
	VERTICES_TYPE verticesType;

public:
	Mesh(VerticesGroup verticesGroup);
	~Mesh();

	void draw();

};