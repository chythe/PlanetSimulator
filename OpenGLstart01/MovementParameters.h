#pragma once

#include "Dependencies\glm\glm.hpp"
#include <math.h>
#include <iostream>

/* gravitational constant */
const double G = 6.673 * pow(10, -11); 

/* Sun radius */
const double R = 7 * pow(10, 8);

/* Sun's mass. It is reduced (divided by 10^4)- as a result the 1 and 2 velocity space is reduced by 10 ^ 2
  In that case 1=4366,430383  and 2=6175,065066   (m/s)
*/
const double M = 2 * pow(10, 26); 

/* Parametr for dividing the real position to make it drawable and visible*/
const double metrToPixel=52600000;;

/* Time step*/
const double dt = 120;

class MovementParameters{

public:
	
	
	/* planet mass */
	double m; 
	
	/* distance between planet and Sun*/
	double r;

	/* planet radius*/
	double radius;
	
	
	/* time indicator*/
	double t;
	
	double startingAngle;
	double vStart;
	double startingHigh;
	
	/* Velocities*/
	/* Total V it could be calculated as sqrt(Vx*Vx + Vy*Vy + Vz*Vz) */
	double V;
	double Vx;
	double Vy;
	double Vz;
	
	/* Actual positions*/
	double positionX;
	double positionY;
	double positionZ;

	/* accelerationa*/
	double ar;
	double ay;
	double ax;
	double az;

	 
	glm::vec3 positionToDraw;
	glm::vec3 rotation;
	glm::vec3 currentRotation;
	

	void calculateDistance();
	void calculateA();
	void calculateNewCoordinates();

	void setStartingParameters(double vStart, double startingAngle, double startingHigh,glm::vec3 rotation);
	MovementParameters();
};