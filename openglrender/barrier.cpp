#include "barrier.h"

barrier::barrier()
{
    this->destructable = false;
}

barrier::~barrier()
{

}

QString barrier::name()
{
    return "barrier";
}
