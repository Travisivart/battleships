#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QList>
#include <QLine>
#include <QOpenGLWidget>

class RenderArea : public QOpenGLWidget //public QWidget
{
    Q_OBJECT

public:
    //enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
    //             Chord, Pie, Path, Text, Pixmap };

    RenderArea (QOpenGLWidget *parent = 0);//(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void add(QLine *item);
    void push(QLine *item);
    QLine* pop();
    void clearList();
    void clear();

public slots:
    //void setShape(Shape shape);
    //void setPen(const QPen &pen);
    //void setBrush(const QBrush &brush);
    //void setAntialiased(bool antialiased);
    //void setTransformed(bool transformed);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QList<QLine*> list;
    //Shape shape;
    //QPen pen;
    //QBrush brush;
    //bool antialiased;
    //bool transformed;
    //QPixmap pixmap;
};


#endif // RENDERAREA_H
