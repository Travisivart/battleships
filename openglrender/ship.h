#ifndef SHIP_H
#define SHIP_H

#include "openglobject.h"
#include "boundingbox.h"
#include "openglmesh.h"
#include "math.h"
//#include "tutor/glm.h"
class openGLMesh;

class ship : public openGLMesh
{
public:
    ship();
    ship(const QString newFilename);
    ~ship();

    //Set methods
    float getVelocity();
    void increaseAcceleration();
    void decreaseAcceleration();


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
private:
    float acceleration, velocity,angle;

};

#endif // SHIP_H
