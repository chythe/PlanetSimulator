#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <string>
#include <fstream>
#include<iostream>
#include "Transform.h"
#include "Camera.h"

/*
	Indicate the type of shader
	Last value means number of avaliable types
*/
enum ShaderType{
	VERTEX, FRAGMENT, NUM_TYPES
};


/*
	Loads the shader from file 
	Perform updates on the variables locates in shaders programms
	Binds shaders - make them active
*/
class Shader{

	GLuint shaders[NUM_TYPES];
	GLuint program;
	/*
		Uniforms indicates the variables in shader program
		Works similalarly like pointers
	*/
	/*
		References to Tansform.modelMatrix
	*/
	GLuint modelUniform;
	/*
		References to Camera.viewMatrix
	*/
	GLuint viewUniform;
	/*
		References to Camera.perspectiveMatrix
	*/
	GLuint perspectiveUniform;
	GLuint textureIndexUniform;

	/*
		Uniforms referenced to the lightning
	*/
	GLuint objectAmbientFactorUniform;
	GLuint objectDiffuseFactorUniform;
	GLuint objectSpecularFactorUniform;

public:
	Shader(std::string fileLocation);
	Shader();
	~Shader();

	bool loadFromFile(std::string fileLocation);
	/*
		Sets the index of texture in shader program
		Before calling this function Bind() function must be called  
	*/
	void setTextureIndex(int inex); 
	/*
		Sets the values of uniforms in shader program: modelMatrix, viewMatrix, perspectiveMatrix
		Before calling this function Bind() function must be called
	*/
	void Update(Transform * currentTransform,Camera * currentCamera); // przed zrobieniem update nalzezy najpierw zrobic bind, bo trzeba wywolac use_program
	void updateLightning(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor);
	void Bind();
	void checkError(GLuint handle, bool isProgram, GLenum status, std::string errorMsg);
	std::string loadShader(std::string fieldLocation);
};