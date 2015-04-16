#include "edge.h"

edge::edge()
{

}

edge::edge(const float &newxMin, const int &newyMax, const int &newDx, const int &newDy)
{
    this->xMin = newxMin;
    this->yMax = newyMax;
    this->dx = newDx;
    this->dy = newDy;

    this->colorP1.setRed(0);
    this->colorP1.setGreen(0);
    this->colorP1.setBlue(0);

    this->colorP2.setRed(0);
    this->colorP2.setGreen(0);
    this->colorP2.setBlue(0);
}

edge::edge(const float &newxMin, const int &newyMax, const int &newDx, const int &newDy, const QColor &newColorP1, const QColor &newColorP2, const float &newColorConstRed, const float &newColorConstGreen, const float &newColorConstBlue)
{
    this->xMin = newxMin;
    this->yMax = newyMax;
    this->dx = newDx;
    this->dy = newDy;

    this->colorP1.setRed(newColorP1.red());
    this->colorP1.setGreen(newColorP1.green());
    this->colorP1.setBlue(newColorP1.blue());

    this->colorP2.setRed(newColorP2.red());
    this->colorP2.setGreen(newColorP2.green());
    this->colorP2.setBlue(newColorP2.blue());

    this->colorConstRed = newColorConstRed;
    this->colorConstGreen = newColorConstGreen;
    this->colorConstBlue = newColorConstBlue;
}

edge::~edge()
{

}

float edge::getXMin()
{
    return this->xMin;
}

int edge::getYMax()
{
    return this->yMax;
}

int edge::getDx()
{
    return this->dx;
}

int edge::getDy()
{
    return this->dy;
}

QColor edge::getColorP1()
{
    return this->colorP1;
}

QColor edge::getColorP2()
{
    return this->colorP2;
}

void edge::setXMin(const float &newxMin)
{
    this->xMin = newxMin;
}

void edge::setYMax(const int &newyMax)
{
    this->yMax = newyMax;
}

void edge::setDx(const int &newDx)
{
    this->dx = newDx;
}

void edge::setDy(const int &newDy)
{
    this->dy = newDy;
}

void edge::setColor(const QColor &newColorP1, const QColor &newColorP2)
{
    this->colorP1 = newColorP1;
    this->colorP2 = newColorP2;
}
/*
void edge::setColorConst(const float &newColorConst)
{
    this->colorConst = newColorConst;
}*/

void edge::updateColors()
{
    //this->colorP1.setRedF(this->getColorP1().redF()+this->colorConstRed);
    //this->colorP1.setGreenF(this->getColorP1().greenF()+this->colorConstGreen);
    //this->colorP1.setBlueF(this->getColorP1().blueF()+this->colorConstBlue);

    this->colorP1.setRed(this->getColorP1().red()+this->colorConstRed > 255 ? 255 : this->getColorP1().red()+this->colorConstRed < 0 ? 0 : this->getColorP1().red()+this->colorConstRed);
    this->colorP1.setGreen(this->getColorP1().green()+this->colorConstGreen > 255 ? 255 : this->getColorP1().green()+this->colorConstGreen < 0 ? 0 : this->getColorP1().green()+this->colorConstGreen);
    this->colorP1.setBlue(this->getColorP1().blue()+this->colorConstBlue > 255 ? 255 : this->getColorP1().blue()+this->colorConstBlue < 0 ? 0 : this->getColorP1().blue()+this->colorConstBlue);
}
