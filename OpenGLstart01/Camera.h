// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Camera.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\transform.hpp"


/*
	Camera handler
	Allows to set position and direction
*/
/// <summary>
/// Class Camera. Allows to set position and direction
/// </summary>
class Camera{
	/// <summary>
	/// The view matrix. Specyfity the direction in which observer is facing
	/// </summary>
	glm::mat4 viewMatrix;
	/// <summary>
	/// The perspective matrix- perspective projection.
	/// Briefly what part of world and how should be diepleyed
	/// </summary>
	glm::mat4 perspectiveMatrix;
	/// <summary>
	/// Up vector.
	/// Vector with size given by the product of two vectors: directionVector and rightVector
	/// </summary>
	glm::vec3 upVector;
	/// <summary>
	/// The right vector
	/// </summary>
	glm::vec3 rightVector;
	/// <summary>
	/// The direction vector. Direction in which observer is facing
	/// </summary>
	glm::vec3 directionVector;
	/// <summary>
	/// The observer - camera position.
	/// Means tha translaction vector which move the camera to the right position
	/// </summary>
	glm::vec3 position;


public:
	
	/// <summary>
	/// Actualize the view matrix
	/// </summary>
	void update();
	/// <summary>
	/// Sets the position by direction.
	/// </summary>
	/// <param name="value">The value.</param>
	void setPositionByDirection(float value);
	/// <summary>
	/// Sets the position by right vector.
	/// </summary>
	/// <param name="value">The value.</param>
	void setPositionByRightVector(float value);
	/// <summary>
	/// Sets the direction vector.
	/// </summary>
	/// <param name="value">The value.</param>
	void setDirectionVector(glm::vec3 value);
	/// <summary>
	/// Sets the right vector.
	/// </summary>
	/// <param name="value">The value.</param>
	void setRightVector(glm::vec3 value);
	/// <summary>
	/// Update the up vector as a cross product of two vectors: directionVector and rightVector
	/// </summary>
	void updateUpVector();
	/// <summary>
	/// Gets the view matrix.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	glm::mat4 getViewMatrix();
	/// <summary>
	/// Gets the perspective matrix.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	glm::mat4 getPerspectiveMatrix();

	/// <summary>
	/// View Matrix and Perspective Matrix are creates with default values
	/// Performing the update before using Camera object(after its creation) is not obligatory
	/// </summary>
	Camera();
	/// <summary>
	/// Finalizes an instance of the <see cref="Camera"/> class.
	/// </summary>
	~Camera();
};