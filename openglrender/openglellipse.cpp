#include "openglellipse.h"

openGLEllipse::openGLEllipse()
{
    cx = 0;
    cy = 0;
    rx = 0;
    ry = 0;
    theta = 0;
}

openGLEllipse::openGLEllipse(const int &newCX, const int &newCY)
{
    cx = newCX;
    cy = newCY;
    rx = 0;
    ry = 0;
    theta = 0;
}

openGLEllipse::openGLEllipse(const int &newCX, const int &newCY, const int &newRX, const int &newRY, const int &newTheta)
{
    cx = newCX;
    cy = newCY;
    rx = newRX;
    ry = newRY;
    theta = newTheta;
}

openGLEllipse::~openGLEllipse()
{

}

QColor openGLEllipse::getColor()
{
    return this->color;
}

int openGLEllipse::getCX()
{
    return this->cx;
}

int openGLEllipse::getCY()
{
    return this->cy;
}

int openGLEllipse::getRX()
{
    return this->rx;
}

int openGLEllipse::getRY()
{
    return this->ry;
}

QString openGLEllipse::getType()
{
    return this->type;
}

//Set methods
void openGLEllipse::setColor(const QColor &newColor)
{
    color = newColor;
}

void openGLEllipse::setCX(const int &newCX)
{
    this->cx = newCX;
}

void openGLEllipse::setCY(const int &newCY)
{
    this->cy = newCY;
}

void openGLEllipse::setRX(const int &newRX)
{
    this->rx = newRX;
}

void openGLEllipse::setRY(const int &newRY)
{
    this->ry = newRY;
}

void openGLEllipse::setTheta(const int &newTheta)
{
    this->theta = newTheta;
}

void openGLEllipse::setType(QString &newType)
{
    this->type = newType;
}

void openGLEllipse::draw()
{
    glColor3f((float)this->getColor().red()/255, (float)this->getColor().green()/255, (float)this->getColor().blue()/255);

    float newPk = (ry*ry)-(rx*rx)*ry + (1/4)*rx*rx;
    float newCos = cos(((float)theta* 3.1415) /180);
    float newSin = sin(((float)theta* 3.1415) /180);

    glVertex2f((float)((0+cx)*newCos-(ry+cy)*newSin)/(OGLWIDTH),(float)((ry+cy)*newCos+(0+cx)*newSin)/OGLHEIGHT);
    glVertex2f((float)((0+cx)*newCos-(-ry+cy)*newSin)/(OGLWIDTH),(float)((-ry+cy)*newCos+(0+cx)*newSin)/OGLHEIGHT);
    glVertex2f((float)((rx+cx)*newCos-(0+cy)*newSin)/(OGLWIDTH),(float)((0+cy)*newCos+(rx+cx)*newSin)/OGLHEIGHT);
    glVertex2f((float)((-rx+cx)*newCos-(0+cy)*newSin)/(OGLWIDTH),(float)((0+cy)*newCos+(-rx+cx)*newSin)/OGLHEIGHT);

    bresenham(0, ry, rx*rx, ry*ry, newPk, newCos, newSin);
}

QString openGLEllipse::name()
{
    return QString("openGLEllipse");
}

void openGLEllipse::bresenham(int x, int y, const int &rxSq, const int &rySq, const float &pk, const float &cos, const float &sin)
{
    //qDebug()<<"Ellipse: Bresenham: cx:" <<cx <<"cy:" <<cy <<"rx:" <<rx <<"ry:" <<ry <<"rxSq:" << rxSq <<"rySq:" <<rySq <<"pk:" <<pk;

    if(rySq*x <= rxSq*y)
    {
        if (pk < 0)
        {
            ++x;
            glVertex2f((float)((x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            bresenham(x, y, rxSq, rySq, pk + 2*rySq*x + rySq, cos, sin);
        }
        else
        {
            ++x;
            --y;
            glVertex2f((float)((x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            bresenham(x, y, rxSq, rySq, pk + 2*rySq*x + rySq - 2*rxSq*y, cos, sin);
        }
    }
    else if(y>0)
    {
        float newPk =  rySq*(.25) + rxSq*(ry-1)*(ry-1) - rxSq*rySq;

        if (newPk > 0)
        {
            --y;
            glVertex2f((float)((x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
        }
        else
        {
            ++x;
            --y;
            glVertex2f((float)((x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
        }
        bresenham2(x, y, rxSq, rySq, newPk, cos, sin);
    }
    return;
}

void openGLEllipse::bresenham2(int x, int y, const int &rxSq, const int &rySq, const float &pk, const float &cos, const float &sin)
{
    if (y>0)
    {
        if (pk > 0)
        {
            --y;
            glVertex2f((float)((x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            bresenham2(x, y, rxSq, rySq, pk - 2*rxSq*y + rxSq, cos, sin);
        }
        else
        {
            ++x;
            --y;
            glVertex2f((float)((x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(y+cy)*sin)/(OGLWIDTH),(float)((y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            glVertex2f((float)((-x+cx)*cos-(-y+cy)*sin)/(OGLWIDTH),(float)((-y+cy)*cos+(-x+cx)*sin)/OGLHEIGHT);
            bresenham2(x, y, rxSq, rySq, pk - 2*rxSq*y + rxSq + 2*rySq*x, cos, sin);
        }
    }
}
