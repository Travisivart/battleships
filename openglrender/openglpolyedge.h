#ifndef OPENGLPOLYEDGE_H
#define OPENGLPOLYEDGE_H

#include <QPoint>
#include "openglobject.h"
#include "openglpoint.h"

class openGLPolyEdge : public openGLObject
{
public:
    openGLPolyEdge();
    ~openGLPolyEdge();

    //Set methods
    void setP1(openGLPoint* newP1);
    void setP2(openGLPoint* newP2);
    void setColor(const QColor newColor);

    //Get methods
    int getWidth();
    QColor getColor();

protected:
    openGLPoint* p1;
    openGLPoint* p2;
    QColor color;
    int width;
};

#endif // OPENGLPOLYEDGE_H
