/*
 * Parent class for both 2d and 3d projectiles
 * Projectiles could be anything that can be considered 'fired' by a weapon
 * Both bullets and bombs or traps could be projectiles. The main difference is bombs or traps may be rather static
 * with little to no velocity and acceleration but 'bullets' could have both velocity and acceleration
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "openglobject.h"
#include "openglmesh.h"
#include "../tutor/glm.h"
#include "boundingbox.h"

// class boundingbox;
 class openGLMesh;

class projectile : public openGLMesh
{
public:
    projectile();
    projectile(GLMmodel* mesh,GLfloat *translation, GLfloat *rotation);

    virtual ~projectile();

    //Set methods
    void setVelocity(GLfloat newVelocity);
    void setAcceleration(GLfloat newAcceleration);

    //Get methods
    GLfloat getVelocity();
    GLfloat getAcceleration();
    void changemesh(GLMmodel* missile,GLfloat translation[3], GLfloat rotation[3]);
    void draw();

    // boundingBox getBox();
    // bool isAlive();
    // bool isDescructable();
    // void destroy();




    QString name();

protected:
    GLfloat velocity;
    GLfloat acceleration;
    // GLMmodel* mesh;
    
    // boundingBox box;



    // GLfloat translation[3];
    // GLfloat rotation[3];
    // GLfloat scaling[3];
    // bool destructible;
    // bool alive;
};

#endif // PROJECTILE_H
