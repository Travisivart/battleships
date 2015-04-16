#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include <QOpenGLWidget>
#include <QtOpenGL/QGL>
#include <QList>
#include <QLine>
#include "openglcircle.h"
#include "openglline.h"
#include "openglpolygon.h"
#include "openglellipse.h"
#include "openglcycloids.h"
#include "openglmesh.h"
#include "openglcamera.h"

struct modelRot
{
    GLfloat angle;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
};

struct modelTrans
{
    GLfloat xTrans;
    GLfloat yTrans;
    GLfloat zTrans;
};


class openGLRender : public QGLWidget
{

public:
    explicit openGLRender(QWidget *parent  = 0);
    ~openGLRender();

    void initializeGL();

    void paintGL();
    void clearGL();
    void setColorGL(int newRed, int newGreen, int newBlue);
    void clearObjects();
    void setLineSizeGL(int newSize);

    bool isEmpty();
    int size();

    void removeAt(int i);
    void push(openGLObject *newObj);
    openGLObject* pop();

    openGLObject* at(const int i);

    void setBackgroundColor(int newRed, int newGreen, int newBlue, int newAlpha);

    QList<GLMmodel*> *m;

protected:

    // void paintGL();
    void resizeGL(int width, int height);

private:
    void draw();

    QList<openGLObject*> *objects;
    int selectedObj;

    QList<_GLMmodel*> *models;

    openGLCamera *camera;
};

//void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc);
void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m);

#endif // OPENGLRENDER_H
