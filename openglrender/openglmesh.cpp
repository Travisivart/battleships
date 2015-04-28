#include "openglmesh.h"

openGLMesh::openGLMesh()
{
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;

    this->scaling[0] = 1.0f;
    this->scaling[1] = 1.0f;
    this->scaling[2] = 1.0f;

    //#define GLM_NONE     (0)		/* render with only vertices */
    //#define GLM_FLAT     (1 << 0)		/* render with facet normals */
    //#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
    //#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
    //#define GLM_COLOR    (1 << 3)		/* render with colors */
    //#define GLM_MATERIAL (1 << 4)		/* render with materials */
    this->mode = GLM_MATERIAL;

    mesh = NULL;
}

openGLMesh::openGLMesh(const QString newFilename)
{
    qDebug()<<"Constructor: openGLMesh(" <<newFilename <<")";
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;

    this->scaling[0] = 1.0f;
    this->scaling[1] = 1.0f;
    this->scaling[2] = 1.0f;

    //#define GLM_NONE     (0)		/* render with only vertices */
    //#define GLM_FLAT     (1 << 0)		/* render with facet normals */
    //#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
    //#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
    //#define GLM_COLOR    (1 << 3)		/* render with colors */
    //#define GLM_MATERIAL (1 << 4)		/* render with materials */
    this->mode = GLM_MATERIAL;

    this->filename = newFilename;

    qDebug()<<"openGLMesh::openGLMesh(const QString newFilename)" <<"Attempting file load";
    this->load(this->filename);

    this->box.calculateBox(this->mesh);

    v = 1.0f;
}

openGLMesh::~openGLMesh()
{
    delete this->mesh;
}

void openGLMesh::translate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->translation[0] = newX;
    this->translation[1] = newY;
    this->translation[2] = newZ;
}

void openGLMesh::translate(GLfloat *newTranslation)
{
    this->translation[0] = newTranslation[0];
    this->translation[1] = newTranslation[1];
    this->translation[2] = newTranslation[2];
}

void openGLMesh::rotate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->rotation[0] = fmod(newX, 360);
    this->rotation[1] = fmod(newY, 360);
    this->rotation[2] = fmod(newZ, 360);
}

void openGLMesh::rotate(GLfloat *newRotation)
{
    this->rotation[0] = fmod(newRotation[0], 360);
    this->rotation[1] = fmod(newRotation[1], 360);
    this->rotation[2] = fmod(newRotation[2], 360);
}

void openGLMesh::scale(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->scaling[0] = newX;
    this->scaling[1] = newY;
    this->scaling[2] = newZ;
}

void openGLMesh::scale(GLfloat *newScaling)
{
    this->scaling[0] = newScaling[0];
    this->scaling[1] = newScaling[1];
    this->scaling[2] = newScaling[2];
}

void openGLMesh::setMode(int GLM_MODE)
{
    this->mode = GLM_MODE;
}

GLfloat* openGLMesh::getTranslation()
{
    return this->translation;
}

GLfloat* openGLMesh::getRotation()
{
    return this->rotation;
}

GLfloat* openGLMesh::getScaling()
{
    return this->scaling;
}

void openGLMesh::load(QString filename)
{
    qDebug()<<"openGLMesh::load(QString filename)";
    //Make sure that we are actually trying to load an existing file.
    if (filename != "")
    {
        //If something is already loaded into the mesh, then delete it.
        //if ( mesh != NULL )
        //deleteMesh();

        QByteArray ba = filename.toLatin1();
        char *c_str2 = ba.data();

        this->mesh = glmReadOBJ(c_str2);
    }
}

void openGLMesh::deleteMesh()
{
    delete this->mesh;
    mesh = NULL;
}

QString openGLMesh::getFilename()
{
    return this->filename;
}

void openGLMesh::update(const int &msec)
{

   // qDebug()<<"Updating for msec: " <<msec;
    this->translation[0] -= ((3.0f * msec/100)*sin(this->rotation[2]*3.14159265/180));
    //this->translation[1] += 1.0f * msec/1000;
    this->translation[1] += ((3.0f * msec/100)*cos(this->rotation[2]*3.14159265/180));
    //((openGLMesh*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
}

void openGLMesh::draw()
{
    glPushMatrix();

    //glLoadIdentity();

    glTranslatef(this->translation[0], this->translation[1], this->translation[2]);

    glRotatef(this->rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
    glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    //Return to original position
    //glTranslatef(0.0,0.0,0.0);
    glRotatef(90, 1.0,0.0,0.0);
    glRotatef(180, 0.0,1.0,0.0);

    glmDraw(this->mesh,this->mode, GL_TRIANGLES);

    glPopMatrix();
}

void openGLMesh::draw(openGLCamera *c)
{
    glPushMatrix();

    glTranslatef(this->translation[0] + c->getTranslation()[0], this->translation[1] + c->getTranslation()[1], this->translation[2] + c->getTranslation()[2]);

    glRotatef(this->rotation[0] + c->getRotation()[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1] + c->getRotation()[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2] + c->getRotation()[2], 0.0f, 0.0f, 1.0f);

    //Return to original position
    //glTranslatef(0.0,0.0,0.0);
    glRotatef(90, 1.0,0.0,0.0);
    glRotatef(180, 0.0,1.0,0.0);

    //Perform scaling
    glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    glmDraw(this->mesh,this->mode, GL_TRIANGLES);
    this->box.checkCollision(this->mesh, this->mesh);
    glPopMatrix();
}

QString openGLMesh::name()
{
    return "openGLMesh";
}
