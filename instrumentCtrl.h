#pragma once
#include <thread>
#include <future>
#include "command.h"
#include "threadsafe_queue.h"


class InstrumentCtrl
{
private:
    threadsafe_queue<Command>* pCq;
    threadsafe_queue<ENGN_Info>* pRq;
    std::thread hw_thread;
public:
    InstrumentCtrl(threadsafe_queue<Command>* p, threadsafe_queue<ENGN_Info>* i);
    ~InstrumentCtrl();
    void control();
    void run();
    void getInfo(std::promise<ENGN_Info> & prom);
};
