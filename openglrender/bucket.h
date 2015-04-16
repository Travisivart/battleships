#ifndef BUCKET_H
#define BUCKET_H

#include <QList>
#include <QDebug>

#include "edge.h"

class bucket
{

public:
    bucket();
    bucket(const int &newSize);
    ~bucket();

    void init(const int &newSize);

    void addAt(const int &slot, edge* e);

    QList<edge*>* getAt(const int &slot);

    void sort();
    void sortAt(const int &slot);

    int getSize();

    void removeAll();

private:
    QList<edge*> **list;
    int size;
};

#endif // BUCKET_H
