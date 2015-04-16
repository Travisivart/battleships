#include "openglpoint.h"
#include "openglobject.h"

openGLPoint::openGLPoint()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;

    this->current = false;
}

openGLPoint::openGLPoint(const float &newX, const float &newY)
{
    this->x = newX;
    this->y = newY;
    this->z = 0;

    this->current = false;
}

openGLPoint::openGLPoint(const float &newX, const float &newY, const QColor &newColor)
{
    this->x = newX;
    this->y = newY;
    this->z = 0;

    this->current = false;

    color = newColor;
}

openGLPoint::openGLPoint(const float &newX, const float &newY, const float &newZ)
{
    this->x = newX;
    this->y = newY;
    this->z = newZ;

    this->current = false;
}

openGLPoint::openGLPoint(const float &newX, const float &newY, const float &newZ, const QColor &newColor)
{
    this->x = newX;
    this->y = newY;
    this->z = newZ;

    this->current = false;

    color = newColor;
}

openGLPoint::~openGLPoint()
{

}

void openGLPoint::setX(const float &newX)
{
    this->x = newX;

    this->current = false;
}

void openGLPoint::setY(const float &newY)
{
    this->y = newY;

    this->current = false;
}

void openGLPoint::setZ(const float &newZ)
{
    this->z = newZ;

    this->current = false;
}

void openGLPoint::setColor(const QColor &newColor)
{
    this->color = newColor;

    this->current = false;
}

float openGLPoint::getX()
{
    return this->x;
}

float openGLPoint::getY()
{
    return this->y;
}

float openGLPoint::getZ()
{
    return this->z;
}

QColor openGLPoint::getColor()
{
    return this->color;
}

void openGLPoint::draw()
{
    glColor3f((float)(this->color.red()/255),(float)(this->color.green()/255),(float)(this->color.blue()/255));

    glVertex2f((float)(this->x/OGLWIDTH),(float)(this->y)/OGLHEIGHT);

    this->current = true;
}

QString openGLPoint::name()
{
    return QString("openGLPoint");
}
