#include "openglobject.h"

openGLObject::openGLObject()
{
    current = false;
    debug = false;
}

openGLObject::~openGLObject()
{

}

void openGLObject::draw()
{
}

void openGLObject::draw(openGLCamera *c)
{

}

QString openGLObject::name()
{
    return QString("openGLObject");
}

void openGLObject::update()
{
    return;
}

bool openGLObject::isCurrent()
{
    return current;
}

void openGLObject::setCurrent(const bool &newCurrent)
{
    current = newCurrent;
}

void openGLObject::setDebug(const bool &d)
{
    debug = d;
}
