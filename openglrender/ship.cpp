#include "ship.h"
#include "openglrender.h"
#include <QDebug>

ship::ship()
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
    this->missilemesh=NULL;

    this->destructible = true;
    this->alive = true;
}

ship::ship(GLMmodel* ship,bool player)
{
    //qDebug()<<"Constructor: ship(" <<newFilename <<")";
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;

    this->scaling[0] = 1.0f;
    this->scaling[1] = 1.0f;
    this->scaling[2] = 1.0f;
    this->player=player;
    this->velocity=0;
    //#define GLM_NONE     (0)		/* render with only vertices */
    //#define GLM_FLAT     (1 << 0)		/* render with facet normals */
    //#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
    //#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
    //#define GLM_COLOR    (1 << 3)		/* render with colors */
    //#define GLM_MATERIAL (1 << 4)		/* render with materials */
    this->mode = GLM_MATERIAL;
    this->mesh=ship;
    this->missilemesh = openGLRender::load("../battleships/obj/Missiles.obj");
    // this->filename = newFilename;
    this->missile=new projectile();

    //qDebug()<<"ship::ship(const QString newFilename)" <<"Attempting file load";
    //this->load(this->filename);

    //qDebug()<<"Calculating bounding box";
    this->getBox().calculateBox(this->mesh);
    this->box.calculateBox(this->mesh);
    //qDebug()<<"MaxX: " <<box.getMaxX();
    //qDebug()<<"MinX: " <<box.getMinX();
    //qDebug()<<"MinY: " <<box.getMinY();

    v = 1.0f;

    this->destructible = true;
    this->alive = true;
}

ship::~ship()
{
    //delete this->mesh;
}

float ship::getVelocity(){
    return this->velocity;
}

void ship::increaseAcceleration(){
    
    if(velocity<2.0f)
        velocity+=.05f;
}

void ship::decreaseAcceleration(){
    if(this->velocity>0.003f)
        velocity-=.03f;
    else
        this->velocity=0.0f;

}

void ship::translate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->translation[0] = newX;
    this->translation[1] = newY;
    this->translation[2] = newZ;
}

void ship::translate(GLfloat *newTranslation)
{
    this->translation[0] = newTranslation[0];
    this->translation[1] = newTranslation[1];
    this->translation[2] = newTranslation[2];
}

void ship::rotate(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->rotation[0] = fmod(newX, 360);
    this->rotation[1] = fmod(newY, 360);
    this->rotation[2] = fmod(newZ, 360);
}

void ship::rotate(GLfloat *newRotation)
{
    this->rotation[0] = fmod(newRotation[0], 360);
    this->rotation[1] = fmod(newRotation[1], 360);
    this->rotation[2] = fmod(newRotation[2], 360);
}

void ship::scale(GLfloat newX, GLfloat newY, GLfloat newZ)
{
    this->scaling[0] = newX;
    this->scaling[1] = newY;
    this->scaling[2] = newZ;
}

void ship::scale(GLfloat *newScaling)
{
    this->scaling[0] = newScaling[0];
    this->scaling[1] = newScaling[1];
    this->scaling[2] = newScaling[2];
}

void ship::setMode(int GLM_MODE)
{
    this->mode = GLM_MODE;
}

GLfloat* ship::getTranslation()
{
    return this->translation;
}

GLfloat* ship::getRotation()
{
    return this->rotation;
}

GLfloat* ship::getScaling()
{
    return this->scaling;
}

// void ship::load(QString filename)
// {
//     qDebug()<<"ship::load(QString filename)";
//     //Make sure that we are actually trying to load an existing file.
//     if (filename != "")
//     {
//         //If something is already loaded into the mesh, then delete it.
//         //if ( mesh != NULL )
//         //deleteMesh();

//         QByteArray ba = filename.toLatin1();
//         char *c_str2 = ba.data();

//         this->mesh = glmReadOBJ(c_str2);
//     }
// }

void ship::deleteMesh()
{
    delete this->mesh;
    mesh = NULL;
}

QString ship::getFilename()
{
    return this->filename;
}

void ship::attack()
{
    this->missile->changemesh(this->missilemesh,this->translation,this->rotation);

}

void ship::update(const int &msec)
{
    float bounce=-.01f;
    bounce = 0.0f;
    int trigger=0;

    //qDebug()<<"Ship update";

    //qDebug()<<"velocity: " <<velocity+(float)(rand()%3-1)/3;
    if(player){
        if(trigger%10==0){
            //if(rand()%2>0)
            //    bounce=.01f;
            //else
            //    bounce=-.01f;
        }
        this->translation[0] -= ((this->velocity+bounce)*sin(this->rotation[2]*3.14159265/180));
        //this->translation[1] += 1.0f * msec/1000;
        this->translation[1] += ((this->velocity+bounce)*cos(this->rotation[2]*3.14159265/180));
        //((ship*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
        bounce=0;
        trigger++;
    }
    else{
        if(this->translation[1]>100*2.1714){
            qDebug()<<"ship out of bounds";
            qDebug()<<"random number between 90-270"<< rand()%178+91;
            rotate(rotation[0], rotation[1], 0);
            rotate(rotation[0], rotation[1], rand()%178+90);
            translate(translation[0],translation[1]-1,translation[2]);


        }
        if(this->translation[0]>100*2.1714){
            qDebug()<<"ship out of bounds";
            rotate(rotation[0], rotation[1], 0);
            rotate(rotation[0], rotation[1], rand()%178+1);
            translate(translation[0]-1,translation[1],translation[2]);


        }
        if(this->translation[0]<-100*2.1714){
            qDebug()<<"ship out of bounds";
            rotate(rotation[0], rotation[1], 0);
            rotate(rotation[0], rotation[1], rand()%178+181);
            translate(translation[0]+1,translation[1],translation[2]);

        }
        if(this->translation[1]<-100*2.1714){
            qDebug()<<"ship out of bounds";
            rotate(rotation[0], rotation[1], 0);
            rotate(rotation[0], rotation[1], rand()%178-90);
            translate(translation[0],translation[1]+1,translation[2]);
        }

        this->translation[0] -= ((30.0f * msec/100)*sin(this->rotation[2]*3.14159265/180));
        //this->translation[1] += 1.0f * msec/1000;
        this->translation[1] += ((30.0f * msec/100)*cos(this->rotation[2]*3.14159265/180));
        //((ship*)o)->translate(trans[0]-(0.1f*sin(rot[2]*3.14159265/180)), trans[1]+(0.1f*cos(rot[2]*3.14159265/180)), trans[2]);
    }
}

void ship::draw()
{


   //  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   //  GLfloat mat_shininess[] = { 100.0 };

   // //GLfloat global_ambient[]={}

   //  GLfloat light0_ambient[] = { 1,1,1, 1.0 };
   //  GLfloat light0_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
   //  GLfloat light0_specular[] = { 10.0, 10.0, 10.0, 1.0 };
   //  GLfloat light0_position[4];
   //  light0_position[0] = this->translation[0];
   //  light0_position[1] = this->translation[1];
   //  light0_position[2] = this->translation[2]-15;
   //  light0_position[3] = 0;

   //  //light0_position[2]+=5;
   //  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
   //  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
   //  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
   //  // glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
   //  // glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
   //  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
   //  glEnable(GL_LIGHTING);
   //  glEnable(GL_LIGHT0);

    //glLoadIdentity();
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 0.0);
    //glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,this->translation);
    
    glPushMatrix();
    glTranslatef(this->translation[0], this->translation[1], this->translation[2]);

    glRotatef(this->rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
    //glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);

    glmDraw(this->mesh,this->mode, GL_TRIANGLES);


    glBegin(GL_LINES);
    float minx = this->getBox().getMinX();
    float miny = this->getBox().getMinY();
    float minz = this->getBox().getMinZ();
    float maxx = this->getBox().getMaxX();
    float maxy = this->getBox().getMaxY();
    float maxz = this->getBox().getMaxZ();

    //Draw bottom square
    glVertex3f(minx, miny ,minz);
    glVertex3f(minx, maxy ,minz);
    glVertex3f(minx, maxy ,minz);
    glVertex3f(maxx, maxy ,minz);
    glVertex3f(maxx, maxy ,minz);
    glVertex3f(maxx, miny ,minz);
    glVertex3f(maxx, miny ,minz);
    glVertex3f(minx, miny ,minz);

    //Draw vertical lines
    glVertex3f(minx, miny ,minz);
    glVertex3f(minx, miny ,maxz);
    glVertex3f(minx, maxy ,minz);
    glVertex3f(minx, maxy ,maxz);
    glVertex3f(maxx, maxy ,minz);
    glVertex3f(maxx, maxy ,maxz);
    glVertex3f(maxx, miny ,minz);
    glVertex3f(maxx, miny ,maxz);

    //Draw top square
    glVertex3f(minx, miny ,maxz);
    glVertex3f(minx, maxy ,maxz);

    glVertex3f(minx, maxy ,maxz);
    glVertex3f(maxx, maxy ,maxz);

    glVertex3f(maxx, maxy ,maxz);
    glVertex3f(maxx, miny ,maxz);

    glVertex3f(maxx, miny ,maxz);
    glVertex3f(minx, miny ,maxz);

    glEnd();

    glPopMatrix();
}

void ship::draw(openGLCamera *c)
{
    glPushMatrix();

    glTranslatef(this->translation[0] + c->getTranslation()[0], this->translation[1] + c->getTranslation()[1], this->translation[2] + c->getTranslation()[2]);

    glRotatef(this->rotation[0] + c->getRotation()[0], 1.0f, 0.0f, 0.0f);
    glRotatef(this->rotation[1] + c->getRotation()[1], 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation[2] + c->getRotation()[2], 0.0f, 0.0f, 1.0f);

    //Perform scaling
    glScalef(this->scaling[0], this->scaling[1], this->scaling[2]);
    glmDraw(this->mesh,GLM_COLOR, GL_TRIANGLES);
    this->box.checkCollision(this->mesh, this->mesh);
    glPopMatrix();
}

QString ship::name()
{
    return "ship";
}
