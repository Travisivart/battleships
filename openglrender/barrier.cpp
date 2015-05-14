#include "barrier.h"

barrier::barrier()
{
    this->destructable = false;

    this->scale(3.0f,3.0f,3.0f);
}

barrier::barrier(GLMmodel *wall)
{
    this->translation[0] = 0.0f;
    this->translation[1] = 0.0f;
    this->translation[2] = 0.0f;

    this->rotation[0] = 0.0f;
    this->rotation[1] = 0.0f;
    this->rotation[2] = 0.0f;

    this->scaling[0] = 8.0f;
    this->scaling[1] = 8.0f;
    this->scaling[2] = 8.0f;

    this->mode = GLM_MATERIAL;
    this->mesh=wall;

    this->getBox().calculateBox(this->mesh);
    this->box.calculateBox(this->mesh);

    this->destructible = false;
    this->alive = true;
}

barrier::~barrier()
{

}

QString barrier::name()
{
    return "barrier";
}
