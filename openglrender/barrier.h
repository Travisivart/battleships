#ifndef BARRIER_H
#define BARRIER_H

#include "openglmesh.h"

class barrier : public openGLMesh
{
public:
    barrier();
    barrier(GLMmodel *wall);
    ~barrier();

    QString name();

private:
    bool destructable;
};

#endif // BARRIER_H
