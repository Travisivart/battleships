#ifndef PROJECTILE2D_H
#define PROJECTILE2D_H

#include "projectile.h"

class projectile2d : public projectile
{
public:
    projectile2d();
    ~projectile2d();

    QString name();

private:
    //Needs some sort of 2d mapping to a sprite or texture.
};

#endif // PROJECTILE2D_H
