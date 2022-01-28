#pragma once
#include <thread>
#include <future>
#include "command.h"
#include "threadsafe_queue.h"


class InstrumentCtrl
{
private:
    threadsafe_queue<Command>* p_mq;
    std::thread hw_thread;
public:
    InstrumentCtrl(threadsafe_queue<Command>* p);
    ~InstrumentCtrl();
    void control();
    void run();
    void getInfo(std::promise<ENGN_Info> & prom);
};
