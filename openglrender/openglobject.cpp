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


bool openGLObject::isDescructable()
{
    return this->destructible;
}

void openGLObject::destroy()
{
    this->alive = false;
    qDebug()<<"object destroyed";
    return;
}
bool openGLObject::isAlive()
{
    return this->alive;
}

