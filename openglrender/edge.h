#ifndef EDGE_H
#define EDGE_H

#include <QString>
#include <QColor>
#include <QDebug>

class edge
{
public:
    edge();
    edge(const float &newxMin, const int &newyMax, const int &newDx, const int &newDy);
    edge(const float &newxMin, const int &newyMax, const int &newDx, const int &newDy, const QColor &newColorP1, const QColor &newColorP2, const float &newColorConstRed, const float &newColorConstGreen, const float &newColorConstBlue);
    ~edge();

    //Get methods
    float getXMin();
    int getYMax();
    int getDx();
    int getDy();
    QColor getColorP1();
    QColor getColorP2();

    //Set methods
    void setXMin(const float &newxMin);
    void setYMax(const int &newyMax);
    void setDx(const int &newDx);
    void setDy(const int &newDy);
    void setColor(const QColor &newColorP1, const QColor &newColorP2);

    void updateColors();
    //void setColorConst(const float &newColorConst);

private:
    QString name;

    float xMin;
    int yMax;
    int dx;
    int dy;

    QColor colorP1;
    QColor colorP2;

    float colorConstRed;
    float colorConstGreen;
    float colorConstBlue;
};

#endif // EDGE_H
