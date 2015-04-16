#ifndef OPENGLPOINT_H
#define OPENGLPOINT_H

#include <QtOpenGL/QGL>
#include <QDebug>

#include "openglobject.h"


class openGLPoint : public openGLObject
{
public:
    openGLPoint();
    openGLPoint(const float &newX, const float &newY);
    openGLPoint(const float &newX, const float &newY, const QColor &newColor);
    openGLPoint(const float &newX, const float &newY, const float &newZ);
    openGLPoint(const float &newX, const float &newY, const float &newZ, const QColor &newColor);
    ~openGLPoint();

    //Set methods
    void setX(const float &newX);
    void setY(const float &newY);
    void setZ(const float &newZ);
    void setColor(const QColor &newColor);

    float getX();
    float getY();
    float getZ();
    QColor getColor();

    void draw();

    QString name();

private:
    float x;
    float y;
    float z;

    QColor color;
};

#endif // OPENGLPOINT_H
