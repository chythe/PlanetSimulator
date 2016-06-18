// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Transform.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Dependencies\glm\glm.hpp"
#include  "Dependencies\glm\gtx\transform.hpp"


/// <summary>
/// Class Transform. Transorm handler 
/// </summary>
class Transform{
	/// <summary>
	/// The model matrix. It is product of rotation, translation and scale matrix
	/// </summary>
	glm::mat4 modelMatrix;
	/// <summary>
	/// The position
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// The rotation
	/// </summary>
	glm::vec3 rotation;
	/// <summary>
	/// The scale
	/// </summary>
	glm::vec3 scale;

public:
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="position">The position.</param>
	void setPosition(glm::vec3 position);
	/// <summary>
	/// Sets the rotation.
	/// </summary>
	/// <param name="rotation">The rotation.</param>
	void setRotation(glm::vec3 rotation);
	/// <summary>
	/// Sets the scale.
	/// </summary>
	/// <param name="scale">The scale.</param>
	void setScale(glm::vec3 scale);
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 getPosition();
	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 getRotation();
	/// <summary>
	/// Gets the scale.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 getScale();
	/// <summary>
	/// Gets the model matrix.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	glm::mat4 getModelMatrix();
	
	
	/// <summary>
	/// Return normalized vector.
	/// </summary>
	/// <param name="vector">The vector.</param>
	/// <returns>glm.vec3. normalized vector</returns>
	glm::vec3 normalize(const glm::vec3 vector);
	

	/// <summary>
	/// Return the matrix which is one part of the final rotation matrix. 
	///	Which part it is depends on axis argumet.
	/// </summary>
	/// <param name="rotation">The rotation.</param>
	/// <param name="axis">The axis.</param>
	/// <returns>glm.mat4.rotation matrix</returns>
	glm::mat4 rotate(float rotation, glm::vec3 axis);
  

	/// <summary>
	/// Multiples the matrix.
	/// </summary>
	/// <param name="m1">The m1. first matrix</param>
	/// <param name="m2">The m2. second matrix</param>
	/// <returns>glm.mat4.multipled matrix </returns>
	glm::mat4 multipleMatrix(const glm::mat4 & m1, const glm::mat4 & m2);
    
	/// <summary>
	/// Translates the specified position.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <returns>glm.mat4.Translation matrix</returns>
	glm::mat4 translate(glm::vec3 position);
	/// <summary>
	/// Create new model matrix based on the class parameters.
	/// </summary>
	void update();
					
	
		
	/// <summary>
	/// Initializes a new instance of the <see cref="Transform"/> class.
	/// </summary>
	Transform();  
	/// <summary>
	/// Finalizes an instance of the <see cref="Transform"/> class.
	/// </summary>
	~Transform();
};