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
qDebug()<<filename;
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

    this->inputQueue = new QList<quint32>();
}

openGLRender::~openGLRender()
{
    delete this->objects;
    delete this->models;
    delete this->inputQueue;
}

void openGLRender::initializeGL(){


    glMatrixMode(GL_MODELVIEW);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light0_position[] = { 0.0, 0.0, 1.0, 0.0 };
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

    glOrtho(-20.0f, 20.0f, -20.0f, 20.0f, -2.0f, 2.0f);

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
    bitmapData = LoadBitmapFile("..\\battleships\\tga\\water2.bmp", &bitmapInfoHeader);

    glGenTextures(1, &texture); // generate texture object
    glBindTexture(GL_TEXTURE_2D, texture); // enable our texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // generate the texture image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
                 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
    glBegin(GL_QUADS); // front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0f, -20.0f, 0.0f);
    glTexCoord2f(40.0f, 0.0f); glVertex3f(20.0f, 20.0f, 0.0f);
    glTexCoord2f(40.0f, 40.0f); glVertex3f(-20.0f, 20.0f, 0.0f);
    glTexCoord2f(0.0f, 40.0f); glVertex3f(-20.0f, -20.0f, 0.0f);
    glEnd();

    /* //Draw 2d ui overlay
    glMatrixMode(GL_PROJECTION);

    glDisable(GL_LIGHTING);
    glColor3f(0.0,0.0,0.0);

    glBegin(GL_QUADS);
    glVertex3f(-1.0f,-1.0f,1.0f);
    glVertex3f(1.0f,-1.0f,1.0f);
    glVertex3f(1.0f,1.0f,1.0f);
    glVertex3f(-1.0f,1.0f,1.0f);
    glEnd();

    glEnable(GL_LIGHTING);*/
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





void openGLRender::pushInput(const quint32 &newKey)
{
    this->inputQueue->push_back(newKey);
}

void openGLRender::processInput()
{
    openGLObject *o;
    GLfloat* trans;
    GLfloat* rot;

    //37 - Left arrow
    //38 = Up arrow
    //39 = Right arrow
    //40 = Down arrow
    //32 = Space
    //27 = Esc
    //qDebug()<<"key: " <<ev->key() <<ev->nativeVirtualKey() <<ev->text();

    if( !this->inputQueue->isEmpty())
    {
        for(int i=0;this->inputQueue->size(); i++)
        {
            switch (this->inputQueue->front())
            {
            //Esc key
            case 27:
                //Set mode to MENU_MODE if set to GAME_MODE and vice versa
                break;

                //Space key
            case 32:
                //Create a projectile
                break;

                //Left arrow key
            case 37:
                //Rotate the player slightly left
                //ui->openGLRenderWindow->rotatePlayer(0.1f);
                o = this->pop();
                rot = ((openGLMesh*)o)->getRotation();
                ((openGLMesh*)o)->rotate(rot[0], rot[1], rot[2]+1.0f);

                break;

                //Up arrow key
            case 38:
                o = this->pop();
                trans = ((openGLMesh*)o)->getTranslation();
                rot = ((openGLMesh*)o)->getRotation();
                //((openGLMesh*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
                break;

                //Right arrow key
            case 39:
                o = this->pop();
                rot = ((openGLMesh*)o)->getRotation();
                ((openGLMesh*)o)->rotate(rot[0], rot[1], rot[2]-1.0f);
                break;

                //Down arrow key
            case 40:
                //Reduce acceleration
                break;

            default:
                break;
            }

            //Remove the first input
            this->inputQueue->pop_front();

            //qDebug()<<"rotZ:" <<rot[2];
            //qDebug()<<"sin(rotZ):" <<sin(rot[2]*3.14159265/180);
            //qDebug()<<"cos(rotZ):" <<cos(rot[2]*3.14159265/180);

        }
    }
}

void openGLRender::update(const int &msec)
{
    //qDebug()<<"openGLRender::update(const int &msec)" <<this->objects->size() << this->objectName();

    for( int i=0; i< this->objects->size(); i++)
        if(this->objects->at(i)->name() == "openGLMesh")
            ((openGLMesh*)this->objects->at(i))->update(msec);
}
