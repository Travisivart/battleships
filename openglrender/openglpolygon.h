#ifndef OPENGLPOLYGON_H
#define OPENGLPOLYGON_H

#include <QList>

#include "openglobject.h"
#include "openglpoint.h"
#include "bucket.h"


class openGLPolygon : public openGLObject
{
public:
    openGLPolygon();
    openGLPolygon(openGLPoint *start);
    openGLPolygon(QList<openGLPoint *> *newVertices);
    ~openGLPolygon();

    void add(openGLPoint *newVertex);

    openGLPoint* at(const int i);
    void removeAt(int i);

    void setColor(const QColor &newColor);
    void setClosed(const bool &newClosed);
    int size();

    void finish();
    void unFinish();
    bool isFinished();
    bool isFilled();
    void createSet();
    void setGoraud(const bool &newGoraud);
    //void floodFill(float x, float y);

    void draw();
    void drawFilled();
    void bresenham(openGLPoint* bp1, openGLPoint* bp2, const int pk);

    QString name();

private:

    bool closed;
    bool filled;
    bool finished;
    bool goraud;

    QList<openGLPoint*> *vertices;

    bucket* set;

    int yMin;
    int yMax;

    QColor color;
};

#endif // OPENGLPOLYGON_H
