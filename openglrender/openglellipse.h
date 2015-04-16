#ifndef OPENGLELLIPSE_H
#define OPENGLELLIPSE_H

#include "openglobject.h"
#include "math.h"

class openGLEllipse : public openGLObject
{
public:
    openGLEllipse();
    openGLEllipse(const int &newCX, const int &newCY);
    openGLEllipse(const int &newCX, const int &newCY, const int &newRX, const int &newRY, const int &newTheta);
    ~openGLEllipse();

    //Get methods
    QColor getColor();
    int getCX();
    int getCY();
    int getRX();
    int getRY();
    int getTheta();
    QString getType();

    //Set methods
    void setColor(const QColor &newColor);
    void setCX(const int &newCX);
    void setCY(const int &newCY);
    void setRX(const int &newRX);
    void setRY(const int &newRY);
    void setTheta(const int &newTheta);
    void setType(QString &newType);

    void draw();

    QString name();

    //void update(int newX, int newY);

private:

    QColor color;

    int cx;
    int cy;
    int rx;
    int ry;
    int theta;

    QString type;

    void bresenham(int x, int y, const int &rxSq, const int &rySq, const float &pk, const float &cos, const float &sin);
    void bresenham2(int x, int y, const int &rxSq, const int &rySq, const float &pk, const float &cos, const float &sin);
};

#endif // OPENGLELLIPSE_H
