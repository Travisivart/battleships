#ifndef OPENGLOBJECT_H
#define OPENGLOBJECT_H

#include <QString>
#include <QDebug>
#include <QtOpenGL/QGL>

#define OGLWIDTH 950
#define OGLHEIGHT 700

#define TRAVDEBUG FALSE

class openGLObject
{
public:
    openGLObject();
    virtual ~openGLObject();

    void virtual draw();

    QString virtual name();

    void virtual update();

    bool isCurrent();
    void setCurrent(const bool &newCurrent);

    void setDebug(const bool &d);

protected:
    bool current;
    bool debug;
};

#endif // OPENGLOBJECT_H
