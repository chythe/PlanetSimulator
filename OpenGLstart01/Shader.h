// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Shader.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <string>
#include <fstream>
#include<iostream>
#include "Transform.h"
#include "Camera.h"


/// <summary>
/// Indicate the type of shader
/// Last value means number of avaliable types
/// </summary>
enum ShaderType{
	/// <summary>
	/// The nu m_ types
	/// </summary>
	VERTEX, FRAGMENT, NUM_TYPES
};



/// <summary>
/// Class Shader.
/// Loads the shader from file 
/// Perform updates on the variables locates in shaders programms
/// Binds shaders - make them active
/// </summary>
class Shader{

	/// <summary>
	/// The shaders avaliable in the program
	/// </summary>
	GLuint shaders[NUM_TYPES];
	
	/// <summary>
	/// The shaders program 
	/// </summary>
	GLuint program;
	
	
	/// <summary>
	/// Variable in the Shader body. References to Tansform.modelMatrix
	/// </summary>
	GLuint modelUniform;


	/// <summary>
	/// Variable in the Shader body. References to Camera.viewMatrix
	/// </summary>
	GLuint viewUniform;
	

	/// <summary>
	/// Variable in the Shader body. References to Camera.perspectiveMatrix
	/// </summary>
	GLuint perspectiveUniform;
	/// <summary>
	/// The texture index uniform. Indicates the one of loaded textures, which should be use 
	/// </summary>
	GLuint textureIndexUniform;

	
	/// <summary>
	/// Variable in the Shader body. The object ambient factor uniform
	/// </summary>
	GLuint objectAmbientFactorUniform;
	/// <summary>
	/// Variable in the Shader body. The object diffuse factor uniform
	/// </summary>
	GLuint objectDiffuseFactorUniform;
	/// <summary>
	/// Variable in the Shader body. The object specular factor uniform
	/// </summary>
	GLuint objectSpecularFactorUniform;

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Shader" /> class.
	/// Data are loaded from the file. 
	/// Shows the loaded data onto console. 
	/// Displays errors
	/// </summary>
	/// <param name="fileLocation">The file location.</param>
	Shader(std::string fileLocation);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Shader" /> class.
	/// </summary>
	Shader();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Shader" /> class.
	/// </summary>
	~Shader();

	/// <summary>
	/// Loads from file.
	/// Shows the loaded data onto console. 
	/// Displays errors
	/// </summary>
	/// <param name="fileLocation">The file location.</param>
	/// <returns>bool operation correction</returns>
	bool loadFromFile(std::string fileLocation);
	

	/// <summary>
	/// Sets the index of texture in shader program
	/// Before calling this function Bind() function must be called
	/// </summary>
	/// <param name="inex">The inex.</param>
	void setTextureIndex(int inex);
	

	/// <summary>
	/// Sets the values of uniforms in shader program: modelMatrix, viewMatrix, perspectiveMatrix
	/// Before calling this function Bind() function must be called
	/// </summary>
	/// <param name="currentTransform">The current transform.</param>
	/// <param name="currentCamera">The current camera.</param>
	void Update(Transform * currentTransform, Camera * currentCamera);
	
	/// <summary>
	/// Updates the lightning- the uniform variables in the shader programe
	/// </summary>
	/// <param name="objectAmbientFactor">The object ambient factor.</param>
	/// <param name="objectDiffuseFactor">The object diffuse factor.</param>
	/// <param name="objectSpecularFactor">The object specular factor.</param>
	void updateLightning(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor);
	
	/// <summary>
	/// Binds this shader programe - causes that this shader is used for rendering
	/// </summary>
	
	void Bind();
	
	/// <summary>
	/// Checks the error.
	/// </summary>
	/// <param name="handle">The handle for the texture.</param>
	/// <param name="isProgram">Is program created.</param>
	/// <param name="status">The status of errors.</param>
	/// <param name="errorMsg">The error MSG.</param>
	void checkError(GLuint handle, bool isProgram, GLenum status, std::string errorMsg);
	
	/// <summary>
	/// Loads the shader from file.
	/// </summary>
	/// <param name="fieldLocation">The file location.</param>
	/// <returns>The body of loaded shader or eventually errors messages</returns>
	std::string loadShader(std::string fieldLocation);
};