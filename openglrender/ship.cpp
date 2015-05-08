#include "ship.h"
#include <QDebug>

ship::ship()
{
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;

    this->scaling[0] = 1.0f;
    this->scaling[1] = 1.0f;
    this->scaling[2] = 1.0f;

    //#define GLM_NONE     (0)		/* render with only vertices */
    //#define GLM_FLAT     (1 << 0)		/* render with facet normals */
    //#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
    //#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
    //#define GLM_COLOR    (1 << 3)		/* render with colors */
    //#define GLM_MATERIAL (1 << 4)		/* render with materials */
    this->mode = GLM_MATERIAL;

    mesh = NULL;

    this->destructible = true;
}

ship::ship(const QString newFilename,bool player)
{
    qDebug()<<"Constructor: ship(" <<newFilename <<")";
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;

    this->scaling[0] = 1.0f;
    this->scaling[1] = 1.0f;
    this->scaling[2] = 1.0f;
    this->player=player;
    this->velocity=0;
    //#define GLM_NONE     (0)		/* render with only vertices */
    //#define GLM_FLAT     (1 << 0)		/* render with facet normals */
    //#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
    //#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
    //#define GLM_COLOR    (1 << 3)		/* render with colors */
    //#define GLM_MATERIAL (1 << 4)		/* render with materials */
    this->mode = GLM_MATERIAL;

    this->filename = newFilename;

    qDebug()<<"ship::ship(const QString newFilename)" <<"Attempting file load";
    this->load(this->filename);

    qDebug()<<"Calculating bounding box";
    this->getBox().calculateBox(this->mesh);
    this->box.calculateBox(this->mesh);
    //qDebug()<<"MaxX: " <<box.getMaxX();
    //qDebug()<<"MinX: " <<box.getMinX();
    //qDebug()<<"MinY: " <<box.getMinY();

    v = 1.0f;

    this->destructible = true;
}

ship::~ship()
{
    delete this->mesh;
}

float ship::getVelocity(){
	return this->velocity;
}

void ship::increaseAcceleration(){
    qDebug()<<"Speed up";
    if(velocity<.1)
        velocity+=.004;
}

void ship::decreaseAcceleration(){
    if(this->velocity>0.005)
        velocity-=.005;
    else
        this->velocity=0;

}

void ship::translate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->translation[0] = newX;
    this->translation[1] = newY;
    this->translation[2] = newZ;
}

void ship::translate(GLfloat *newTranslation)
{
    this->translation[0] = newTranslation[0];
    this->translation[1] = newTranslation[1];
    this->translation[2] = newTranslation[2];
}

void ship::rotate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->rotation[0] = fmod(newX, 360);
    this->rotation[1] = fmod(newY, 360);
    this->rotation[2] = fmod(newZ, 360);
}

void ship::rotate(GLfloat *newRotation)
{
    this->rotation[0] = fmod(newRotation[0], 360);
    this->rotation[1] = fmod(newRotation[1], 360);
    this->rotation[2] = fmod(newRotation[2], 360);
}

void ship::scale(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->scaling[0] = newX;
    this->scaling[1] = newY;
    this->scaling[2] = newZ;
}

void ship::scale(GLfloat *newScaling)
{
    this->scaling[0] = newScaling[0];
    this->scaling[1] = newScaling[1];
    this->scaling[2] = newScaling[2];
}

void ship::setMode(int GLM_MODE)
{
    this->mode = GLM_MODE;
}

GLfloat* ship::getTranslation()
{
    return this->translation;
}

GLfloat* ship::getRotation()
{
    return this->rotation;
}

GLfloat* ship::getScaling()
{
    return this->scaling;
}

void ship::load(QString filename)
{
    qDebug()<<"ship::load(QString filename)";
    //Make sure that we are actually trying to load an existing file.
    if (filename != "")
    {
        //If something is already loaded into the mesh, then delete it.
        //if ( mesh != NULL )
        //deleteMesh();

        QByteArray ba = filename.toLatin1();
        char *c_str2 = ba.data();

        this->mesh = glmReadOBJ(c_str2);
    }
}

void ship::deleteMesh()
{
    delete this->mesh;
    mesh = NULL;
}

QString ship::getFilename()
{
    return this->filename;
}

void ship::update(const int &msec)
{
    float bounce=-.01f;
    int trigger=0;
    //qDebug()<<"Ship update";

    qDebug()<<"velocity: " <<velocity+(float)(rand()%3-1)/3;
    if(player){
        if(trigger%10==0){
            if(rand()%2>0)
                bounce=.01f;
            else
                bounce=-.01f;
        }
            this->translation[0] -= ((this->velocity+bounce)*sin(this->rotation[2]*3.14159265/180));
            //this->translation[1] += 1.0f * msec/1000;
            this->translation[1] += ((this->velocity+bounce)*cos(this->rotation[2]*3.14159265/180));
            //((ship*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
            bounce=0;
            trigger++;
    }
    else{
        if(this->translation[1]>20){
            qDebug()<<"ship out of bounds";
        }

        else{
        this->translation[0] -= ((2.0f * msec/100)*sin(this->rotation[2]*3.14159265/180));
        //this->translation[1] += 1.0f * msec/1000;
        this->translation[1] += ((2.0f * msec/100)*cos(this->rotation[2]*3.14159265/180));
        //((ship*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
    }
    }
}

void ship::draw()
{
    glPushMatrix();

    //glLoadIdentity();

    glTranslatef(this->translation[0], this->translation[1], this->translation[2]);

    glRotatef(this->rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
    glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    //Return to original position
    //glTranslatef(0.0,0.0,0.0);
    glRotatef(90, 1.0,0.0,0.0);
    glRotatef(180, 0.0,1.0,0.0);

    glmDraw(this->mesh,this->mode, GL_TRIANGLES);

    glPopMatrix();
}

void ship::draw(openGLCamera *c)
{
    glPushMatrix();

    glTranslatef(this->translation[0] + c->getTranslation()[0], this->translation[1] + c->getTranslation()[1], this->translation[2] + c->getTranslation()[2]);

    glRotatef(this->rotation[0] + c->getRotation()[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1] + c->getRotation()[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2] + c->getRotation()[2], 0.0f, 0.0f, 1.0f);

    //Return to original position
    //glTranslatef(0.0,0.0,0.0);
    glRotatef(90, 1.0,0.0,0.0);
    glRotatef(180, 0.0,1.0,0.0);

    //Perform scaling
    glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    glmDraw(this->mesh,this->mode, GL_TRIANGLES);
    this->box.checkCollision(this->mesh, this->mesh);
    glPopMatrix();
}

QString ship::name()
{
    return "ship";
}
