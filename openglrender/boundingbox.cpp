#include "boundingbox.h"
#include "../tutor/glm.h"

boundingBox::boundingBox()
{
    this->minX = 0.0f;
    this->minY = 0.0f;
    this->minZ = 0.0f;
    this->maxX = 0.0f;
    this->maxY = 0.0f;
    this->maxZ = 0.0f;
}

boundingBox::~boundingBox()
{

}

float boundingBox::getMinX()
{
    return this->minX;
}

float boundingBox::getMinY()
{
    return this->minY;
}

float boundingBox::getMinZ()
{
    return this->minZ;
}

float boundingBox::getMaxX()
{
    return this->maxX;
}

float boundingBox::getMaxY()
{
    return this->maxY;
}

float boundingBox::getMaxZ()
{
    return this->maxZ;
}

void boundingBox::calculateBox(GLMmodel *mesh)
{
    //Verticies start at i=1
    int i = 1;

    //Set initial min/max values
    this->minX = mesh->vertices[3*i + 0];
    this->minY = mesh->vertices[3*i + 1];
    this->minZ = mesh->vertices[3*i + 2];
    this->maxX = mesh->vertices[3*i + 0];
    this->maxY = mesh->vertices[3*i + 1];
    this->maxZ = mesh->vertices[3*i + 2];

    //qDebug()<<"numgroups: " <<mesh->numgroups;
    //for(int j = 1; j <2; j++)
        for( i = 2; i<= mesh->numvertices; i++)
        {
            //qDebug()<<mesh->vertices[3*i + 0] <<mesh->vertices[3*i + 1] <<mesh->vertices[3*i + 2];

            minX > mesh->vertices[3*i + 0] ? minX = mesh->vertices[3*i + 0] : maxX < mesh->vertices[3*i + 0] ? maxX = mesh->vertices[3*i + 0] : maxX;
            minY > mesh->vertices[3*i + 1] ? minY = mesh->vertices[3*i + 1] : maxY < mesh->vertices[3*i + 1] ? maxY = mesh->vertices[3*i + 1] : maxY;
            minZ > mesh->vertices[3*i + 2] ? minZ = mesh->vertices[3*i + 2] : maxZ < mesh->vertices[3*i + 2] ? maxZ = mesh->vertices[3*i + 2] : maxZ;
        }

    //qDebug()<<"minx" <<this->minX;
    //qDebug()<<"minY" <<this->minY;
    //qDebug()<<"minZ" <<this->minZ;
    //qDebug()<<"maxX" <<this->maxX;
    //qDebug()<<"maxY" <<this->maxY;
    //qDebug()<<"maxZ" <<this->maxZ;

}

bool boundingBox::possibleCollision(GLMmodel *mesh1, GLMmodel *mesh2)
{
    bool flag = false;
    return flag;
}

bool boundingBox::checkCollision(GLMmodel *mesh1, GLMmodel *mesh2)
{
    bool flag = false;

    /*
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f(this->minX, this->minY, this->minZ);
    glVertex3f(this->minX, this->minY, this->maxZ);

    glVertex3f(this->minX, this->minY, this->maxZ);
    glVertex3f(this->maxX, this->minY, this->maxZ);

    glVertex3f(this->maxX, this->minY, this->maxZ);
    glVertex3f(this->maxX, this->minY, this->minZ);

    glVertex3f(this->maxX, this->minY, this->minZ);
    glVertex3f(this->minX, this->minY, this->minZ);

    glVertex3f(this->minX, this->minY, this->minZ);
    glVertex3f(this->minX, this->maxY, this->minZ);

    glVertex3f(this->minX, this->minY, this->maxZ);
    glVertex3f(this->minX, this->maxY, this->maxZ);

    glVertex3f(this->maxX, this->minY, this->maxZ);
    glVertex3f(this->maxX, this->maxY, this->maxZ);

    glVertex3f(this->maxX, this->minY, this->minZ);
    glVertex3f(this->maxX, this->maxY, this->minZ);

    glVertex3f(this->minX, this->maxY, this->minZ);
    glVertex3f(this->minX, this->maxY, this->maxZ);

    glVertex3f(this->minX, this->maxY, this->maxZ);
    glVertex3f(this->maxX, this->maxY, this->maxZ);

    glVertex3f(this->maxX, this->maxY, this->maxZ);
    glVertex3f(this->maxX, this->maxY, this->minZ);

    glVertex3f(this->maxX, this->maxY, this->minZ);
    glVertex3f(this->minX, this->maxY, this->minZ);
    glEnd();
    */

    return flag;
}
