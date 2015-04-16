#include "renderarea.h"

#include <QPainter>
#include <QDebug>

//! [0]
RenderArea::RenderArea (QOpenGLWidget *parent)//(QWidget *parent)
    : QOpenGLWidget(parent) //: QWidget(parent)
{
    //shape = Polygon;
    //antialiased = false;
    //transformed = false;
    //pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //qDebug() << list.size();
    //list.push_front(new QOpenGLWidget());
    // qDebug() << list.size();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(600, 500);
}


void RenderArea::push(QLine *item)
{
    list.push_back(item);
}

QLine* RenderArea::pop()
{
    if (list.isEmpty())
            return new QLine();

    return list.last();
}

void RenderArea::add(QLine *item)
{
    list.push_back(item);

    return;
}

void RenderArea::clearList()
{
    list.clear();
}

void RenderArea::clear()
{
    QPainter painter(this);

    painter.eraseRect(0,0,600,500);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();

    foreach(QLine* l, list)
    {
        painter.drawLine(l->x1()-this->x(),l->y1()-this->y(),l->x2()-this->x(),l->y2()-this->y());
    }
    painter.restore();

}

