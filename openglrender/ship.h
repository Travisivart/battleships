#ifndef SHIP_H
#define SHIP_H

#include "openglmesh.h"

class ship : public openGLMesh
{
public:
    ship();
    ~ship();
    getVelocity();
    increaseAcceleration();
    decreaseAcceleration();

private:
    float acceleration, velocity,angle;

};

#endif // SHIP_H
