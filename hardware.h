#pragma once
#include <thread>
#include "command.h"
#include "threadsafe_queue.h"

class Hardware
{
private:
    threadsafe_queue<Command>* p_mq;
    std::thread hw_thread;
public:
    Hardware(threadsafe_queue<Command>* p);
    ~Hardware();
    void control();
    void run();
};
