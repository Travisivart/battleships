#include "openglpolyedge.h"

openGLPolyEdge::openGLPolyEdge()
{
    p1 = new openGLPoint(0,0,0);
    p2 = new openGLPoint(0,0,0);
}

openGLPolyEdge::~openGLPolyEdge()
{
    delete p1;
    delete p2;
}

