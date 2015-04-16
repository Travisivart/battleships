#include "camera.h"

camera::camera()
{

}

camera::~camera()
{

}


void camera::translate(float newX, float newY, float newZ)
{
    this->transX = newX;
    this->transY = newY;
    this->transZ = newZ;
}

void camera::rotate(float newX, float newY, float newZ)
{
    this->rotX = newX;
    this->rotY = newY;
    this->rotZ = newZ;
}
