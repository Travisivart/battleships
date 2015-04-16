#ifndef OPENGLCIRCLE_H
#define OPENGLCIRCLE_H

#include "openglobject.h"

enum CircleType{FULL, SEMINORTH, SEMIEAST, SEMISOUTH, SEMIWEST, QUADNW, QUADNE, QUADSE, QUADSW};

class openGLCircle : public openGLObject
{
public:
    openGLCircle();
    openGLCircle(const int newX, const int newY, const int newR);
    ~openGLCircle();

    //Get methods
    QColor getColor();
    QColor getFillColor();
    int getX();
    int getY();
    int getR();
    QString getType();
    bool isFilled();

    //Set methods
    void setColor(const QColor &newColor);
    void setFillColor(const QColor &newFillColor);
    void setX(const int newX);
    void setY(const int newY);
    void setR(const int newR);
    void setType(QString newType);
    void setFilled(const bool &newFilled);

    void draw();

    QString name();

    void update(int newX, int newY);

private:

    QColor color;
    QColor fillColor;

    int x;
    int y;
    int r;

    bool filled;

    QString type;

    void bresenham(const int newX, const int newY, const int newR, const int s);
    void bresenhamLine(int x1, int y1, int x2, int y2);

};

#endif // OPENGLCIRCLE_H
