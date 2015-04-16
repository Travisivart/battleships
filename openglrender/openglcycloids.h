#ifndef OPENGLCYCLOIDS_H
#define OPENGLCYCLOIDS_H

#include "openglobject.h"
#include "openglcircle.h"
#include "math.h"

class openGLCycloids : public openGLObject
{
public:
    openGLCycloids();
    ~openGLCycloids();

    //Get methods
    int getX1();
    int getY1();
    int getX2();
    int getY2();
    int getR1();
    int getR2();
    int getTheta();

    void setX1(const int &newX1);

    void draw();
    void drawCycloid(float x, float y, int r1, int r2, int theta);

private:

    QColor color;

    int x1;
    int y1;
    int x2;
    int y2;

    int r1;
    int r2;

    int theta;

    openGLCircle *c1;
    openGLCircle *c2;
};

#endif // OPENGLCYCLOIDS_H
