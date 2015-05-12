#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include <QOpenGLWidget>
#include <QtOpenGL/QGL>
#include <QList>
#include <QLine>
#include <QTime>

#include "openglcircle.h"
#include "openglline.h"
#include "openglpolygon.h"
#include "openglellipse.h"
#include "openglcycloids.h"
#include "openglmesh.h"
#include "ship.h"
#include "openglcamera.h"
#include "../tutor/glm.h"

#define GAME_MODE 0
#define MENU_MODE 1

#ifdef __linux__
#include <stdint.h>
typedef unsigned short WORD;
typedef struct
{
    uint16_t bfType; //2 bytes storing "BM". This means that it is bmp
    uint32_t bfSize; //4 bytes total file size of bmp. Including both the header and pixel array
    uint16_t bfReserved1; //Always 0
    uint16_t bfReserved2; //Always 0
    uint32_t bfOffBits;   // stores 54. (40 +14)Total size of the headers.
} __attribute__((__packed__))
BITMAPFILEHEADER;

typedef struct
{
    uint32_t biSize; //40 bytes. Size of the header.
    int32_t biWidth; //Width of the bitmap image. How many pixel wide is the image.
    int32_t biHeight; //Height of the bitmap image.
    uint16_t biPlanes; // Always 1.
    uint16_t biBitCount; //24 for 24 bit bitmap. Number of bit representing each pixel.
    uint32_t biCompression;
    uint32_t biSizeImage; //Total size of bitmap pixel array including padding.
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;
#endif

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

    //Delete destroyed objects
    void removeDestroyedObjects();

    //Update the camera
    void updateCamera();

    void checkCollisions();

    static GLMmodel* load(QString filename);

    GLMmodel *ships;
protected:

    // void paintGL();
    void resizeGL(int width, int height);

private:

    GLint mode;

    void draw();

    QList<openGLObject*> *objects;
    int selectedObj;

    //QList<_GLMmodel*> *models;
    _GLMmodel *player;

    openGLCamera *camera;

    QList<quint32> *inputQueue;

    unsigned char* bitmapData; // the texture data
    unsigned char* bitmapData2;
};

#endif // OPENGLRENDER_H
