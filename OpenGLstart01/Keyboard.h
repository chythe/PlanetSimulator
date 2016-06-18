// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="Keyboard.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Camera.h"
#include "Dependencies\glfw\glfw3.h"

/// <summary>
/// Class Keyboard.
/// Keyboard handler
/// </summary>
class Keyboard{


public:
	/// <summary>
	/// Moves the camera basing on the pressed key
	/// </summary>
	/// <param name="camera">The objcet of Camera class.</param>
	/// <param name="window">The window.</param>
	/// <param name="elapsedTime">The elapsed time. Determines how fast camera is moving</param>
	void moveCamera(Camera & camera, GLFWwindow * window, double elapsedTime);
};