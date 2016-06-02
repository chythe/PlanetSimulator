#include "VerticesGroup.h"

VerticesGroup::VerticesGroup(Vertex * vertices, int type,int count){
	verticesType = VERTICES_TYPE(type);
	this->vertices = vertices;
	this->count = count;
}

VerticesGroup::~VerticesGroup(){
//	delete vertices;
}

Vertex* VerticesGroup::getVertices(){
	return vertices;
}

VERTICES_TYPE VerticesGroup::getVerticesType(){
	return verticesType;
}

int VerticesGroup::getCount(){
	return count;
}