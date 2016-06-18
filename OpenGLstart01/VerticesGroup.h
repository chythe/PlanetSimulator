#pragma once
#include "Vertex.h"
#include <iostream>


// DEPRECATED
enum  VERTICES_TYPE { texture,color };

class VerticesGroup{
	VERTICES_TYPE verticesType;
	Vertex * vertices;
	int count;

public:
	Vertex * getVertices();
	VERTICES_TYPE getVerticesType();
	int getCount();

	VerticesGroup(Vertex* vertices, int verticesType, int count);
	~VerticesGroup();
};