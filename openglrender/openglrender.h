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

    /*****Input queue functions*****/

    //When a user presses a key, push it onto the input queue.
    void pushInput(const quint32 &newKey);
    void popInput(const quint32 &newKey);
    void processInput();

    //Update all objects based upon how much time has passed.
    void update(const int &msec);

    //Spawn enemies around the map
    void spawnEnemies();

protected:

    // void paintGL();
    void resizeGL(int width, int height);

private:

    GLint mode;

    void draw();

    QList<openGLObject*> *objects;
    int selectedObj;

    QList<_GLMmodel*> *models;
    _GLMmodel *player;

    openGLCamera *camera;

    QList<quint32> *inputQueue;

    unsigned char* bitmapData; // the texture data
};

#endif // OPENGLRENDER_H
