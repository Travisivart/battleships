#ifndef OPENGLCAMERA_H
#define OPENGLCAMERA_H

#include <QtOpenGL/QGL>

#include "math.h"

class openGLCamera
{
public:
    openGLCamera();
    ~openGLCamera();

    void init();

    //Set methods
    void translate(GLfloat newX, GLfloat newY, GLfloat newZ);
    void translate(GLfloat *newTranslation);
    void rotate(GLfloat newX, GLfloat newY, GLfloat newZ);
    void rotate(GLfloat *newRotation);

    //Get methods
    GLfloat* getTranslation();
    GLfloat* getRotation();

private:

    GLfloat translation[3];
    GLfloat rotation[3];
};

#endif // OPENGLCAMERA_H
