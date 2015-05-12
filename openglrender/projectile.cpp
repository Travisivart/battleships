#include "projectile.h"
#include <QDebug>


projectile::projectile()
{
	this->mesh=NULL;
}

projectile::~projectile()
{

}

void projectile::setVelocity(GLfloat newVelocity)
{

}

void projectile::setAcceleration(GLfloat newAcceleration)
{

}


GLfloat projectile::getVelocity()
{
    return 0.0f;
}

GLfloat projectile::getAcceleration()
{
    return 0.0f;
}

QString projectile::name()
{
    return "projectile";
}

void projectile::changemesh(GLMmodel* missile, GLfloat translation[3], GLfloat rotation[3]){
	this->mesh=missile;
	this->translation[0] = translation[0];
    this->translation[1] = translation[1];
    this->translation[2] = translation[2];

    this->rotation[0] = rotation[0];
    this->rotation[1] = rotation[1];
    this->rotation[2] = rotation[2];
    this->scaling[0] = .2f;
    this->scaling[1] = .2f;
    this->scaling[2] = .2f;
}


void projectile::draw()
{
    glPushMatrix();

    //glLoadIdentity();

    //glTranslatef(0, 0, 0);
	if(this->translation[1]>20 && this->translation[0]>20){
		//qDebug()<<"missile translation"<<this->translation[2];
		this->mesh=NULL;
	}
	else
    	glTranslatef(this->translation[0] -= ((0.5f )*sin(this->rotation[2]*3.14159265/180)), this->translation[1] += ((0.5f)*cos(this->rotation[2]*3.14159265/180)), this->translation[2]);

    glRotatef(this->rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
   glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    //Return to original position
    //glTranslatef(0.0,0.0,0.0);
    // glRotatef(90, 1.0,0.0,0.0);
    // glRotatef(180, 0.0,1.0,0.0);
    if(this->mesh!=NULL)
    	glmDraw(this->mesh,GLM_MATERIAL, GL_TRIANGLES);
    //qDebug()<<"draw missile";
    glPopMatrix();
}
