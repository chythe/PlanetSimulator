// ***********************************************************************
// Assembly         : 
// Author           : Przemek
// Created          : 06-17-2016
//
// Last Modified By : Przemek
// Last Modified On : 06-17-2016
// ***********************************************************************
// <copyright file="MovementParameters.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include "Dependencies\glm\glm.hpp"
#include <math.h>
#include <iostream>


/// <summary>
/// The Gravitation constant
/// </summary>
const double G = 6.673 * pow(10, -11);


/// <summary>
/// The Sun radius
/// </summary>
const double R = 7 * pow(10, 8);


/// <summary>
/// Sun's mass. It is reduced (divided by 10^4)- as a result the 1 and 2 velocity space is reduced by 10 ^ 2
/// In that case 1 = 4366, 430383  and 2 = 6175, 065066   (m / s)
/// </summary>
const double M = 2 * pow(10, 26);


/// <summary>
/// Parametr for dividing the real position to make it drawable and visible on the computer world space
/// </summary>
const double metrToPixel = 52600000;;


/// <summary>
/// The time step
/// </summary>
const double dt = 120;

/// <summary>
/// Class MovementParameters.
/// Represents the phisical parameters needed to calculate all planet moves
/// </summary>
class MovementParameters{

public:
	
	/// <summary>
	/// The plante mass
	/// </summary>
	double m;
	
	
	/// <summary>
	/// The r distance between planet and Sun
	/// </summary>
	double r;

	
	/// <summary>
	/// The plant radius
	/// </summary>
	double radius;
	
	
	
	/// <summary>
	/// The time indicator 
	/// </summary>
	double t;
	
	/// <summary>
	/// The starting angle
	/// </summary>
	double startingAngle;

	/// <summary>
	/// The starting velocity
	/// </summary>
	double vStart;
	/// <summary>
	/// The starting high
	/// </summary>
	double startingHigh;
	

	/// <summary>
	/// Total V it could be calculated as sqrt(Vx*Vx + Vy*Vy + Vz*Vz)
	/// </summary>
	double V;
	/// <summary>
	/// The Vx velocity in x direction
	/// </summary>
	double Vx;
	/// <summary>
	/// The vy velocity in y direction
	/// </summary>
	double Vy;
	/// <summary>
	/// The vz velocity in z direction
	/// </summary>
	double Vz;
	
	
	/// <summary>
	/// The position x
	/// </summary>
	double positionX;
	/// <summary>
	/// The position y
	/// </summary>
	double positionY;
	/// <summary>
	/// The position z
	/// </summary>
	double positionZ;


	/// <summary>
	/// The ar centripetal acceleration, caused by Sun gravitation
	/// </summary>
	double ar;
	/// <summary>
	/// The ay acceleration in the y direction
	/// </summary>
	double ay;
	/// <summary>
	/// The ax acceleration in the x direction
	/// </summary>
	double ax;
	/// <summary>
	/// The az acceleration in the z direction
	/// </summary>
	double az;

	 
	/// <summary>
	/// The position to draw in the computer world space
	/// Based on the real calculated position
	/// </summary>
	glm::vec3 positionToDraw;
	/// <summary>
	/// The rotation. In practice represents the rotation of single planet. 
	/// It could be const value, but can be modified during program execution
	/// </summary>
	glm::vec3 rotation;
	/// <summary>
	/// The current rotation. Depends on program executing time. 
	/// Its the value for creating the rotation matrix to render the object.
	/// Value of this variables changes in time
	/// </summary>
	glm::vec3 currentRotation;
	

	/// <summary>
	/// Calculates the distance between planet and Sun - r
	/// </summary>
	void calculateDistance();
	/// <summary>
	/// Calculates ar - centripetal acceleration.
	/// </summary>
	void calculateA();
	/// <summary>
	/// Calculates the new coordinates. This method is sipmly based on the laws of physics.
	/// Based on the centripetal force and the gravitation
	/// </summary>
	void calculateNewCoordinates();

	/// <summary>
	/// Sets the starting parameters.
	/// </summary>
	/// <param name="vStart">The v start.</param>
	/// <param name="startingAngle">The starting angle.</param>
	/// <param name="startingHigh">The starting high.</param>
	/// <param name="radius">The radius.</param>
	/// <param name="rotation">The rotation.</param>
	void setStartingParameters(double vStart, double startingAngle, double startingHigh, double radius, glm::vec3 rotation);

	/// <summary>
	/// Initializes a new instance of the <see cref="MovementParameters"/> class.
	/// </summary>
	MovementParameters();
};