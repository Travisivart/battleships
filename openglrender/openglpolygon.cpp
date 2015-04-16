#include "openglpolygon.h"

openGLPolygon::openGLPolygon()
{
    vertices = new QList<openGLPoint*>();

    closed = false;

    filled = false;

    finished = false;

    current = false;

    this->goraud = false;

    this->yMin = 0;
    this->yMax = 0;

    //Create a new bucket
    this->set = new bucket();

    color = QColor(rand()%256,rand()%256,rand()%256);
}

openGLPolygon::openGLPolygon(openGLPoint *start)
{
    vertices = new QList<openGLPoint*>();
    closed = false;

    filled = false;

    finished = false;

    current = false;

    this->goraud = false;

    this->yMin = start->getY();
    this->yMax = start->getY();

    vertices->append(start);

    //Create a new bucket
    this->set = new bucket();

    color = QColor(rand()%256,rand()%256,rand()%256);
}

openGLPolygon::openGLPolygon(QList<openGLPoint*> *newVertices)
{
    delete this->vertices;

    vertices = newVertices;

    closed = false;

    filled = false;

    finished = false;

    current = false;

    this->goraud = false;

    //Find and set the yMin and yMax
    this->yMin = newVertices->at(0)->getY();
    this->yMax = newVertices->at(0)->getY();

    for( int i=0; i< newVertices->size (); i++)
    {
        if( this->yMin > newVertices->at(i)->getY())
            this->yMin = newVertices->at(i)->getY();

        if( this->yMax < newVertices->at(i)->getY())
            this->yMax = newVertices->at(i)->getY();
    }

    //Create a new bucket
    this->set = new bucket();

    color = QColor(rand()%256,rand()%256,rand()%256);
}

openGLPolygon::~openGLPolygon()
{
    delete vertices;

    delete set;
}

void openGLPolygon::add(openGLPoint *newVertex)
{
    if (this->vertices->size() == 0)
    {
        this->yMin = newVertex->getY();
        this->yMax = newVertex->getY();
    }
    else
    {
        if( this->yMin > newVertex->getY())
            this->yMin = newVertex->getY();

        if( this->yMax < newVertex->getY())
            this->yMax = newVertex->getY();
    }

    vertices->append(newVertex);
}

openGLPoint *openGLPolygon::at(const int i)
{
    if (vertices->size() >= i)
        return vertices->at(i);

    return NULL;
}

void openGLPolygon::removeAt(int i)
{
    //delete the data
    delete this->vertices->at(i);

    //remove the pointer from the list
    this->vertices->removeAt(i);
}

void openGLPolygon::setColor(const QColor &newColor)
{
    color = newColor;
}

void openGLPolygon::setClosed(const bool &newClosed)
{
    closed = newClosed;
}

void openGLPolygon::setGoraud(const bool &newGoraud)
{
    this->goraud = newGoraud;
}

int openGLPolygon::size()
{
    return vertices->size();
}

void openGLPolygon::finish()
{
    this->finished = true;
}

void openGLPolygon::unFinish()
{
    this->finished = false;
}

bool openGLPolygon::isFinished()
{
    return this->finished;
}

bool openGLPolygon::isFilled()
{
    return this->filled;
}

void openGLPolygon::createSet()
{
    edge *e;
    openGLPoint *p1, *p2;
    int i;

    /* Testing data
    lines->clear();
    lines->append(new openGLLine(0,0,150,40));
    lines->append(new openGLLine(150,40,30,-50));
    lines->append(new openGLLine(30,-50,0,0));
    this->yMin = -50;
    this->yMax = 40;


    lines->clear();
    lines->append(new openGLLine(0,0,-5,40));
    lines->append(new openGLLine(-5,40,15,10));
    lines->append(new openGLLine(15,10,30,60));
    lines->append(new openGLLine(30,60,40,-20));
    lines->append(new openGLLine(40,-20,0,0));
    this->yMin = -20;
    this->yMax = 60;
*/

    //Initialize set
    set->init(this->yMax - this->yMin);

    for(i=0; i < this->vertices->size()-1; i++)
    {
        if (vertices->at(i)->getY() != vertices->at(i+1)->getY())
        {
            e = new edge();

            p1 = vertices->at(i);
            p2 = vertices->at(i+1);

            //Set xMin for the edge to whichever point has the lowest Y value
            e->setXMin(p1->getY() < p2->getY() ? p1->getX() : p2->getX() );

            //Set YMax to whichever has the highest Y value
            e->setYMax(p1->getY() < p2->getY() ? p2->getY() : p1->getY() );

            e->setDx(p2->getX() - p1->getX());
            e->setDy(p2->getY() - p1->getY());

            e->setColor(p1->getY() < p2->getY() ? p1->getColor() : p2->getColor(), p1->getY() < p2->getY() ? p2->getColor() : p1->getColor());

            this->set->addAt(p1->getY() < p2->getY() ? p1->getY() - this->yMin : p2->getY() - this->yMin, e);
        }
    }
    //Create the final edge - Link the final point to the first point
    if(i > 0)
    {
        if (vertices->at(i)->getY() != vertices->at(0)->getY())
        {
            e = new edge();

            p1 = vertices->at(i);
            p2 = vertices->at(0);

            //Set xMin for the edge to whichever point has the lowest Y value
            e->setXMin(p1->getY() < p2->getY() ? p1->getX() : p2->getX() );

            //Set YMax to whichever has the highest Y value
            e->setYMax(p1->getY() < p2->getY() ? p2->getY() : p1->getY() );

            e->setDx(p2->getX() - p1->getX());
            e->setDy(p2->getY() - p1->getY());

            e->setColor(p1->getY() < p2->getY() ? p1->getColor() : p2->getColor(), p1->getY() < p2->getY() ? p2->getColor() : p1->getColor());

            this->set->addAt(p1->getY() < p2->getY() ? p1->getY() - this->yMin : p2->getY() - this->yMin, e);
        }
    }

    set->sort();

    if(this->debug)
        qDebug()<<"Printing SET:";
    for(int i=0; i<set->getSize(); i++)
    {
        if(set->getAt(i)->size() > 0)
        {
            if(this->debug)
                qDebug()<<"  At bucket[" <<i <<"]";
            for(int j=0; j<set->getAt(i)->size(); j++)
            {
                e = set->getAt(i)->at(j);
                if(this->debug)
                    qDebug()<<"    (yMax:" <<e->getYMax() <<", xMin:" <<e->getXMin() <<", dx:" <<e->getDx() <<", dy:" <<e->getDy() <<(j==set->getAt(i)->size()-1 ? ", NULL)" : ", ->)") <<"";
            }
        }
    }
    if(this->debug)
        qDebug()<<"Finished building set.";
}

void openGLPolygon::draw()
{
    glColor3f(0.0f,0.0f,0.0f);

    for(int i=0; i < this->vertices->size(); i++)
    {
        if ( i == this->vertices->size()-1)
        {
            if(qAbs(this->vertices->at(0)->getY()-this->vertices->at(i)->getY()) < qAbs(this->vertices->at(0)->getX()-this->vertices->at(i)->getX()))
                bresenham(this->vertices->at(i), this->vertices->at(0), 2*qAbs(this->vertices->at(0)->getY()-this->vertices->at(i)->getY())-qAbs(this->vertices->at(0)->getX()-this->vertices->at(i)->getX()));
            else
                bresenham(this->vertices->at(i), this->vertices->at(0), 2*qAbs(this->vertices->at(0)->getX()-this->vertices->at(i)->getX())-qAbs(this->vertices->at(0)->getY()-this->vertices->at(i)->getY()));
        }
        else
        {
            if(qAbs(this->vertices->at(i+1)->getY()-this->vertices->at(i)->getY()) < qAbs(this->vertices->at(i+1)->getX()-this->vertices->at(i)->getX()))
                bresenham(this->vertices->at(i), this->vertices->at(i+1), 2*qAbs(this->vertices->at(i+1)->getY()-this->vertices->at(i)->getY())-qAbs(this->vertices->at(i+1)->getX()-this->vertices->at(i)->getX()));
            else
                bresenham(this->vertices->at(i), this->vertices->at(i+1), 2*qAbs(this->vertices->at(i+1)->getX()-this->vertices->at(i)->getX())-qAbs(this->vertices->at(i+1)->getY()-this->vertices->at(i)->getY()));
        }

        //Calculate dx and dy values
        //int dx = qAbs(x2 - x1);
        //int dy = qAbs(y2 - y1);

        //Plot starting point

        //qDebug() <<"Drawing line: Initial point at: (" <<p1->getX() << "," <<p1->getY() <<") dx=" << dx << " dy=" <<dy;
        //glVertex2f(x1/OGLWIDTH,y1/OGLHEIGHT);

        //openGLPoint p1;
        //openGLPoint p2;
        //p1.setX(x1);
        //p1.setY(y1);
        //p2.setX(x2);
        //p2.setY(y2);
        //if(qAbs((y2-y1)) < qAbs((x2-x1)))
        //bresenham(&p1, &p2, 2*dy-dx);
        // else
        //bresenham(&p1, &p2, 2*dx-dy);

    }
}

void openGLPolygon::drawFilled()
{
    QList<edge*>* aet = new QList<edge*>();
    edge* e;
    QList<edge*> *temp;
    float x1, x2;
    openGLPoint p1;
    openGLPoint p2;
    int i;

    glColor3f((float)color.red()/255,(float)color.green()/255,(float)color.blue()/255);

    //qDebug()<<"Calling Create set";
    //if(this->set->getSize() == 0)

    //if(set->getSize() == 0)
    this->createSet();

    for(i = 0; i < set->getSize(); i++)
    {
        //qDebug()<<"Starting scanline: " <<i;
        //Add entering edges
        for (int j = 0; j < set->getAt(i)->size(); j++)
        {
            temp = set->getAt(i);
            if(this->debug)
                qDebug()<<"  Adding to aet:" <<temp->at(j)->getXMin() <<temp->at(j)->getYMax();
            aet->append(temp->at(j));
        }
        //qDebug()<<"Remove";
        //Remove invalid edges
        for (int j=0; j < aet->size();)
        {
            //qDebug()<<"Y max for" <<j <<"is: " <<aet->at(j)->getYMax();
            if(aet->at(j)->getYMax() <= this->yMin + i)
            {
                if(this->debug)
                    qDebug()<<"  Removing from aet" <<aet->at(j)->getXMin() <<aet->at(j)->getYMax();
                delete aet->at(j);
                aet->removeAt(j);
            }
            else
                j++;

        }
        //qDebug()<<"Sort";
        //Sort the aet
        for(int j=0;j<aet->size();j++)
        {
            e = aet->at(j);

            for(int k=j;k<aet->size();k++)
            {
                if(aet->at(k)->getXMin ()<e->getXMin ())
                    e = aet->at(k);
            }
            aet->removeAll (e);
            aet->insert (j,e);
        }

        //qDebug()<<"Aet size at i=" <<i <<"  " <<aet->size();

        //Fill
        //qDebug()<<"Fill";
        for( int j=0; j < aet->size(); j++)
        {
            //qDebug()<<"Drawing line between: " <<"(" <<aet->at(j)->getXMin() <<"," <<this->yMin+i <<") and (" <<aet->at(j+1)->getXMin() <<"," <<this->yMin+i <<")";
            //glVertex2f((float)(p1->getX())/(OGLWIDTH),(float)(p1->getY())/OGLHEIGHT);
            //glVertex2f(aet->at(j)->getXMin()/OGLWIDTH,(float)(this->yMin+i)/OGLHEIGHT);
            //glVertex2f(aet->at(j+1)->getXMin()/OGLWIDTH,(float)(this->yMin+i)/OGLHEIGHT);


            x1 = aet->at(j)->getXMin() < aet->at(j+1)->getXMin() ? aet->at(j)->getXMin() : aet->at(j+1)->getXMin();
            x2 = aet->at(j)->getXMin() < aet->at(j+1)->getXMin() ? aet->at(j+1)->getXMin() : aet->at(j)->getXMin();

            //Plot starting point

            //qDebug() <<"Drawing line: Initial point at: (" <<p1->getX() << "," <<p1->getY() <<") dx=" << dx << " dy=" <<dy;
            //glVertex2f(x1/OGLWIDTH,(float)(this->yMin+i)/OGLHEIGHT);

            p1.setX(x1);
            p1.setY(yMin + i);
            p2.setX(x2);
            p2.setY(yMin + i);
            p1.setColor(e->getColorP1());
            p2.setColor(e->getColorP2());
            bresenham(&p1, &p2, -qAbs(x2 - x1));

            //qDebug()<<"DX: " <<(aet->at(j)->getXMin() + ((float)aet->at(j)->getDx()/(float)aet->at(j)->getDy()));
            aet->at(j)->setXMin(aet->at(j)->getXMin() + ((float)aet->at(j)->getDx()/(float)aet->at(j)->getDy()));
            aet->at(j+1)->setXMin(aet->at(j+1)->getXMin() + ((float)aet->at(j+1)->getDx()/(float)aet->at(j+1)->getDy()));
            if(this->goraud)
            {
                aet->at(j)->updateColors();
                aet->at(j+1)->updateColors();
            }
            j++;
        }


        if(this->debug)
        {
            qDebug()<<"AET After scanline:" <<i <<"(y = " <<this->yMin+i << ")";
            for( int j = 0; j< aet->size(); j++)
                qDebug()<<"  (" <<aet->at(j)->getXMin() <<"," <<aet->at(j)->getYMax() <<")";
        }
    }

    //Draw final points
    for( int j=0; j < aet->size(); j++)
    {
        x1 = aet->at(j)->getXMin() < aet->at(j+1)->getXMin() ? aet->at(j)->getXMin() : aet->at(j+1)->getXMin();
        x2 = aet->at(j)->getXMin() < aet->at(j+1)->getXMin() ? aet->at(j+1)->getXMin() : aet->at(j)->getXMin();
        p1.setX(x1);
        p1.setY(yMin + i);
        p2.setX(x2);
        p2.setY(yMin + i);
        bresenham(&p1, &p2, -qAbs(x2 - x1));
        j++;
    }
    //Remove final aet edges
    for (int j=0; j < aet->size();)
    {
        //qDebug()<<"Y max for" <<j <<"is: " <<aet->at(j)->getYMax();
        if(aet->at(j)->getYMax() <= this->yMin + i)
        {
            if(this->debug)
                qDebug()<<"  Removing from aet" <<aet->at(j)->getXMin() <<aet->at(j)->getYMax();
            delete aet->at(j);
            aet->removeAt(j);
        }
        else
            j++;
    }
    if(this->debug)
    {
        qDebug()<<"AET After scanline:" <<i <<"(y = " <<this->yMin+i << ")";
        for( int j = 0; j< aet->size(); j++)
            qDebug()<<"  (" <<aet->at(j)->getXMin() <<"," <<aet->at(j)->getYMax() <<")";
        qDebug()<<"Finished drawing.";
    }

    delete aet;
}

QString openGLPolygon::name()
{
    return QString("openGLPolygon");
}



void openGLPolygon::bresenham(openGLPoint* bp1, openGLPoint* bp2, const int pk)
{
    int xStep = 0;
    int yStep = 0;
    int dx = qAbs((bp2->getX()-bp1->getX()));
    int dy = qAbs((bp2->getY()-bp1->getY()));
    openGLPoint *p;
    float a, red, green, blue;

    //qDebug()<<"red: " <<bp1->getColor().red();

    //glColor3f((float)bp1->getColor().red()/255, (float)bp1->getColor().green()/255, (float)bp1->getColor().blue()/255);

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
            if(this->goraud)
            {
                a = (y1-bp1->getY())/(bp2->getY()-bp1->getY());
                red = a*bp2->getColor().red() + (1-a)*bp1->getColor().red();
                green = a*bp2->getColor().green() + (1-a)*bp1->getColor().green();
                blue = a*bp2->getColor().blue() + (1-a)*bp1->getColor().blue();
                glColor3f(red/255,green/255,blue/255);
            }
            glVertex2f((float)(bp1->getX())/(OGLWIDTH),(float)(y1)/OGLHEIGHT);
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

        for(;x1 <= x2; x1++)
        {
            if(this->goraud)
            {
                a = (x1-bp1->getX())/(bp2->getX()-bp1->getX());
                red = a*bp2->getColor().red() + (1-a)*bp1->getColor().red();
                green = a*bp2->getColor().green() + (1-a)*bp1->getColor().green();
                blue = a*bp2->getColor().blue() + (1-a)*bp1->getColor().blue();
                glColor3f(red/255,green/255,blue/255);
            }
            glVertex2f((float)(x1)/(OGLWIDTH),(float)(bp1->getY())/OGLHEIGHT);
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
            p = new openGLPoint(bp1->getX()+xStep,bp1->getY(), QColor(0.0,0.0,0.0));
            bresenham(p, bp2, pk + 2*dy);
            delete p;
        }
        else
        {
            glVertex2f((float)(bp1->getX()+xStep)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
            p = new openGLPoint(bp1->getX()+xStep,bp1->getY()+yStep, QColor(0.0,0.0,0.0));
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
            p = new openGLPoint(bp1->getX(),bp1->getY()+yStep, QColor(0.0,0.0,0.0));
            bresenham(p, bp2, pk + 2*dx);
            delete p;
        }
        else
        {
            glVertex2f((float)(bp1->getX()+xStep)/(OGLWIDTH),(float)(bp1->getY()+yStep)/OGLHEIGHT);
            p = new openGLPoint(bp1->getX()+xStep,bp1->getY()+yStep, QColor(0.0,0.0,0.0));
            bresenham(p, bp2, pk + 2*dx - 2*dy);
            delete p;
        }
    }


    return;
}

/*void openGLPolygon::floodFill(float x, float y)
{

    glBegin(GL_POINTS);

    glColor3f(0.5f,0.0f,1.0f);
    unsigned char pixel[4];
    glReadPixels(OGLWIDTH/2, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    qDebug()<<"pixel[0]" <<pixel[0]<<"pixel[1]" <<pixel[1]<<"pixel[2]" <<pixel[2]<<"pixel[3]" <<pixel[3];

    glVertex2f(0, 0);
    ///glVertex2f(0,0);
    //glVertex2f(0.5,0.5);
    //glVertex2f(0.25,0.25);

    glReadPixels(OGLWIDTH/2, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    qDebug()<<"pixel[0]" <<pixel[0]<<"pixel[1]" <<pixel[1]<<"pixel[2]" <<pixel[2]<<"pixel[3]" <<pixel[3];
    //if()

    glEnd();

}
*/
