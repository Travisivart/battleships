#include "ship.h"

ship::ship()
{

}

ship::~ship()
{

}

float ship::getVelocity(){
	return velocity;
}

void ship::increaseAcceleration(){
    acceleration+=.5;
}

void ship::decreaseAcceleration(){
    acceleration-=1;

}

