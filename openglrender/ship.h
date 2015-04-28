#ifndef SHIP_H
#define SHIP_H

#include "openglmesh.h"

class ship : public openGLMesh
{
public:
    ship();
    ~ship();
    float getVelocity();
    void increaseAcceleration();
    void decreaseAcceleration();

private:
    float acceleration, velocity,angle;

};

#endif // SHIP_H
