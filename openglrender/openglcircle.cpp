#include "openglcircle.h"

openGLCircle::openGLCircle()
{
    x = 0;
    y = 0;
    r = 0;
    filled = false;
}

openGLCircle::openGLCircle(const int newX, const int newY, const int newR)
{
    x = newX;
    y = newY;
    r = newR;

    filled = false;
}

openGLCircle::~openGLCircle()
{

}

QColor openGLCircle::getColor()
{
    return color;
}

QColor openGLCircle::getFillColor()
{
    return fillColor;
}

int openGLCircle::getX()
{
    return x;
}

int openGLCircle::getY()
{
    return y;
}

int openGLCircle::getR()
{
    return r;
}

QString openGLCircle::getType()
{
    return type;
}
bool openGLCircle::isFilled()
{
    return this->filled;
}

void openGLCircle::setColor(const QColor &newColor)
{
    color = newColor;
}

void openGLCircle::setFillColor(const QColor &newFillColor)
{
    fillColor = newFillColor;
}

void openGLCircle::setX(const int newX)
{
    x = newX;
}

void openGLCircle::setY(const int newY)
{
    y = newY;
}

void openGLCircle::setR(const int newR)
{
    r = newR;
}

void openGLCircle::setType(QString newType)
{
    type = newType;
}

void openGLCircle::setFilled(const bool &newFilled)
{
    filled = newFilled;
}


void openGLCircle::draw()
{
    int step = 0;

    glColor3f((float)this->getColor().red()/255, (float)this->getColor().green()/255, (float)this->getColor().blue()/255);

    //qDebug()<<"circle:: center: ("<<(x) << "," <<(y) <<"), Radius:" <<r;

    if (type == "FULL" || type == "SEMINORTH" || type == "SEMIEAST" || type == "SEMIWEST" || type == "QUADNE" || type == "QUADNW")
        glVertex2f((float)(x)/(OGLWIDTH),(float)(y+r)/OGLHEIGHT);
    if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "SEMIWEST" || type == "QUADSE" || type == "QUADSW")
        glVertex2f((float)(x)/(OGLWIDTH),(float)(y-r)/OGLHEIGHT);
    if (type == "FULL" || type == "SEMINORTH" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "QUADNE" || type == "QUADSE")
        glVertex2f((float)(x+r)/(OGLWIDTH),(float)(y)/OGLHEIGHT);
    if (type == "FULL" || type == "SEMINORTH" || type == "SEMISOUTH" || type == "SEMIWEST" || type == "QUADNW" || type == "QUADSW")
        glVertex2f((float)(x-r)/(OGLWIDTH),(float)(y)/OGLHEIGHT);
    //qDebug()<<"  Step:" <<step <<"(" <<x <<"," <<y+r <<") calculated";
    //qDebug()<<"    (" <<x <<"," <<y-r <<")";
    //qDebug()<<"    (" <<x+r <<"," <<y <<")";
    //qDebug()<<"    (" <<x-r <<"," <<y <<")";

    if (this->filled)
    {

    }

    bresenham(1,r,1-r, step+1);

    return;
}

void openGLCircle::bresenham(const int newX, const int newY, const int newR, const int s)
{

    glColor3f((float)this->getColor().red()/255, (float)this->getColor().green()/255, (float)this->getColor().blue()/255);

    if (newX>newY)
        return;
    else if (newX == newY)
    {

        if (type == "FULL" || type == "SEMINORTH" || type == "SEMIEAST" || type == "QUADNE")
            glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(newY+y)/OGLHEIGHT);
        if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "QUADSE")
            glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(-newY+y)/OGLHEIGHT);
        if (type == "FULL" || type == "SEMINORTH" || type == "SEMIWEST" || type == "QUADNW")
            glVertex2f((float)(-newX+x)/(OGLWIDTH),(float)(newY+y)/OGLHEIGHT);
        if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIWEST" || type == "QUADSW")
            glVertex2f((float)(-newX+x)/(OGLWIDTH),(float)(-newY+y)/OGLHEIGHT);
        //qDebug()<<"  Step:" <<s <<"(" <<newX+x <<"," <<newY+y <<") calculated";
        //qDebug()<<"    (" <<newX+x <<"," <<-newY+y <<")";
        //qDebug()<<"    (" <<-newX+x <<"," <<newY+y <<")";
        //qDebug()<<"    (" <<-newX+x <<"," <<-newY+y <<")";
        if (this->filled)
            bresenhamLine(newX+x, newY+y, -newX+x, newY+y);
        bresenham(newX+1, newY, newR+2*newX, s+1);
    }
    else if (newR < 0)
    {
        if (type == "FULL" || type == "SEMINORTH" || type == "SEMIEAST" || type == "SEMIWEST" || type == "QUADNE" || type == "QUADNW")
        {
            if (type == "FULL" || type == "SEMINORTH" || type == "SEMIEAST" || type == "QUADNE")
            {
                glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(newY+y)/OGLHEIGHT); //NORTH //EAST //QUADNE
                glVertex2f((float)(newY+x)/(OGLWIDTH),(float)(newX+y)/OGLHEIGHT); //NORTH //EAST //QUADNE
            }
            if (type == "FULL" || type == "SEMINORTH" || type == "SEMIWEST" || type == "QUADNW")
            {
                glVertex2f((float)(-newX+x)/(OGLWIDTH),(float)(newY+y)/OGLHEIGHT); //NORTH //WEST //QUADNW
                glVertex2f((float)(-newY+x)/(OGLWIDTH),(float)(newX+y)/OGLHEIGHT); //NORTH //WEST //QUADNW
            }
        }
        if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "SEMIWEST" || type == "QUADSE" || type == "QUADSW")
        {
            if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "QUADSE")
            {
                glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(-newY+y)/OGLHEIGHT); //SOUTH //EAST //QUADSE
                glVertex2f((float)(newY+x)/(OGLWIDTH),(float)(-newX+y)/OGLHEIGHT); //SOUTH //EAST //QUADSE
            }
            if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIWEST" || type == "QUADSW")
            {
                glVertex2f((float)(-newX+x)/(OGLWIDTH),(float)(-newY+y)/OGLHEIGHT); //SOUTH /WEST //QUADSW
                glVertex2f((float)(-newY+x)/(OGLWIDTH),(float)(-newX+y)/OGLHEIGHT); //SOUTH //WEST //QUADSW
            }
        }
        /*qDebug()<<"  Step:" <<s <<"(" <<newX+x <<"," <<newY+y <<") calculated";
        qDebug()<<"    (" <<newX+x <<"," <<-newY+y <<")";
        qDebug()<<"    (" <<-newX+x <<"," <<newY+y <<")";
        qDebug()<<"    (" <<-newX+x <<"," <<-newY+y <<")";
        qDebug()<<"    (" <<newY+x <<"," <<newX+y <<")";
        qDebug()<<"    (" <<newY+x <<"," <<-newX+y <<")";
        qDebug()<<"    (" <<-newY+x <<"," <<newX+y <<")";
        qDebug()<<"    (" <<-newY+x <<"," <<-newX+y <<")";*/
        if (this->filled)
        {
            bresenhamLine(newX+x, newY+y, -newX+x, newY+y);
            bresenhamLine(newY+x, newX+y, -newY+x, newX+y);
            bresenhamLine(newX+x, -newY+y, -newX+x, -newY+y);
            bresenhamLine(newY+x, -newX+y, -newY+x, -newX+y);
        }
        bresenham(newX+1, newY, newR+2*newX, s+1);
    }
    else
    {
        if (type == "FULL" || type == "SEMINORTH" || type == "SEMIEAST" || type == "SEMIWEST" || type == "QUADNE" || type == "QUADNW")
        {
            if (type == "FULL" || type == "SEMINORTH" || type == "SEMIEAST" || type == "QUADNE")
            {
                glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(newY+y-1)/OGLHEIGHT);
                glVertex2f((float)(newY+x)/(OGLWIDTH),(float)(newX+y-1)/OGLHEIGHT);
            }
            if (type == "FULL" || type == "SEMINORTH" || type == "SEMIWEST" || type == "QUADNW")
            {
                glVertex2f((float)(-newX+x)/(OGLWIDTH),(float)(newY+y-1)/OGLHEIGHT);
                glVertex2f((float)(-newY+x)/(OGLWIDTH),(float)(newX+y-1)/OGLHEIGHT);
            }
        }
        if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "SEMIWEST" || type == "QUADSE" || type == "QUADSW")
        {
            if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIEAST" || type == "QUADSE")
            {
                glVertex2f((float)(newX+x)/(OGLWIDTH),(float)(-newY+y-1)/OGLHEIGHT);
                glVertex2f((float)(newY+x)/(OGLWIDTH),(float)(-newX+y-1)/OGLHEIGHT);
            }
            if (type == "FULL" || type == "SEMISOUTH" || type == "SEMIWEST" || type == "QUADSW")
            {
                glVertex2f((float)(-newX+x)/(OGLWIDTH),(float)(-newY+y-1)/OGLHEIGHT);
                glVertex2f((float)(-newY+x)/(OGLWIDTH),(float)(-newX+y-1)/OGLHEIGHT);
            }
        }
        /*qDebug()<<"  Step:" <<s <<"(" <<newX+x <<"," <<newY+y-1 <<") calculated";
        qDebug()<<"    (" <<newX+x <<"," <<-newY+y-1 <<")";
        qDebug()<<"    (" <<-newX+x <<"," <<newY+y-1 <<")";
        qDebug()<<"    (" <<-newX+x <<"," <<-newY+y-1 <<")";
        qDebug()<<"    (" <<newY+x <<"," <<newX+y-1 <<")";
        qDebug()<<"    (" <<newY+x <<"," <<-newX+y-1 <<")";
        qDebug()<<"    (" <<-newY+x <<"," <<newX+y-1 <<")";
        qDebug()<<"    (" <<-newY+x <<"," <<-newX+y-1 <<")";*/
        if (this->filled)
        {
            bresenhamLine(newX+x, newY+y, -newX+x, newY+y);
            bresenhamLine(newY+x, newX+y, -newY+x, newX+y);
            bresenhamLine(newX+x, -newY+y, -newX+x, -newY+y);
            bresenhamLine(newY+x, -newX+y, -newY+x, -newX+y);
        }
        bresenham(newX+1, newY-1, newR+2*(newX-newY), s+1);
    }
    //Draw a line to complete the semi/quad circle.
    if (type != "FULL")
    {

    }

    this->current = true;

    return;
}

QString openGLCircle::name()
{
    return QString("openGLCircle");
}

void openGLCircle::update(int newX, int newY)
{
    this->x = newX;
    this->y = newY;

    return;
}



void openGLCircle::bresenhamLine(int x1, int y1, int x2, int y2)
{
    glColor3f((float)this->getFillColor().red()/255, (float)this->getFillColor().green()/255, (float)this->getFillColor().blue()/255);

    //Horizontal line
    if (y1 == y2)
    {
        int x11;
        int x22;
        if (x2-x1 > 0)
        {
            x11 = x1;
            x22 = x2;
        }
        else
        {
            x11 = x2;
            x22 = x1;
        }
        for(; x11 <= x22; x11++)
            glVertex2f((float)(x11)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);

        return;
    }
    //Line goes from left to right
    /*else if (x1 < x2)
    {
        xStep = 1;
        if (y2-y1 > 0)
            yStep = 1;
        else
            yStep = -1;

    }
    //Line goes from right to left
    else if (x1 > x2)
    {
        xStep = -1;
        if (y2-y1 > 0)
            yStep = 1;
        else
            yStep = -1;

    }
    //If slope is 1
    if (dx == dy)
    {
        if (y1 > y2)
            yStep = -1;
        else
            yStep = 1;

        glVertex2f((float)(x1)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);

        if (x1< x2)
            for(int x= 1; x1+x<=x2;x++)
                glVertex2f((float)(x1+(x))/(OGLWIDTH),(float)(y1+(yStep*x))/OGLHEIGHT);
        if (x1>= x2)
            for(int x= -1; x1+x>=x2;x--)
                glVertex2f((float)(x1+(x))/(OGLWIDTH),(float)(y1+((-1)*yStep*x))/OGLHEIGHT);
    }
    //Slope is less than 1
    else if (dx > dy)
    {
        if (pk<0)
        {
            glVertex2f((float)(x1+xStep)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
            bresenhamLine(x1+xStep, y1, x2, y2, pk + 2*dy);
        }
        else
        {
            glVertex2f((float)(x1+xStep)/(OGLWIDTH),(float)(y1+yStep)/OGLHEIGHT);
            bresenhamLine(x1+xStep, y1+yStep, x2, y2, pk + 2*dy - 2*dx);
        }
    }
    //Slope is greater than 1
    else
    {
        if (pk<0)
        {
            glVertex2f((float)(x1)/(OGLWIDTH),(float)(y1+yStep)/OGLHEIGHT);
            bresenhamLine(x1, y1+yStep, x2, y2, pk + 2*dx);
        }
        else
        {
            glVertex2f((float)(x1+xStep)/(OGLWIDTH),(float)(y1+yStep)/OGLHEIGHT);
            bresenhamLine(x1+xStep, y1+yStep, x2, y2, pk + 2*dx - 2*dy);
        }
    }*/


    return;
}
