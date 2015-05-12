#include "openglcamera.h"

openGLCamera::openGLCamera()
{
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;
}

openGLCamera::~openGLCamera()
{

}

void openGLCamera::init()
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light0_ambient[] = { 5.0, 5.0, 5.0, 5.0 };
    GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light0_position[] = { 10.0, 10.0, 10.0, 10.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void openGLCamera::translate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->translation[0] = newX;
    this->translation[1] = newY;
    this->translation[2] = newZ;
}

void openGLCamera::translate(GLfloat *newTranslation)
{
    this->translation[0] = newTranslation[0];
    this->translation[1] = newTranslation[1];
    this->translation[2] = newTranslation[2];
}

void openGLCamera::rotate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->rotation[0] = fmod(newX, 360);
    this->rotation[1] = fmod(newY, 360);
    this->rotation[2] = fmod(newZ, 360);
}

void openGLCamera::rotate(GLfloat *newRotation)
{
    this->rotation[0] = fmod(newRotation[0], 360);
    this->rotation[1] = fmod(newRotation[1], 360);
    this->rotation[2] = fmod(newRotation[2], 360);
}

GLfloat* openGLCamera::getTranslation()
{
    return this->translation;
}

GLfloat* openGLCamera::getRotation()
{
    return this->rotation;
}
