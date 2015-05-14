#include "projectile.h"
#include <QDebug>


projectile::projectile()
{
	this->mesh=NULL;
}
projectile::projectile(GLMmodel* mesh,GLfloat *translation,GLfloat *rotation){
    this->mesh=mesh;
	//this->getBox().calculateBox(this->mesh);
    this->box.calculateBox(this->mesh);
	this->translation[0] = translation[0];
    this->translation[1] = translation[1];
    this->translation[2] = translation[2];

    this->rotation[0] = rotation[0];
    this->rotation[1] = rotation[1];
    this->rotation[2] = rotation[2];
    this->scaling[0] = 2.0f;
    this->scaling[1] = 2.0f;
    this->scaling[2] = 2.0f;
    this->destructible=true;
    this->alive=true;
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
	this->getBox().calculateBox(this->mesh);
    //this->box.calculateBox(this->mesh);
	this->translation[0] = translation[0];
    this->translation[1] = translation[1];
    this->translation[2] = translation[2];

    this->rotation[0] = rotation[0];
    this->rotation[1] = rotation[1];
    this->rotation[2] = rotation[2];
    this->scaling[0] = .1f;
    this->scaling[1] = .1f;
    this->scaling[2] = .1f;
}


void projectile::draw()
{
    glPushMatrix();

    //glLoadIdentity();

    //glTranslatef(0, 0, 0);
	if((this->translation[1]>800 || this->translation[0]>800 || this->translation[1]<-800 || this->translation[0]<-800) ){
		qDebug()<<"destroy missile";
		this->mesh=NULL;
        openGLObject::destroy();
        //openGLObject::destroy();
	}
	else
    	glTranslatef(this->translation[0] -= ((10.0f )*sin(this->rotation[2]*3.14159265/180)), this->translation[1] += ((10.0f)*cos(this->rotation[2]*3.14159265/180)), this->translation[2]);

    glRotatef(this->rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
   glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    //Return to original position
    //glTranslatef(0.0,0.0,0.0);
    // glRotatef(90, 1.0,0.0,0.0);
    // glRotatef(180, 0.0,1.0,0.0);
    if(this->mesh!=NULL){
    	glmDraw(this->mesh,GLM_MATERIAL, GL_TRIANGLES);
    	//this->box.checkCollision(this->mesh, this->mesh);
    }
    //qDebug()<<"draw missile";

    // glBegin(GL_LINES);
    // float minx = this->getBox().getMinX();
    // float miny = this->getBox().getMinY();
    // float minz = this->getBox().getMinZ();
    // float maxx = this->getBox().getMaxX();
    // float maxy = this->getBox().getMaxY();
    // float maxz = this->getBox().getMaxZ();
    // // qDebug()<<"minx "<<minx<<" miny "<<miny<<" minz "<<minz<<" maxx "<<maxx<<" maxy "<<maxy<<" maxz "<<maxz;

    // //Draw bottom square
    // glVertex3f(minx, miny ,minz);
    // glVertex3f(minx, maxy ,minz);
    // glVertex3f(minx, maxy ,minz);
    // glVertex3f(maxx, maxy ,minz);
    // glVertex3f(maxx, maxy ,minz);
    // glVertex3f(maxx, miny ,minz);
    // glVertex3f(maxx, miny ,minz);
    // glVertex3f(minx, miny ,minz);

    // //Draw vertical lines
    // glVertex3f(minx, miny ,minz);
    // glVertex3f(minx, miny ,maxz);
    // glVertex3f(minx, maxy ,minz);
    // glVertex3f(minx, maxy ,maxz);
    // glVertex3f(maxx, maxy ,minz);
    // glVertex3f(maxx, maxy ,maxz);
    // glVertex3f(maxx, miny ,minz);
    // glVertex3f(maxx, miny ,maxz);

    // //Draw top square
    // glVertex3f(minx, miny ,maxz);
    // glVertex3f(minx, maxy ,maxz);

    // glVertex3f(minx, maxy ,maxz);
    // glVertex3f(maxx, maxy ,maxz);

    // glVertex3f(maxx, maxy ,maxz);
    // glVertex3f(maxx, miny ,maxz);

    // glVertex3f(maxx, miny ,maxz);
    // glVertex3f(minx, miny ,maxz);

    // glEnd();

    glPopMatrix();
}


//boundingBox projectile::getBox()
//{
//    return this->box;
//}


//bool projectile::isAlive(){
//	return this->alive;
//}

//bool projectile::isDescructable(){
//	return this->destructible;
//}
