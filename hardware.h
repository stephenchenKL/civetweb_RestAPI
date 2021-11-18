#pragma once

#include "command.h"
#include "threadsafe_queue.h"

class Hardware
{
private:
    threadsafe_queue<Command>* p_mq;
public:
    Hardware(threadsafe_queue<Command>* p);
    ~Hardware();
    void control();
};
