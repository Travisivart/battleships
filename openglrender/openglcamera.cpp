#include "openglcamera.h"

openGLCamera::openGLCamera()
{
    cameraLeft = -1.0f;
    cameraRight = 1.0f;
    cameraBottom = -1.0f;
    cameraTop = 1.0f;
    cameraNear = -1.0f;
    cameraFar = 1.0f;
}

openGLCamera::~openGLCamera()
{

}

