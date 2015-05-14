#include "openglrender.h"
#include "QTemporaryDir"
//Loads Bitmap into memory and Loads it
////// Texture Information
BITMAPINFOHEADER bitmapInfoHeader; // bitmap info header
BITMAPINFOHEADER bitmapInfoHeader2; // bitmap info header
BITMAPINFOHEADER bitmapInfoHeader3;
unsigned int texture; // the texture object
unsigned int texture2; // the texture object
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
    if (filePtr == NULL){
        return NULL;
    }


    // read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    // verify that this is a bitmap by checking for the universal bitmap id
    if (bitmapFileHeader.bfType != BITMAP_ID)
    {
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
    this->ships = load("../battleships/obj/Shipboatsmall1.obj");
    this->missilemesh = load("../battleships/obj/Missiles.obj");    //this->models = new QList<GLMmodel*>();
    this->walls = load("../battleships/obj/Pillar.obj");
    this->delay.start();
    this->timecounter.start();
    this->selectedObj = -1;

    this->inputQueue = new QList<quint32>();

    this->camera = new openGLCamera();
}

openGLRender::~openGLRender()
{
    delete this->objects;
    //delete this->models;
    delete this->inputQueue;
    delete this->camera;
}

GLMmodel* openGLRender::load(QString filename)
{
    GLMmodel *mesh;
    //qDebug()<<"ship::load(QString filename)";
    //Make sure that we are actually trying to load an existing file.
    if (filename != "")
    {
        //If something is already loaded into the mesh, then delete it.
        //if ( mesh != NULL )
        //deleteMesh();

        QByteArray ba = filename.toLatin1();
        char *c_str2 = ba.data();

        mesh = glmReadOBJ(c_str2);
    }
    return mesh;
}

void openGLRender::initializeGL(){

    // float ambientLight[] = { 1, 1, 1, 1.0 };
    // float specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    // float specularity[] = { 1.0, 1.0, 1.0, 1.0 };
    // float emission[]={0.3, 0.3, 0.3, 1.0};
    // float shininess[] = { 60.0 };
    // float lightPosition[] = { 0.0, 0.0, 10.0, 1.0 };
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glColorMaterial ( GL_FRONT, GL_EMISSION ) ;
    // glEnable ( GL_COLOR_MATERIAL ) ;
    // glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emission ) ;
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specularity); // Reflectance
    // glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Shininess

    // // Enable ambient light usage
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    // // Position of the light source
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    glMatrixMode(GL_MODELVIEW);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);                 // The type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_TEXTURE_2D);

    //setBackgroundColor(255,255,255,255);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //makeCurrent();
    //this->swapBuffers();

    this->camera->init();

    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    glOrtho(-100.0f*2.1714, 100.0f*2.1714, -100.0f, 100.0f, -2000.0f, 2000.0f);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glViewport(0,0,OGLWIDTH,OGLHEIGHT);


    glEnable(GL_TEXTURE_2D); // enable 2D texturing
    // load our bitmap file
    //QDir dir; qDebug()<< dir.absolutePath()<<flush;
    bitmapData = LoadBitmapFile("../battleships/tga/water4.bmp", &bitmapInfoHeader);
    bitmapData2 = LoadBitmapFile("../battleships/tga/skybox.bmp", &bitmapInfoHeader2);
    bitmapData3 = LoadBitmapFile("../battleships/tga/water4r.bmp",&bitmapInfoHeader3);

    //Bind the textures
    glGenTextures(1, &texture); // generate texture object
    glBindTexture(GL_TEXTURE_2D, texture); // enable our texture object

    glGenTextures(1, &texture2); // generate texture object
    glBindTexture(GL_TEXTURE_2D, texture2); // enable our texture object
    //counter=0;

    title = glmReadOBJ("../battleships/obj/battleships.obj");
    title2 = glmReadOBJ("../battleships/obj/pressanykey.obj");

}

void openGLRender::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    draw();

    //Create terrain
    //g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1));
    //g_glRender->Render();

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // clear to black

    glShadeModel(GL_SMOOTH); // use smooth shading
    glEnable(GL_DEPTH_TEST); // hidden surface removal
    glEnable(GL_CULL_FACE); // do not calculate inside of poly's
    glFrontFace(GL_CCW); // counter clock-wise polygons are out

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // generate the texture image
    if(this->timecounter.elapsed()<1000){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
        glBegin(GL_QUADS); // front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(800.0f, -800.0f, 0.0f);
        glTexCoord2f(40.0f, 0.0f); glVertex3f(800.0f, 800.0f, 0.0f);
        glTexCoord2f(40.0f, 40.0f); glVertex3f(-800.0f, 800.0f, 0.0f);
        glTexCoord2f(0.0f, 40.0f); glVertex3f(-800.0f, -800.0f, 0.0f);
        glEnd();
    }
    else if(this->timecounter.elapsed()<2000) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData3);
        glBegin(GL_QUADS); // front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(800.0f, -800.0f, 0.0f);
        glTexCoord2f(40.0f, 0.0f); glVertex3f(800.0f, 800.0f, 0.0f);
        glTexCoord2f(40.0f, 40.0f); glVertex3f(-800.0f, 800.0f, 0.0f);
        glTexCoord2f(0.0f, 40.0f); glVertex3f(-800.0f, -800.0f, 0.0f);
        glEnd();
    }
    else{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
        glBegin(GL_QUADS); // front face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(800.0f, -800.0f, 0.0f);
        glTexCoord2f(40.0f, 0.0f); glVertex3f(800.0f, 800.0f, 0.0f);
        glTexCoord2f(40.0f, 40.0f); glVertex3f(-800.0f, 800.0f, 0.0f);
        glTexCoord2f(0.0f, 40.0f); glVertex3f(-800.0f, -800.0f, 0.0f);
        glEnd();
        this->timecounter.restart();
    }
    //counter++;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader2.biWidth, bitmapInfoHeader2.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData2);
    glBegin(GL_QUADS); // front face
    glTexCoord2f(0.7529296875f, 0.24609375f); glVertex3f(800.0f, 800.0f, 800.0f);
    glTexCoord2f(0.24609375f, 0.24609375f); glVertex3f(-800.0f, 800.0f, 800.0f);
    glTexCoord2f(0.24609375f, 0.0f); glVertex3f(-800.0f, 800.0f, 0.0f);
    glTexCoord2f(0.7529296875f, 0.0f); glVertex3f(800.0f, 800.0f, 0.0f);

    glTexCoord2f(0.7529296875f, 0.24609375f); glVertex3f(800.0f, 800.0f, 800.0f);
    glTexCoord2f(1.0f, 0.24609375f); glVertex3f(800.0f, 800.0f, 0.0f);
    glTexCoord2f(1.0f, 0.7529296875f); glVertex3f(800.0f, -800.0f, 0.0f);
    glTexCoord2f(0.7529296875f, 0.7529296875f); glVertex3f(800.0f, -800.0f, 800.0f);

    glTexCoord2f(0.7529296875f, 0.7529296875f); glVertex3f(800.0f, -800.0f, 800.0f);
    glTexCoord2f(0.7529296875f, 1.0f); glVertex3f(800.0f, -800.0f, 0.0f);
    glTexCoord2f(0.24609375f, 1.0f); glVertex3f(-800.0f, -800.0f, 0.0f);
    glTexCoord2f(0.24609375f, 0.7529296875f); glVertex3f(-800.0f, -800.0f, 800.0f);

    glTexCoord2f(0.24609375f, 0.7529296875f); glVertex3f(-800.0f, -800.0f, 800.0f);
    glTexCoord2f(0.0f, 0.7529296875f); glVertex3f(-800.0f, -800.0f, 0.0f);
    glTexCoord2f(0.0f, 0.24609375f); glVertex3f(-800.0f, 800.0f, 0.0f);
    glTexCoord2f(0.24609375f, 0.24609375f); glVertex3f(-800.0f, 800.0f, 800.0f);

    glTexCoord2f(0.7529296875f, 0.24609375f); glVertex3f(800.0f, 800.0f, 800.0f);
    glTexCoord2f(0.7529296875f, 0.7529296875f); glVertex3f(800.0f, -800.0f, 800.0f);
    glTexCoord2f(0.24609375f, 0.7529296875f); glVertex3f(-800.0f, -800.0f, 800.0f);
    glTexCoord2f(0.24609375f, 0.24609375f); glVertex3f(-800.0f, 800.0f, 800.0f);

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

void openGLRender::paintTitle(float rotX, float rotY, float rotZ)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glShadeModel(GL_SMOOTH); // use smooth shading
    glEnable(GL_DEPTH_TEST); // hidden surface removal
    glEnable(GL_CULL_FACE); // do not calculate inside of poly's
    glFrontFace(GL_CCW); // counter clock-wise polygons are out

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glLoadIdentity();
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    glScalef(12.0f,12.0f,12.0f);
    glmDraw(title, GLM_MATERIAL, GL_TRIANGLES);
    glLoadIdentity();
    glTranslatef(1.0f,-16.0f,0.0f);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    glScalef(12.0f,12.0f,12.0f);
    glmDraw(title2, GLM_MATERIAL, GL_TRIANGLES);

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

            if(objects->at(i)->name() != "openGLPolygon" && objects->at(i)->name() != "ship" && objects->at(i)->name() != "projectile")
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
        {
            if(objects->at(i)->name() == "ship"){
                if(i != 0)
                    ((ship*)this->objects->at(i))->draw();
                else
                    this->objects->at(i)->draw();
            }
            else if(objects->at(i)->name()=="projectile"){
                ((projectile*)this->objects->at(i))->draw();
            }
        }
    }
}

void openGLRender::clearGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    //qDebug()<<"deleting i";
    //delete this->objects->at(i);
    //qDebug()<<"removing i";
    this->objects->removeAt(i);
    //qDebug()<<"i removed";
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
    if ( this->inputQueue->indexOf(newKey) == -1)
        this->inputQueue->push_back(newKey);
}

void openGLRender::popInput(const quint32 &newKey)
{
    this->inputQueue->removeAt(this->inputQueue->indexOf(newKey));
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
    //87 = w
    //65 = a
    //83 = s
    //68 = d
    //qDebug()<<"key: " <<ev->key() <<ev->nativeVirtualKey() <<ev->text();

    if( !this->inputQueue->isEmpty())
    {
        for(int i=0; i < this->inputQueue->size(); i++)
        {
            switch (this->inputQueue->at(i))
            {
            //Esc key
            case 16777216:
                //Set mode to MENU_MODE if set to GAME_MODE and vice versa
                break;

                //Space key
            case 32:
                //Create a projectile
                //qDebug()<<"Create projectile";

                if(this->delay.elapsed()>1000){
                    this->spawnMissile();
                    this->delay.restart();
                }
                break;

                //Left arrow key
            case 16777234:
                //Rotate the player slightly left
                //ui->openGLRenderWindow->rotatePlayer(0.1f);
                o = this->objects->at(0);
                rot = ((ship*)o)->getRotation();
                ((ship*)o)->rotate(rot[0], rot[1], rot[2]+0.6f);
                //this->camera->rotate(rot[0], rot[1], rot[2]+0.6f);

                break;
            case 65:
                //Rotate the player slightly left
                o = this->objects->at(0);
                rot = ((ship*)o)->getRotation();
                ((ship*)o)->rotate(rot[0], rot[1], rot[2]+0.6f);
break;

                //Up arrow key
            case 16777235:
                o = this->objects->at(0);
                ((ship*)o)->increaseAcceleration();
                break;
            case 87:
                o = this->objects->at(0);
                ((ship*)o)->increaseAcceleration();
                break;

                //Right arrow key
            case 16777236:
                o = this->objects->at(0);
                rot = ((ship*)o)->getRotation();
                ((ship*)o)->rotate(rot[0], rot[1], rot[2]-0.6f);
                //this->camera->rotate(rot[0], rot[1], rot[2]+0.6f);
                break;

            case 68:
                o = this->objects->at(0);
                rot = ((ship*)o)->getRotation();
                ((ship*)o)->rotate(rot[0], rot[1], rot[2]-0.6f);
                break;

                //Down arrow key
            case 16777237:
                //Reduce acceleration
                o = this->objects->at(0);
                ((ship*)o)->decreaseAcceleration();
                break;

            case 83:
                //Reduce acceleration
                o = this->objects->at(0);
                ((ship*)o)->decreaseAcceleration();
                break;

            default:
                break;
            }

            //Remove the first input
            //this->inputQueue->pop_front();

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
        if(this->objects->at(i)->name() == "ship")
            ((ship*)this->objects->at(i))->update(msec);
}
void openGLRender::spawnMissile(){
    openGLObject *o;
    o = this->objects->at(0);
   this->push(new projectile(this->missilemesh,((ship*)o)->getTranslation(),((ship*)o)->getRotation()));

}
void openGLRender::spawnEnemies()
{
    GLfloat transX, transY;
    float rotZ;

    //Always make sure there are at least 4 enemies in the world. (Player + enemies = 5)

    int counter = 0;

    //count how many ships there are
    for(int i = 0; i < this->objects->size(); i++)
        if(this->objects->at(i)->name() == "ship")
            counter++;

    if( counter < 10 )
    {
        while(counter < 10)
        {
            //qDebug()<<"spawnEnemies";
            this->push(new ship(this->ships,false));

            //((ship*)this->pop())->scale(0.2f, 0.2f, 0.2f);
            //this->push(new ship("../battleships/obj/tetrahedron.obj"));

            qsrand(QTime::currentTime().msec());

            //Give the enemies some random positioning
            transX = (float)(qrand()%7900);
            transY = (float)(qrand()%7900);

            qrand()%2 == 0 ? transX : transX = transX*(-1);
            qrand()%2 == 0 ? transY : transY = transY*(-1);

            ((ship*)this->pop())->translate(transX/10.0f,transY/10.0f, 0.0f );
            ((ship*)this->pop())->rotate(0, 0, rand()%359);

            //((ship*)this->pop())->rotate();
            counter++;
        }
        this->push(new barrier(this->walls));
        transX = (float)(qrand()%7900);
        transY = (float)(qrand()%7900);

        qrand()%2 == 0 ? transX : transX = transX*(-1);
        qrand()%2 == 0 ? transY : transY = transY*(-1);

        ((barrier*)this->pop())->translate(transX/10.0f,transY/10.0f, 0.0f );
        ((barrier*)this->pop())->rotate(0, 0, rand()%359);
        ((barrier*)this->pop())->scale(qrand()%36+4,qrand()%36+4,8.0);

    }
}

void openGLRender::updateCamera()
{
    //glMatrixMode(GL_PROJECTION);

    //glOrtho(-1.0001f, 1.0001f, -1.0001f, 1.0001f, -1.0001f, 1.0001f);
}

void openGLRender::checkCollisions()
{
    //Only check for collisions if there is more than one object.

    if(this->objects->size() > 1)
    {
        for(int i=0; i< this->objects->size(); i++)
        {
            for(int j=i+1; j<this->objects->size(); j++)
            {
                //qDebug()<<"Checking for collision at:" <<i <<"and" <<j;
                //If there is a collision between objects i and j then do something (destroy both objects)
                if(((openGLMesh*)this->objects->at(i))->checkCollision( ((openGLMesh*)this->objects->at(j)) ))
                {   
                    qDebug()<< this->objects->at(i)->name();
                    // if((this->objects->at(i)->name()=="projectile" || this->objects->at(j)->name()=="projectile")&& (i==0)){
                    if(i==0 &&  this->objects->at(j)->name()=="projectile"){
                        qDebug()<<i<<"skipped"<<j;
                        break;
                    }
                    else if(this->objects->at(i)->name()=="projectile" && this->objects->at(j)->name()=="projectile" ){
                        qDebug()<<i<<"skipped"<<j;
                        break;
                    }
                        qDebug()<<"Collision between objects:" <<i <<"and" <<j;
                        if( (this->objects->at(i))->isDescructable())
                            (this->objects->at(i))->destroy();
                        if( (this->objects->at(j))->isDescructable())
                            (this->objects->at(j))->destroy();
                    
                }

            }
        }
    }
}

void openGLRender::removeDestroyedObjects()
{
    for(int i=0; i< this->objects->size(); i++)
    {
        if(!(this->objects->at(i))->isAlive())
        {
            if (i != 0)
            {
                qDebug()<<"object:" <<i <<"is destroyed";
                //((openGLMesh*)this->objects->at(i))->deleteMesh();
                delete (this->objects->at(i));
                this->objects->removeAt(i);
            }
        }
    }
}
