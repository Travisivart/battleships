/*
 * Parent class for both 2d and 3d projectiles
 * Projectiles could be anything that can be considered 'fired' by a weapon
 * Both bullets and bombs or traps could be projectiles. The main difference is bombs or traps may be rather static
 * with little to no velocity and acceleration but 'bullets' could have both velocity and acceleration
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "openglobject.h"

class projectile : public openGLObject
{
public:
    projectile();
    virtual ~projectile();

    //Set methods
    void setVelocity(GLfloat newVelocity);
    void setAcceleration(GLfloat newAcceleration);

    //Get methods
    GLfloat getVelocity();
    GLfloat getAcceleration();

    QString name();

protected:
    GLfloat velocity;
    GLfloat acceleration;
};

#endif // PROJECTILE_H
