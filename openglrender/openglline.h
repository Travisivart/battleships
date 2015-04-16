#ifndef OPENGLLINE_H
#define OPENGLLINE_H

#include <QColor>
#include <QPoint>
#include <QDebug>
#include <QtOpenGL/QGL>
#include "openglobject.h"
#include "openglpoint.h"

class openGLLine : public openGLObject
{
public:
    enum LineStyle { Line, Dot, Dash, Dash_Dot };

    openGLLine();
    openGLLine(openGLPoint* newP1, openGLPoint* newP2);
    openGLLine(const float &newX1, const float &newY1, const float &newX2, const float &newY2);
    openGLLine(const float &newX1, const float &newY1, const float &newZ1, const float &newX2, const float &newY2, const float newZ2);
    openGLLine(const float &newX1, const float &newY1, const float &newX2, const float &newY2, const QColor &newColor);
    ~openGLLine();

    //Set methods
    void setColor(const QColor &newColor);
    void setStyle(const QString &newStyle);
    void setP1(const float &x1, const float &y1);
    void setP1(const float &x1, const float &y1, const float &z1);
    void setP1(openGLPoint* newP1);
    void setP2(const float &x2, const float &y2);
    void setP2(const float &x2, const float &y2, const float &z2);
    void setP2(openGLPoint* newP2);
    void setWidth(const int &newWidth);

    //Get methods
    openGLPoint* getP1();
    openGLPoint* getP2();
    QColor getColor();
    float x1();
    float y1();
    float z1();
    float x2();
    float y2();
    float z2();
    int getWidth();

    void draw();

    QString name();

private:

    openGLPoint* p1;
    openGLPoint* p2;
    QColor color;

    int width;
    QString style;

    void bresenham(openGLPoint* bp1, openGLPoint* bp2, const int pk);


};

#endif // OPENGLLINE_H
