#include "openglline.h"

openGLLine::openGLLine()
{
    p1 = new openGLPoint(0,0,0);
    p2 = new openGLPoint(0,0,0);
    color = QColor(0,0,0);

    width = 1;
    style = Line;
}

openGLLine::openGLLine(openGLPoint* newP1, openGLPoint* newP2)
{
    p1 = newP1;
    p2 = newP2;
    width = 1;
}

openGLLine::openGLLine(const float &newX1, const float &newY1, const float &newX2, const float &newY2)
{
    p1 = new openGLPoint(newX1, newY1);
    p2 = new openGLPoint(newX2, newY2);

    width = 1;
}

openGLLine::openGLLine(const float &newX1, const float &newY1, const float &newZ1, const float &newX2, const float &newY2, const float newZ2)
{
    p1 = new openGLPoint(newX1, newY1, newZ1);
    p2 = new openGLPoint(newX2, newY2, newZ2);

    width = 1;
}

openGLLine::openGLLine(const float &newX1, const float &newY1, const float &newX2, const float &newY2, const QColor &newColor)
{
    p1 = new openGLPoint(newX1, newY1);
    p2 = new openGLPoint(newX2, newY2);

    color = newColor;
    width = 1;
}

openGLLine::~openGLLine()
{
    delete p1;
    delete p2;
}

QString openGLLine::name()
{
    return QString("openGLLine");
}

void openGLLine::setColor(const QColor &newColor)
{
    color = newColor;
}

void openGLLine::setStyle(const QString &newStyle)
{
    style = newStyle;
}

void openGLLine::setP1(const float &x1, const float &y1)
{
    p1->setX(x1);
    p1->setY(y1);
}

void openGLLine::setP1(const float &x1, const float &y1, const float &z1)
{
    p1->setX(x1);
    p1->setY(y1);
    p1->setZ(z1);
}

void openGLLine::setP1(openGLPoint* newP1)
{
    p1 = newP1;
}

void openGLLine::setP2(const float &x2, const float &y2)
{
    p2->setX(x2);
    p2->setY(y2);
}

void openGLLine::setP2(const float &x2, const float &y2, const float &z2)
{
    p2->setX(x2);
    p2->setY(y2);
    p2->setZ(z2);
}

void openGLLine::setP2(openGLPoint* newP2)
{
    p2 = newP2;
}

void openGLLine::setWidth(const int &newWidth)
{
    width = newWidth;
}

openGLPoint* openGLLine::getP1()
{
    return this->p1;
}

openGLPoint* openGLLine::getP2()
{
    return this->p2;
}

QColor openGLLine::getColor()
{
    return color;
}

float openGLLine::x1()
{
    return p1->getX();
}

float openGLLine::y1()
{
    return p1->getY();
}

float openGLLine::z1()
{
    return p1->getZ();
}

float openGLLine::x2()
{
    return p2->getX();
}

float openGLLine::y2()
{
    return p2->getY();
}

float openGLLine::z2()
{
    return p2->getZ();
}

int openGLLine::getWidth()
{
    return width;
}

void openGLLine::draw()
{

    glColor3f((float)this->getColor().red()/255, (float)this->getColor().green()/255, (float)this->getColor().blue()/255);
    glVertex3f((float)(p1->getX())/(OGLWIDTH),(float)(p1->getY())/OGLHEIGHT, p1->getZ());
    glVertex3f((float)(p2->getX())/(OGLWIDTH),(float)(p2->getY())/OGLHEIGHT, p2->getZ());

    /*
    TRAVDEBUG ? qDebug() <<"BEGIN" <<this->name() <<"draw()" <<this->x1() <<this->y1() << this->x2() <<this->y2() : qDebug();
    glColor3f((float)this->getColor().red()/255, (float)this->getColor().green()/255, (float)this->getColor().blue()/255);

    //Calculate dx and dy values
    int dx = qAbs(this->x2() - this->x1());
    int dy = qAbs(this->y2() - this->y1());

    //Plot starting point

    //qDebug() <<"Drawing line: Initial point at: (" <<p1->getX() << "," <<p1->getY() <<") dx=" << dx << " dy=" <<dy;
    glVertex2f((float)(p1->getX())/(OGLWIDTH),(float)(p1->getY())/OGLHEIGHT);

    //Width loop
    for(int wx = 1; wx < this->width; wx++)
    {
        glVertex2f((float)(p1->getX()+wx)/(OGLWIDTH),(float)(p1->getY())/OGLHEIGHT);
        glVertex2f((float)(p1->getX()-wx)/(OGLWIDTH),(float)(p1->getY())/OGLHEIGHT);

        for(int wy = 1; wy < this->width; wy++)
        {
            glVertex2f((float)(p1->getX()+wx)/(OGLWIDTH),(float)(p1->getY()+wy)/OGLHEIGHT);
            glVertex2f((float)(p1->getX()+wx)/(OGLWIDTH),(float)(p1->getY()-wy)/OGLHEIGHT);
            glVertex2f((float)(p1->getX()-wx)/(OGLWIDTH),(float)(p1->getY()+wy)/OGLHEIGHT);
            glVertex2f((float)(p1->getX()-wx)/(OGLWIDTH),(float)(p1->getY()-wy)/OGLHEIGHT);
        }
    }
    if(qAbs((p2->getY()-p1->getY())) < qAbs((p2->getX()-p1->getX())))
        bresenham(p1, p2, 2*dy-dx);
    else
        bresenham(p1, p2, 2*dx-dy);
*/
}

void openGLLine::bresenham(openGLPoint* bp1, openGLPoint* bp2, const int pk)
{
    int xStep = 0;
    int yStep = 0;
    int dx = qAbs((bp2->getX()-bp1->getX()));
    int dy = qAbs((bp2->getY()-bp1->getY()));
    openGLPoint *p;

    int styleMod = 1;
    if (style == "Line")
        styleMod = 1;
    else if(style == "Dot")
        styleMod = 8;


    //Vertical line
    if (bp1->getX() == bp2->getX())
    {
        int y1;
        int y2;
        if (bp2->getY()-bp1->getY() > 0)
        {
            y1 = bp1->getY();
            y2 = bp2->getY();
        }
        else
        {
            y1 = bp2->getY();
            y2 = bp1->getY();
        }

        for(; y1 <= y2; y1++)
        {

            glVertex2f((float)(bp1->getX())/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
            //Width loop
            for(int wx = 1; wx < this->width; wx++)
            {
                glVertex2f((float)(bp1->getX()+wx)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
                glVertex2f((float)(bp1->getX()-wx)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
            }
        }



        return;
    }
    //Horizontal line
    else if (bp1->getY() == bp2->getY())
    {
        int x1;
        int x2;
        if (bp2->getX()-bp1->getX() > 0)
        {
            x1 = bp1->getX();
            x2 = bp2->getX();
        }
        else
        {
            x1 = bp2->getX();
            x2 = bp1->getX();
        }

        for(; x1 <= x2; x1++)
        {
            glVertex2f((float)(x1)/(OGLWIDTH),(float)(bp1->getY())/OGLHEIGHT);
            //Width loop
            for(int wy = 1; wy < this->width; wy++)
            {
                glVertex2f((float)(x1)/(OGLWIDTH),(float)(bp1->getY()+wy)/OGLHEIGHT);
                glVertex2f((float)(x1)/(OGLWIDTH),(float)(bp1->getY()-wy)/OGLHEIGHT);
                //glVertex2f((float)(bp1->getX()+wx)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
                //glVertex2f((float)(bp1->getX()-wx)/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
            }
        }



        return;
    }
    //Line goes from left to right
    else if (bp1->getX() < bp2->getX())
    {
        xStep = 1;
        if (bp2->getY()-bp1->getY() > 0)
            yStep = 1;
        else
            yStep = -1;

    }
    //Line goes from right to left
    else if (bp1->getX() > bp2->getX())
    {
        xStep = -1;
        if (bp2->getY()-bp1->getY() > 0)
            yStep = 1;
        else
            yStep = -1;

    }
    //If slope is 1
    if (dx == dy)
    {
        if (bp1->getY() > bp2->getY())
            yStep = -1;
        else
            yStep = 1;

        glVertex2f((float)(bp1->getX())/(OGLWIDTH),(float)(bp1->getY())/OGLHEIGHT);

        if (bp1->getX()< bp2->getX())
            for(int x= 1; bp1->getX()+x<=bp2->getX();x++)
                glVertex2f((float)(bp1->getX()+(x))/(OGLWIDTH),(float)(bp1->getY()+(yStep*x))/OGLHEIGHT);
        if (bp1->getX()>= bp2->getX())
            for(int x= -1; bp1->getX()+x>=bp2->getX();x--)
                glVertex2f((float)(bp1->getX()+(x))/(OGLWIDTH),(float)(bp1->getY()+((-1)*yStep*x))/OGLHEIGHT);
    }
    //Slope is less than 1
    else if (dx > dy)
    {
        if (pk<0)
        {
            glVertex2f((float)(bp1->getX()+xStep)/(OGLWIDTH),(float)(bp1->getY())/OGLHEIGHT);
            //Width loop
            for(int wx = 1; wx < this->width; wx++)
            {
                glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY())/OGLHEIGHT);
                glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY())/OGLHEIGHT);

                for(int wy = 1; wy < this->width; wy++)
                {
                    glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()-wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()-wy)/OGLHEIGHT);
                }
            }
            p = new openGLPoint(bp1->getX()+xStep,bp1->getY());
            bresenham(p, bp2, pk + 2*dy);
            delete p;
        }
        else
        {
            glVertex2f((float)(bp1->getX()+xStep)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
            //Width loop
            for(int wx = 1; wx < this->width; wx++)
            {
                glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
                glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);

                for(int wy = 1; wy < this->width; wy++)
                {
                    glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep-wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep-wy)/OGLHEIGHT);
                }
            }
            p = new openGLPoint(bp1->getX()+xStep,bp1->getY()+yStep);
            bresenham(p, bp2, pk + 2*dy - 2*dx);
            delete p;
        }
    }
    //Slope is greater than 1
    else
    {
        if (pk<0)
        {
            glVertex2f((float)(bp1->getX())/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
            //Width loop
            for(int wx = 1; wx < this->width; wx++)
            {
                glVertex2f((float)(bp1->getX()+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
                glVertex2f((float)(bp1->getX()-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);

                for(int wy = 1; wy < this->width; wy++)
                {
                    glVertex2f((float)(bp1->getX()+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep-wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep-wy)/OGLHEIGHT);
                }
            }
            p = new openGLPoint(bp1->getX(),bp1->getY()+yStep);
            bresenham(p, bp2, pk + 2*dx);
            delete p;
        }
        else
        {
            glVertex2f((float)(bp1->getX()+xStep)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
            //Width loop
            for(int wx = 1; wx < this->width; wx++)
            {
                glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
                glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);

                for(int wy = 1; wy < this->width; wy++)
                {
                    glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep+wx)/(OGLWIDTH),(float)(bp1->getY()+yStep-wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep+wy)/OGLHEIGHT);
                    glVertex2f((float)(bp1->getX()+xStep-wx)/(OGLWIDTH),(float)(bp1->getY()+yStep-wy)/OGLHEIGHT);
                }
            }
            p = new openGLPoint(bp1->getX()+xStep,bp1->getY()+yStep);
            bresenham(p, bp2, pk + 2*dx - 2*dy);
            delete p;
        }
    }


    return;
}
