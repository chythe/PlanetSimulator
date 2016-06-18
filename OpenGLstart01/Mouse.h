// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Mouse.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Camera.h"
#include "Dependencies\glfw\glfw3.h"

/// <summary>
/// Class Mouse. Mouse operation handler
/// </summary>
class Mouse{
protected:
	/// <summary>
	/// The cursor position x
	/// </summary>
	double cursorPositionX;
	/// <summary>
	/// The cursor position y
	/// </summary>
	double cursorPositionY;
	/// <summary>
	/// The horizontal angle
	/// </summary>
	float horizontalAngle;
	/// <summary>
	/// The vertical angle
	/// </summary>
	float verticalAngle;
public:
	/// <summary>
	/// Moves the camera basing on the mouse position
	/// </summary>
	/// <param name="window">The window.</param>
	/// <param name="camera">The Camera class object.</param>
	/// <param name="elapsedTime">The elapsed time. Determines how fast camera is moving</param>
	void moveCamera(GLFWwindow * window, Camera&camera, double elapsedTime);
	/// <summary>
	/// Initializes a new instance of the <see cref="Mouse"/> class.
	/// </summary>
	Mouse();
};