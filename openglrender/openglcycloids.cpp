#include "openglcycloids.h"

openGLCycloids::openGLCycloids()
{
    x1 = 0;
    y1 =0;

    r1 = 50;
    r2 = 20;

    theta = 90;
}

openGLCycloids::~openGLCycloids()
{

}

int openGLCycloids::getX1()
{
    return x1;
}

int openGLCycloids::getY1()
{
    return y1;
}

int openGLCycloids::getX2()
{
    return x2;
}

int openGLCycloids::getY2()
{
    return y2;
}

int openGLCycloids::getR1()
{
    return r1;
}

int openGLCycloids::getR2()
{
    return r2;
}

int openGLCycloids::getTheta()
{
    return theta;
}

void openGLCycloids::setX1(const int &newX1)
{
    x1 = newX1;
}

void openGLCycloids::draw()
{
    //    X = (a-b) cos(theta) + b cos( (a-b)/b * theta)
    //    y = (a-b) sin(theta) + b sin( (a-b)/b * theta)
    float newX;
    float newY;
    glColor3f(0.0f,0.5f,0.0f);

    qDebug()<<"x1" <<x1 <<"y1" <<y1 <<"r1" <<r1 <<"r2" <<r2 <<"theta" <<theta;

    qDebug()<<"X: " <<(r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta);
    qDebug()<<"Y: " <<(r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta);


    // newX = (r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta);
    // newY = (r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta);

    // glVertex2f(newX,newY);

    //drawCycloid(x1+r1, y1, r1, r2, theta);

    //newX = ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    //newY = ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));
for (int t=0; t<20; t++)
{
    newX = ((r1-r2) * cos(t) + r2 * cos((r1-r2)/r2 * t));
    newY = ((r1-r2) * sin(t) + r2 * sin((r1-r2)/r2 * t));
    glVertex2f((float)(newX+this->getX1())/(OGLWIDTH),(float)(newY+this->getY1())/OGLHEIGHT);
}



}

void openGLCycloids::drawCycloid(float x, float y, int r1, int r2, int theta)
{
float newX;
float newY;
    qDebug()<<"x1" <<x1 <<"y1" <<y1 <<"r1" <<r1 <<"r2" <<r2 <<"theta" <<theta;
x = r1;
y = 0;
    for (int i = x+r1; i>=0; i--)
    {
        qDebug()<<"X:" <<x <<"y:" <<y;
        newX = ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
        newY = ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));
        glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(newY+y)/OGLHEIGHT);
        x--;
        y++;

    }

    /*
    qDebug()<<"X: " <<x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    qDebug()<<"Y: " <<y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    x = x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    y = y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    qDebug()<<"X: " <<x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    qDebug()<<"Y: " <<y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    x = x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    y = y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    qDebug()<<"X: " <<x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    qDebug()<<"Y: " <<y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    x = x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    y = y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    qDebug()<<"X: " <<x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    qDebug()<<"Y: " <<y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    x = x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    y = y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    qDebug()<<"X: " <<x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    qDebug()<<"Y: " <<y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    x = x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    y = y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));

    qDebug()<<"X: " <<x + ((r1-r2) * cos(theta) + r2 * cos((r1-r2)/r2 * theta));
    qDebug()<<"Y: " <<y + ((r1-r2) * sin(theta) + r2 * sin((r1-r2)/r2 * theta));*/

}
