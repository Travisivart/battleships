#ifndef OPENGLMESH_H
#define OPENGLMESH_H

#include "openglobject.h"
#include "boundingbox.h"

#include "math.h"
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
    _GLMmodel *getMesh();
    boundingBox getBox();

    //Load an object into memory from filename.
    void load(QString filename);

    //Delete the mesh if one has been loaded.
    void deleteMesh();

    //If the mesh was created with an object file, then return the filename used.
    QString getFilename();

    //Update the mesh
    void update(const int &msec);

    //Draw the mesh
    void draw();

    //Draw the mesh relative to a camera
    void draw(openGLCamera *c);

    bool checkCollision(openGLMesh *otherMesh);

    bool isDescructable();
    void destroy();
    bool isAlive();

    //Returns the object's name
    QString name();

    float v;

protected:

    GLMmodel *mesh;
    boundingBox box;

    GLfloat translation[3];
    GLfloat rotation[3];
    GLfloat scaling[3];

    //The GLM_MODE which we are using to render the mesh.
    int mode;

    //The location of the .obj file
    QString filename;

    bool destructible;
    bool alive;
};

#endif // OPENGLMESH_H
