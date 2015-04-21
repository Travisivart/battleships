#include <QDebug>

#include "openglrender.h"


//Loads Bitmap into memory and Loads it
////// Texture Information
BITMAPINFOHEADER bitmapInfoHeader; // bitmap info header
unsigned char* bitmapData; // the texture data
unsigned int texture; // the texture object
WORD BITMAP_ID = 19778;


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; // the file pointer
    BITMAPFILEHEADER bitmapFileHeader; // bitmap file header
    unsigned char *bitmapImage; // bitmap image data
    int imageIdx = 0; // image index counter
    unsigned char tempRGB; // swap variable

    // open filename in "read binary" mode
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    // read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    // verify that this is a bitmap by checking for the universal bitmap id
    if (bitmapFileHeader.bfType != BITMAP_ID)
    {
        qDebug()<<"LoadBitmapFile - BITMAP_ID invalid";
        fclose(filePtr);
        return NULL;
    }
    // read the bitmap information header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

    // move file pointer to beginning of bitmap data
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    // allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    // verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    // swap the R and B values to get RGB since the bitmap color format is in BGR
    for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    // close the file and return the bitmap image data
    fclose(filePtr);
    return bitmapImage;
}



//openGLRender(QWidget *parent  = 0);
openGLRender::openGLRender(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->objects = new QList<openGLObject*>();

    this->models = new QList<GLMmodel*>();
    this->selectedObj = -1;
}

openGLRender::~openGLRender()
{
    delete objects;
}

void openGLRender::initializeGL(){


    glMatrixMode(GL_MODELVIEW);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light0_position[] = { 0.0, 0.0, 10.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_position);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light0_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);                 // The type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_TEXTURE_2D);

    //setBackgroundColor(255,255,255,255);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //makeCurrent();
    //this->swapBuffers();


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -2.0f, 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0,0,OGLWIDTH,OGLHEIGHT);
}

void openGLRender::paintGL(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glPushMatrix();
    //glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    /*
    //Light
    //GLfloat lightColor0[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 0.0f};
    //GLfloat lightPos0[] = {0.0f, 30.0f, 0.0f, 1};
    GLfloat lightPos0[] = {0.0, 0.0, 1.0, 0};
    //glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor0);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);

    //Material
    //GLfloat mcolor[] = {0.1, 0.9, 0.4, 1.0};
    GLfloat mcolor[] = {1.0, 1.0, 1.0, 1.0};
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mcolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
*/
    draw();


    //Create terrain
    //g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
    //g_glRender->Render();

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // clear to black

    glShadeModel(GL_SMOOTH); // use smooth shading
    glEnable(GL_DEPTH_TEST); // hidden surface removal
    glEnable(GL_CULL_FACE); // do not calculate inside of poly's
    glFrontFace(GL_CCW); // counter clock-wise polygons are out

    glEnable(GL_TEXTURE_2D); // enable 2D texturing
    //change wood.bmp to the name of your bitmap
    // load our bitmap file
    bitmapData = LoadBitmapFile("D:\\Projects\\Qt\\battleships\\tga\\water.bmp", &bitmapInfoHeader);

    glGenTextures(1, &texture); // generate texture object
    glBindTexture(GL_TEXTURE_2D, texture); // enable our texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // generate the texture image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
                 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
    glBegin(GL_QUADS); // front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0f, -20.0f, 0.0f);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(20.0f, 20.0f, 0.0f);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(-20.0f, 20.0f, 0.0f);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-20.0f, -20.0f, 0.0f);
    glEnd();



    makeCurrent();
    this->swapBuffers();

}

void openGLRender::draw(){

    if (!objects->empty())
    {
        glBegin(GL_POINTS);

        for(int i=0; i<objects->size();i++)
        {
            if(objects->at(i)->name() == "openGLPolygon")
                if(((openGLPolygon*)objects->at(i))->isFinished())
                    ((openGLPolygon*)objects->at(i))->drawFilled();

            if(objects->at(i)->name() != "openGLPolygon" && objects->at(i)->name() != "openGLMesh")
                objects->at(i)->draw();
        }

        glEnd();

        glBegin(GL_LINES);

        for(int i=0; i<objects->size();i++)
        {
            if(objects->at(i)->name() == "openGLLine")
                objects->at(i)->draw();
        }
        glEnd();

        //Draw meshes
        for(int i=0; i<objects->size();i++)
            if(objects->at(i)->name() == "openGLMesh")
                objects->at(i)->draw();
    }
}

void openGLRender::clearGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glFlush();
    makeCurrent();
    this->swapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void openGLRender::setColorGL(int newRed, int newGreen, int newBlue)
{
    glColor3f((float)newRed/255, (float)newGreen/255, (float)newBlue/255);
}

void openGLRender::clearObjects()
{
    objects->clear();
}

void openGLRender::setLineSizeGL(int newSize)
{
    glLineWidth(newSize);
}

void openGLRender::resizeGL(int width, int height)
{
    
}

bool openGLRender::isEmpty()
{
    return objects->isEmpty();
}

int openGLRender::size()
{
    return objects->size();
}

void openGLRender::removeAt(int i)
{
    qDebug()<<"deleting i";
    //delete this->objects->at(i);
    qDebug()<<"removing i";
    this->objects->removeAt(i);
    qDebug()<<"i removed";
}

void openGLRender::push(openGLObject *newObj)
{
    objects->append(newObj);
}

openGLObject* openGLRender::pop()
{
    return objects->last();
}

openGLObject* openGLRender::at(const int i)
{
    return objects->at(i);
}


void openGLRender::setBackgroundColor(int newRed, int newGreen, int newBlue, int newAlpha)
{
    glClearColor(((float)newRed/255), ((float)newGreen/255), ((float)newBlue/255), ((float)newAlpha/255));
}






void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
    glVertex3fv(va);
    glVertex3fv(vb);
    glVertex3fv(vc);
}

void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{

    GLfloat colors[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
                            {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}};

    glColor3fv(colors[0]);
    triangle(a, b, c);
    glColor3fv(colors[1]);
    triangle(a, c, d);
    glColor3fv(colors[2]);
    triangle(a, d, b);
    glColor3fv(colors[3]);
    triangle(b, d, c);
}


void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{

    GLfloat mid[6][3];
    int j;
    if(m>0)
    {
        /* compute six midpoints */

        for(j=0; j<3; j++) mid[0][j]=(a[j]+b[j])/2;
        for(j=0; j<3; j++) mid[1][j]=(a[j]+c[j])/2;
        for(j=0; j<3; j++) mid[2][j]=(a[j]+d[j])/2;
        for(j=0; j<3; j++) mid[3][j]=(b[j]+c[j])/2;
        for(j=0; j<3; j++) mid[4][j]=(c[j]+d[j])/2;
        for(j=0; j<3; j++) mid[5][j]=(b[j]+d[j])/2;

        /* create 4 tetrahedrons by subdivision */

        divide_tetra(a, mid[0], mid[1], mid[2], m-1);
        divide_tetra(mid[0], b, mid[3], mid[5], m-1);
        divide_tetra(mid[1], mid[3], c, mid[4], m-1);
        divide_tetra(mid[2], mid[4], d, mid[5], m-1);

    }
    else(tetra(a,b,c,d)); /* draw tetrahedron at end of recursion */
}











