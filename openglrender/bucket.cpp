#include "bucket.h"

bucket::bucket()
{
    size = 0;
}

bucket::bucket(const int &newSize)
{
    size = newSize;

    list = new QList<edge*> *[newSize];

    for(int i = 0; i < newSize; i++)
        list[i] = new QList<edge*>();

    /*
    qDebug()<<"Build Bucket";

    list = new QList<edge*> *[size];

    list[0] = new QList<edge*>();

    qDebug()<<"List[0]:" <<list[0]->size();

    this->list[0]->append(new edge());

    qDebug()<<"List[0]:" <<list[0]->size();
    */

}

bucket::~bucket()
{
    for(int i = 0; i < this->size; i++)
        delete list[i];

    delete list;
}

void bucket::init(const int &newSize)
{
    list = new QList<edge*> *[newSize];

    for(int i = 0; i < newSize; i++)
        list[i] = new QList<edge*>();

    this->size = newSize;
}

void bucket::addAt(const int &slot, edge *e)
{

    this->list[slot]->push_back(e);
    //qDebug()<<"List size at slot" <<slot <<list[slot]->size();
}

QList<edge *> *bucket::getAt(const int &slot)
{
    return this->list[slot];
}

void bucket::sort()
{
    edge* min;

    //qDebug()<<"Set.sort:"<<this->size;
    for (int i=0; i<this->size; i++)
    {
        //qDebug()<<"  list["<<i<<"].size:" <<list[i]->size();
        for(int j=0;j<list[i]->size();j++)
        {
            min = list[i]->at(j);

            for(int k=j;k<list[i]->size();k++)
            {
                if(list[i]->at(k)->getXMin ()<min->getXMin ())
                    min = list[i]->at(k);
            }
            list[i]->removeAll (min);
            list[i]->insert (j,min);
        }
    }

    /*for (int i=0; i<this->size; i++)
    {
        //qDebug()<<"  list["<<i<<"].size:" <<list[i]->size();
        for(int j=0;j<list[i]->size();j++)
        {
           qDebug()<<"At slot" <<i <<" xMin: " <<list[i]->at(j)->getXMin() <<" yMax: " <<list[i]->at(j)->getYMax();
        }
    }*/
   // qDebug()<<"Finished sort";
}

void bucket::sortAt(const int &slot)
{

}

int bucket::getSize()
{
    return this->size;
}

void bucket::removeAll()
{
    delete list;
    size = 0;
}
