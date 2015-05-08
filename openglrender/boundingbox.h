#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "../tutor/glm.h"

class boundingBox
{
public:
    boundingBox();
    ~boundingBox();

    float getMinX();
    float getMinY();
    float getMinZ();
    float getMaxX();
    float getMaxY();
    float getMaxZ();

    //Takes a mesh and calculates the min and max values to build the box;
    void calculateBox(GLMmodel *mesh);

    //Check if we should do a more complicated check for collisions
    bool possibleCollision(GLMmodel *mesh1, GLMmodel *mesh2);

    //More complex coliision detection
    bool checkCollision(GLMmodel *mesh1, GLMmodel *mesh2);

private:

    float minX, minY, minZ, maxX, maxY, maxZ;
};

#endif // BOUNDINGBOX_H
