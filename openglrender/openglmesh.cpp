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

    this->load(this->filename);
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
    this->rotation[0] = newX;
    this->rotation[1] = newY;
    this->rotation[2] = newZ;
}

void openGLMesh::rotate(GLfloat *newRotation)
{
    this->rotation[0] = newRotation[0];
    this->rotation[1] = newRotation[1];
    this->rotation[2] = newRotation[2];
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

void openGLMesh::load(QString filename)
{

    //Make sure that we are actually trying to load an existing file.
    if (filename != "")
    {
        //If something is already loaded into the mesh, then delete it.
        if ( mesh != NULL )
            deleteMesh();

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

void openGLMesh::draw()
{
    glPushMatrix();

    //Perform translations
    glTranslatef(this->translation[0], this->translation[1], this->translation[2]);

    //Perform rotations
    glRotatef(this->rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
    glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    glmDraw(this->mesh,this->mode, GL_TRIANGLES);

    glPopMatrix();
}

QString openGLMesh::name()
{
    return "openGLMesh";
}
