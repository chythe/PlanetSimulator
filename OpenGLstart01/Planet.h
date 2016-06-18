// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Planet.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Model.h"
#include "MovementParameters.h"

/// <summary>
/// Class Planet. 
/// Contains all classes objects which are needed to render and move the planet
/// </summary>
class Planet{

protected:
	

	/// <summary>
	/// The transform - position, rotation, scale handler
	/// The model rendering is based on Transform object
	/// </summary>
	Transform transform;
	
	
	/// <summary>
	/// Pointer to Model object. 
	/// It is assigned, not memory allocated especcialy for this object into planet class
	/// </summary>
	const Model * model;

	/// <summary>
	/// Pointer to Shader
	/// It is assigned, memory is not allocated in this class
	/// </summary>
	Shader * shader;

	/// <summary>
	/// The movement parameters
	/// Describes all phisics values and calculate them during the movement
	/// </summary>
	MovementParameters movementParameters;

	

public:

	
	/// <summary>
	/// The object light ambient factor
	/// </summary>
	glm::vec3 objectAmbientFactor;
	
	/// <summary>
	/// The object light diffuse factor
	/// </summary>
	glm::vec3 objectDiffuseFactor;
	
	/// <summary>
	/// The object light specular factor
	/// </summary>
	glm::vec3 objectSpecularFactor;

	/// <summary>
	/// Initializes a new instance of the <see cref="Planet"/> class.
	/// </summary>
	/// <param name="model">The model.</param>
	/// <param name="shader">The shader.</param>
	Planet(const Model * model, Shader * shader);
	
	/// <summary>
	/// Gets the transform.
	/// </summary>
	/// <returns>Transform &.</returns>
	Transform & getTransform();
	

	/// <summary>
	/// Draws the complex- update transform, update shader, draw model
	/// </summary>
	/// <param name="camera">The camera.</param>
	void drawComplex(Camera&camera);
	

	/// <summary>
	/// Just model->draw()
	/// </summary>
	void draw();
	
	
	/// <summary>
	/// Sets the starting parameters.
	/// Just movementParameters -> setStartingParameters()
	/// </summary>
	/// <param name="vStart">The starting velocity.</param>
	/// <param name="startingAngle">The starting angle.</param>
	/// <param name="startingHigh">The starting high.</param>
	/// <param name="rotation">The rotation factor.</param>
	void setStartingParameters(double vStart, double startingAngle, double startingHigh, glm::vec3 rotation);

	
	/// <summary>
	/// Calculates the new coordinates.
	/// Just movementParameters->calculateNewCoordinates(). 
	/// Just calculating, not updating Transform object
	/// </summary>
	void calculateNewCoordinates();

	
	/// <summary>
	/// Sets the transform.
	/// This function should be call after calculateNewCoordinates to set the new coordinates in the Transform object 
	/// </summary>
	void setTransform();
	
	/// <summary>
	/// Updates the shader.
	/// </summary>
	/// <param name="camera">The camera.</param>
	void updateShader(Camera & camera);


	/// <summary>
	/// Sets the lightning parameters.
	/// </summary>
	/// <param name="objectAmbientFactor">The object ambient factor.</param>
	/// <param name="objectDiffuseFactor">The object diffuse factor.</param>
	/// <param name="objectSpecularFactor">The object specular factor.</param>
	void setLightningParameters(glm::vec3 objectAmbientFactor, glm::vec3 objectDiffuseFactor, glm::vec3 objectSpecularFactor);

	/// <summary>
	/// Updates the lightning in shader. 
	/// Updates uniforms variables in shader
	/// </summary>
	void updateLightningInShader();
	
	/// <summary>
	/// Gets the shader.
	/// </summary>
	/// <returns>Shader &.</returns>
	Shader & getShader();
};
