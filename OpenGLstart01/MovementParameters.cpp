#include "MovementParameters.h"


MovementParameters::MovementParameters(){

}

/*
Maybe here could be parameters checker, if they are correct
*/
void MovementParameters::setStartingParameters(double vStart, double startingAngle, double startingHigh, double radius, glm::vec3 rotation){

	currentRotation = glm::vec3(0.0, 0.0, 0.0);
	this->rotation = rotation;
	this->vStart = vStart;
	this->startingAngle = startingAngle;
	this->startingHigh = startingHigh;
    this->radius = radius;

	t = 0;

	positionX = R + startingHigh;
	positionY = 0;
	positionZ = 0;
	r = sqrt(pow(positionX, 2) + pow(positionY, 2));

	Vx = 0;
	Vy = vStart;

	//	Vx = vStart*cos(90 - startingAngle);  tu bytrzeba zrobic w radianach i nie wiem czy sin i cos nie zamienic 
	//	Vy = vStart*sin(90 - startingAngle);


	r = sqrt(pow(positionX, 2) + pow(positionY, 2));

	ar = (-1 * G * M) / pow(r, 2);
	ax = ar * positionX / r;
	ay = ar * positionY / r;

	Vx = Vx + ax*(dt / 2);
	Vy = Vy + ay*(dt / 2);


	
}

void MovementParameters::calculateDistance(){
	r = sqrt((pow(positionX, 2) + pow(positionY, 2) + pow(positionZ, 2)));
}

void MovementParameters::calculateA(){
	//	a.x = -(position.x / pow(r, 3));
	//a.y = -(position.y / pow(r, 3));

}

void MovementParameters::calculateNewCoordinates(){
	t = t + dt;



	if (r >= R){

		currentRotation += rotation;

		positionX = positionX + Vx*dt;
		positionY = positionY + Vy*dt;

		r = sqrt(pow(positionX, 2) + pow(positionY, 2));

		ar = (-1 * G*M) / pow(r, 2);
		ax = ar*positionX / r;
		ay = ar*positionY / r;

		Vx = Vx + ax*dt;
		Vy = Vy + ay*dt;

		positionToDraw.x = positionX / metrToPixel;
		positionToDraw.y = -1 * positionY / metrToPixel;
		positionToDraw.z = positionZ / metrToPixel;
	}

}
/* altertnatywa z uwzglednieniem mas planet, i oddzia³ywania jednej planety na drug¹
dx = x1 - x2;
dy = ya1 - y2;

r = sqrt((dx*dx)+(dy*dy));

g = Cg*m1*m2/(r*r);

gx = g*dx/r;
gy = g*dy/r;


vx1 += -gx*dt/m1;
vy1 += -gy*dt/m1;
vx2 += gx*dt/m2;
vy2 += gy*dt/m2;

x1 += vx1*dt;
ya1 += vy1*dt;
x2 += vx2*dt;
y2 += vy2*dt;

*/