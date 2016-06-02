#pragma once
#include "assimp\scene.h"
#include "assimp\cimport.h"
#include "assimp\postprocess.h"


#include "Shader.h"
#include "Texture.h"


#include  <iostream>
#include <vector>


/*
	Model hadnler
	Loads from file
	Draws the mesh with textures
*/

class Model{
public:
	
	Shader shader;
	Transform transform;


	std::vector<GLfloat> meshVerticesCount;
	std::vector<GLfloat> meshStartingVertexIndex;
	std::vector<GLuint> textures;
	GLuint vao;

	void draw() const;
	


	std::vector<GLfloat>  getMeshStartingVertexIndex() const;
	std::vector<GLuint>	  getTextures() const;
	std::vector<GLfloat>  getMeshVerticesCount() const;
	GLuint  getVao() const;

	Shader& getShader();
	Transform& getTransform();
	Model(std::string fileName);
	Model(const Model & model);
};