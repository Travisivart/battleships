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

#define GAME_MODE 0
#define MENU_MODE 1

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

    //Operations on the object list
    bool isEmpty();
    int size();
    void removeAt(int i);
    void push(openGLObject *newObj);
    openGLObject* pop();
    openGLObject* at(const int i);

    void setBackgroundColor(int newRed, int newGreen, int newBlue, int newAlpha);

protected:

    // void paintGL();
    void resizeGL(int width, int height);

private:

    GLint mode;

    void draw();

    QList<openGLObject*> *objects;
    int selectedObj;

    QList<_GLMmodel*> *models;

    openGLCamera *camera;
};

#endif // OPENGLRENDER_H
