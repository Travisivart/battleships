#ifndef OPENGLCAMERA_H
#define OPENGLCAMERA_H

#include <QtOpenGL/QGL>

class openGLCamera
{
public:
    openGLCamera();
    ~openGLCamera();

private:
    GLfloat cameraLeft;
    GLfloat cameraRight;
    GLfloat cameraBottom;
    GLfloat cameraTop;
    GLfloat cameraNear;
    GLfloat cameraFar;
};

#endif // OPENGLCAMERA_H
