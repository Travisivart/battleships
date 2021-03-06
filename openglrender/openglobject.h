#ifndef OPENGLOBJECT_H
#define OPENGLOBJECT_H

#include <QString>
#include <QDebug>
#include <QtOpenGL/QGL>

#include "openglcamera.h"

#define OGLWIDTH 1520
#define OGLHEIGHT 700

#define TRAVDEBUG FALSE

class openGLObject
{
public:
    openGLObject();
    virtual ~openGLObject();

    void virtual draw();

    void virtual draw(openGLCamera *c);

    QString virtual name();

    void virtual update();

    bool isCurrent();
    void setCurrent(const bool &newCurrent);

    void setDebug(const bool &d);
    bool isDescructable();
    bool isAlive();
    void destroy();


protected:
    bool current;
    bool debug;
    bool destructible;
    bool alive;
};

#endif // OPENGLOBJECT_H
