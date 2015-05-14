#include "openglmesh.h"

openGLMesh::openGLMesh()
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

    this->destructible = false;
    this->alive = false;
}

openGLMesh::openGLMesh(const QString newFilename)
{
    qDebug()<<"Constructor: openGLMesh(" <<newFilename <<")";
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

    this->filename = newFilename;

    qDebug()<<"openGLMesh::openGLMesh(const QString newFilename)" <<"Attempting file load";
    this->load(this->filename);

    qDebug()<<"Calculating bounding box";
    this->box.calculateBox(this->mesh);

    v = 1.0f;

    this->destructible = false;
    this->alive = false;
}

openGLMesh::~openGLMesh()
{
    //delete this->mesh;
}

void openGLMesh::translate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->translation[0] = newX;
    this->translation[1] = newY;
    this->translation[2] = newZ;
}

void openGLMesh::translate(GLfloat *newTranslation)
{
    this->translation[0] = newTranslation[0];
    this->translation[1] = newTranslation[1];
    this->translation[2] = newTranslation[2];
}

void openGLMesh::rotate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->rotation[0] = fmod(newX, 360);
    this->rotation[1] = fmod(newY, 360);
    this->rotation[2] = fmod(newZ, 360);
}

void openGLMesh::rotate(GLfloat *newRotation)
{
    this->rotation[0] = fmod(newRotation[0], 360);
    this->rotation[1] = fmod(newRotation[1], 360);
    this->rotation[2] = fmod(newRotation[2], 360);
}

void openGLMesh::scale(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->scaling[0] = newX;
    this->scaling[1] = newY;
    this->scaling[2] = newZ;
}

void openGLMesh::scale(GLfloat *newScaling)
{
    this->scaling[0] = newScaling[0];
    this->scaling[1] = newScaling[1];
    this->scaling[2] = newScaling[2];
}

void openGLMesh::setMode(int GLM_MODE)
{
    this->mode = GLM_MODE;
}

GLfloat* openGLMesh::getTranslation()
{
    return this->translation;
}

GLfloat* openGLMesh::getRotation()
{
    return this->rotation;
}

GLfloat* openGLMesh::getScaling()
{
    return this->scaling;
}

_GLMmodel* openGLMesh::getMesh()
{
    return this->mesh;
}

boundingBox openGLMesh::getBox()
{
    return this->box;
}

void openGLMesh::load(QString filename)
{
    qDebug()<<"openGLMesh::load(QString filename)";
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

void openGLMesh::deleteMesh()
{
    delete this->mesh;
    mesh = NULL;
}

QString openGLMesh::getFilename()
{
    return this->filename;
}

void openGLMesh::update(const int &msec)
{

    // qDebug()<<"Updating for msec: " <<msec;
    this->translation[0] -= ((1.0f * msec/100)*sin(this->rotation[2]*3.14159265/180));
    //this->translation[1] += 1.0f * msec/1000;
    this->translation[1] += ((1.0f * msec/100)*cos(this->rotation[2]*3.14159265/180));
    //((openGLMesh*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
}

void openGLMesh::draw()
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
    //this->box.checkCollision(this->mesh, this->mesh);
    glPopMatrix();
}

void openGLMesh::draw(openGLCamera *c)
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
    //this->box.checkCollision(this->mesh, this->mesh);
    glPopMatrix();
}

bool openGLMesh::checkCollision(openGLMesh *otherMesh)
{
    bool collisionFlag = false;

    //this->box.checkCollision(this->mesh, otherMesh->getMesh());

    float* myTrans = this->getTranslation();
    float* otherTrans = otherMesh->getTranslation();
    float* myRot = this->getRotation();
    float* otherRot = otherMesh->getRotation();
    float* myScale = this->getScaling();
    float* otherScale = otherMesh->getScaling();

    float temp;
    float myMinX, myMinY, myMinZ, myMaxX, myMaxY, myMaxZ;
    float otherMinX, otherMinY, otherMinZ, otherMaxX, otherMaxY, otherMaxZ;

    float myxTopLeft, myxTopRight, myxBottomLeft, myxBottomRight;
    float myyTopLeft, myyTopRight, myyBottomLeft, myyBottomRight;
    float otherxTopLeft, otherxTopRight, otherxBottomLeft, otherxBottomRight;
    float otheryTopLeft, otheryTopRight, otheryBottomLeft, otheryBottomRight;

    //myMinX = myScale[0] * (this->box.getMinX() * cos(myRot[2]*3.14159265/180) + this->box.getMinY() * sin(myRot[2]*3.14159265/180)) + myTrans[0];
    //myMinY = myScale[1] * (this->box.getMinY() * cos(myRot[2]*3.14159265/180) - this->box.getMinX() * sin(myRot[2]*3.14159265/180)) + myTrans[1];
    //myMaxX = myScale[0] * (this->box.getMaxX() * cos(myRot[2]*3.14159265/180) + this->box.getMaxY() * sin(myRot[2]*3.14159265/180)) + myTrans[0];
    //myMaxY = myScale[1] * (this->box.getMaxY() * cos(myRot[2]*3.14159265/180) - this->box.getMaxX() * sin(myRot[2]*3.14159265/180)) + myTrans[1];

    //calculations for object that called this function
    myxTopLeft = myScale[0] * (this->box.getMinX() * cos(myRot[2]*3.14159265/180) - this->box.getMaxY() * sin(myRot[2]*3.14159265/180)) + myTrans[0];
    myxTopRight = myScale[0] * (this->box.getMaxX() * cos(myRot[2]*3.14159265/180) - this->box.getMaxY() * sin(myRot[2]*3.14159265/180)) + myTrans[0];
    myxBottomLeft = myScale[0] * (this->box.getMinX() * cos(myRot[2]*3.14159265/180) - this->box.getMinY() * sin(myRot[2]*3.14159265/180)) + myTrans[0];
    myxBottomRight = myScale[0] * (this->box.getMaxX() * cos(myRot[2]*3.14159265/180) - this->box.getMinY() * sin(myRot[2]*3.14159265/180)) + myTrans[0];

    myyTopLeft = myScale[1] * (this->box.getMaxY() * cos(myRot[2]*3.14159265/180) + this->box.getMinX() * sin(myRot[2]*3.14159265/180)) + myTrans[1];
    myyTopRight = myScale[1] * (this->box.getMaxY() * cos(myRot[2]*3.14159265/180) + this->box.getMaxX() * sin(myRot[2]*3.14159265/180)) + myTrans[1];
    myyBottomLeft = myScale[1] * (this->box.getMinY() * cos(myRot[2]*3.14159265/180) + this->box.getMinX() * sin(myRot[2]*3.14159265/180)) + myTrans[1];
    myyBottomRight = myScale[1] * (this->box.getMinY() * cos(myRot[2]*3.14159265/180) + this->box.getMaxX() * sin(myRot[2]*3.14159265/180)) + myTrans[1];

    myMinX = myxTopLeft;
    myxTopRight < myMinX ? myMinX = myxTopRight : myMinX;
    myxBottomLeft < myMinX ? myMinX = myxBottomLeft : myMinX;
    myxBottomRight < myMinX ? myMinX = myxBottomRight : myMinX;

    myMinY = myyTopLeft;
    myyTopRight < myMinY ? myMinY = myyTopRight : myMinY;
    myyBottomLeft < myMinY ? myMinY = myyBottomLeft : myMinY;
    myyBottomRight < myMinY ? myMinY = myyBottomRight : myMinY;

    myMaxX = myxTopLeft;
    myxTopRight > myMaxX ? myMaxX = myxTopRight : myMaxX;
    myxBottomLeft > myMaxX ? myMaxX = myxBottomLeft : myMaxX;
    myxBottomRight > myMaxX ? myMaxX = myxBottomRight : myMaxX;

    myMaxY = myyTopLeft;
    myyTopRight > myMaxY ? myMaxY = myyTopRight : myMaxY;
    myyBottomLeft > myMaxY ? myMaxY = myyBottomLeft : myMaxY;
    myyBottomRight > myMaxY ? myMaxY = myyBottomRight : myMaxY;

    //calculations for the mesh we are comparing to
    otherxTopLeft = otherScale[0] * (otherMesh->getBox().getMinX() * cos(otherRot[2]*3.14159265/180) - otherMesh->getBox().getMaxY() * sin(otherRot[2]*3.14159265/180)) + otherTrans[0];
    otherxTopRight = otherScale[0] * (otherMesh->getBox().getMaxX() * cos(otherRot[2]*3.14159265/180) - otherMesh->getBox().getMaxY() * sin(otherRot[2]*3.14159265/180)) + otherTrans[0];
    otherxBottomLeft = otherScale[0] * (otherMesh->getBox().getMinX() * cos(otherRot[2]*3.14159265/180) - otherMesh->getBox().getMinY() * sin(otherRot[2]*3.14159265/180)) + otherTrans[0];
    otherxBottomRight = otherScale[0] * (otherMesh->getBox().getMaxX() * cos(otherRot[2]*3.14159265/180) - otherMesh->getBox().getMinY() * sin(otherRot[2]*3.14159265/180)) + otherTrans[0];

    otheryTopLeft = otherScale[1] * (otherMesh->getBox().getMaxY() * cos(otherRot[2]*3.14159265/180) + otherMesh->getBox().getMinX() * sin(otherRot[2]*3.14159265/180)) + otherTrans[1];
    otheryTopRight = otherScale[1] * (otherMesh->getBox().getMaxY() * cos(otherRot[2]*3.14159265/180) + otherMesh->getBox().getMaxX() * sin(otherRot[2]*3.14159265/180)) + otherTrans[1];
    otheryBottomLeft = otherScale[1] * (otherMesh->getBox().getMinY() * cos(otherRot[2]*3.14159265/180) + otherMesh->getBox().getMinX() * sin(otherRot[2]*3.14159265/180)) + otherTrans[1];
    otheryBottomRight = otherScale[1] * (otherMesh->getBox().getMinY() * cos(otherRot[2]*3.14159265/180) + otherMesh->getBox().getMaxX() * sin(otherRot[2]*3.14159265/180)) + otherTrans[1];

    otherMinX = otherxTopLeft;
    otherxTopRight < otherMinX ? otherMinX = otherxTopRight : otherMinX;
    otherxBottomLeft < otherMinX ? otherMinX = otherxBottomLeft : otherMinX;
    otherxBottomRight < otherMinX ? otherMinX = otherxBottomRight : otherMinX;

    otherMinY = otheryTopLeft;
    otheryTopRight < otherMinY ? otherMinY = otheryTopRight : otherMinY;
    otheryBottomLeft < otherMinY ? otherMinY = otheryBottomLeft : otherMinY;
    otheryBottomRight < otherMinY ? otherMinY = otheryBottomRight : otherMinY;

    otherMaxX = otherxTopLeft;
    otherxTopRight > otherMaxX ? otherMaxX = otherxTopRight : otherMaxX;
    otherxBottomLeft > otherMaxX ? otherMaxX = otherxBottomLeft : otherMaxX;
    otherxBottomRight > otherMaxX ? otherMaxX = otherxBottomRight : otherMaxX;

    otherMaxY = otheryTopLeft;
    otheryTopRight > otherMaxY ? otherMaxY = otheryTopRight : otherMaxY;
    otheryBottomLeft > otherMaxY ? otherMaxY = otheryBottomLeft : otherMaxY;
    otheryBottomRight > otherMaxY ? otherMaxY = otheryBottomRight : otherMaxY;


    //qDebug()<<"myMinX" <<myMinX <<"myMaxX" <<myMaxX <<"myMinY" <<myMinY <<"myMaxY" <<myMaxY;
    /*if(myMaxX < myMinX)
    {
        temp = myMinX;
        myMinX = myMaxX;
        myMaxX = temp;
    }*/
    //qDebug()<<"this->box.getMinX()" <<this->box.getMaxX() <<"this->box.getMinY()" <<this->box.getMaxY();
    //qDebug()<<"cos(myRot[2]*3.14159265/180)" << cos(myRot[2]*3.14159265/180) <<"sin(myRot[2]*3.14159265/180)" <<sin(myRot[2]*3.14159265/180);
    //qDebug()<<"getMinX" <<this->box.getMinX() <<"cos" <<cos(myRot[2]*3.14159265/180) <<"getMaxY" <<this->box.getMaxY() <<"sin" <<sin(-myRot[2]*3.14159265/180);
    //qDebug()<<"this->box.getMinX()" <<myScale[0]*this->box.getMinX() + myTrans[0] <<"this->box.getMaxX()" <<myScale[0]*this->box.getMaxX() <<"this->box.getMinY()" <<myScale[1]*this->box.getMinY() <<"this->box.getMaxY()" <<myScale[1]*this->box.getMaxY();

    //qDebug()<<"myxTopLeft" << myxTopLeft <<"myxTopRight" <<myxTopRight <<"myxBottomLeft" <<myxBottomLeft << "myxBottomRight" <<myxBottomRight <<"myMinX" <<myMinX;
    //qDebug()<<"yTopLeft" << yTopLeft <<"yTopRight" <<yTopRight <<"yBottomLeft" <<yBottomLeft << "yBottomRight" <<yBottomRight ;

    //otherMinX = otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0];
    //otherMinY = otherScale[1]*otherMesh->getBox().getMinY() + otherTrans[1];
    //otherMaxX = otherScale[0]*otherMesh->getBox().getMaxX() + otherTrans[0];
    //otherMaxY = otherScale[1]*otherMesh->getBox().getMaxY() + otherTrans[1];

    //this->translation[0] -= ((this->velocity+bounce)*sin(this->rotation[2]*3.14159265/180));
    //this->translation[1] += ((this->velocity+bounce)*cos(this->rotation[2]*3.14159265/180));
    //qDebug()<<"Rotation:" <<myRot[2] <<cos(myRot[2]*3.14159265/180)*myMaxX + sin(myRot[2]*3.14159265/180)*myMaxY <<"myMaxY" <<cos(myRot[2]*3.14159265/180)*myMaxY - sin(myRot[2]*3.14159265/180)*myMaxX;
    //qDebug()<<"otMinX" << otherMinX <<"otMaxX" <<otherMaxX;

    //this->translation[0] -= ((3.0f * msec/100)*sin(this->rotation[2]*3.14159265/180));
    //this->translation[1] += ((3.0f * msec/100)*cos(this->rotation[2]*3.14159265/180));

    //qDebug()<<myScale[0]*this->box.getMinX() + myTrans[0] <<otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0] << myScale[0]*this->box.getMaxX() +myTrans[0];
    //qDebug()<<"Checking for collision";
    //qDebug()<<"My Real minX: " <<myScale[0]*box.getMinX() + myTrans[0] <<"My Real maxX: " <<myScale[0]*box.getMaxX() + myTrans[0];
    //qDebug()<<"sin(myRot[2]*3.1415 9265/180" <<sin(myRot[2]*3.14159265/180);
    //qDebug()<<"My Real minX: " <<myScale[0]*this->box.getMinX()+abs(sin(myRot[2]*3.14159265/180)) + myTrans[0] <<"My Real maxX: " <<myScale[0]*this->box.getMaxX()+abs(sin(myRot[2]*3.14159265/180)) + myTrans[0];
    //qDebug()<<"Ot Real minX: " <<otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0] <<"Ot Real maxX: " <<otherScale[0]*otherMesh->getBox().getMaxX() + otherTrans[0];


    if ((myMinX >= otherMinX && myMinX <= otherMaxX) || (myMaxX <= otherMaxX && myMaxX >= otherMinX))
    {
        if ((myMinY >= otherMinY && myMinY <= otherMaxY) || (myMaxY <= otherMaxY && myMaxY >= otherMinY))
        {
            collisionFlag = true;
            if (this->name() == "projectile" || otherMesh->name() == "projectile")
                qDebug()<<"projectile collision!!!";
        }

    }

    /*  Currently used:
     *     if (myScale[0]*this->box.getMinX() + myTrans[0] <= otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0] && myScale[0]*this->box.getMaxX() +myTrans[0] >= otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0])
    {
        if (myScale[1]*this->box.getMinY() + myTrans[1] <= otherScale[1]*otherMesh->getBox().getMinY() + otherTrans[1] && myScale[1]*this->box.getMaxY() +myTrans[1] >= otherScale[1]*otherMesh->getBox().getMinY() + otherTrans[1])
        {
            collisionFlag = true;
        }

    }*/

    /* Original without Rotation
    if (myScale[0]*this->box.getMinX() + myTrans[0] <= otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0] && myScale[0]*this->box.getMaxX() +myTrans[0] >= otherScale[0]*otherMesh->getBox().getMinX() + otherTrans[0])
    {
        if (myScale[1]*this->box.getMinY() + myTrans[1] <= otherScale[1]*otherMesh->getBox().getMinY() + otherTrans[1] && myScale[1]*this->box.getMaxY() +myTrans[1] >= otherScale[1]*otherMesh->getBox().getMinY() + otherTrans[1])
        {
            collisionFlag = true;
        }

    }*/

    //    if (collisionFlag)
    //qDebug()<<"COLLISION";
    //else
    //qDebug()<<"NO COLLISION";
    

    return collisionFlag;
}

// bool openGLMesh::isDescructable()
// {
//     return this->destructible;
// }

// void openGLMesh::destroy()
// {
//     this->alive = false;

//     return;
// }

// bool openGLMesh::isAlive()
// {
//     return this->alive;
// }

QString openGLMesh::name()
{
    return "openGLMesh";
}
