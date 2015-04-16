#ifndef PROJECTILE3D_H
#define PROJECTILE3D_H

#include "projectile.h"

class projectile3d : public projectile
{
public:
    projectile3d();
    ~projectile3d();

    QString name();

private:
    //Needs the mesh setup similar to openGLMesh.
};

#endif // PROJECTILE3D_H
