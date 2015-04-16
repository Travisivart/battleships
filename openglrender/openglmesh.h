#ifndef OPENGLMESH_H
#define OPENGLMESH_H

#include "openglobject.h"

#include "tutor/glm.h"

class openGLMesh : public openGLObject
{
public:
    openGLMesh();
    openGLMesh(const QString newFilename);
    ~openGLMesh();

    //Set methods
    void translate(GLfloat newX, GLfloat newY, GLfloat newZ);
    void translate(GLfloat *newTranslation);
    void rotate(GLfloat newX, GLfloat newY, GLfloat newZ);
    void rotate(GLfloat *newRotation);
    void scale(GLfloat newX, GLfloat newY, GLfloat newZ);
    void scale(GLfloat *newScaling);
    void setMode(int GLM_MODE);

    //Get methods
    GLfloat* getTranslation();
    GLfloat* getRotation();
    GLfloat* getScaling();

    //Load an object into memory from filename.
    void load(QString filename);

    //Deleted the mesh if one has been loaded.
    void deleteMesh();

    //If the mesh was created with an object file, then return the filename used.
    QString getFilename();

    //Draw the mesh
    void draw();

    //Returns the object's name
    QString name();

protected:
    GLMmodel *mesh;

    GLfloat translation[3];

    GLfloat rotation[3];

    GLfloat scaling[3];

    //The GLM_MODE which we are using to render the mesh.
    int mode;

    //The location of the .obj file
    QString filename;
};

#endif // OPENGLMESH_H
