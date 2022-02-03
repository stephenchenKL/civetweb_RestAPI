#include <thread>
#include <iostream>
#include "instrumentCtrl.h"

// extern threadsafe_queue<ENGN_Info> rslt_q;



InstrumentCtrl::InstrumentCtrl(threadsafe_queue<Command>* p, threadsafe_queue<ENGN_Info>* i)
{
    pCq = p;
    pRq = i;
}

InstrumentCtrl::~InstrumentCtrl()
{
}

void  InstrumentCtrl::control()
{
    std::cout << "Ctrl thread is waiting for cmd ... \n";
    Command cmd;
    while(true){
        pCq->wait_and_pop(cmd);
        if(0 == cmd.cmd.compare("info"))
        {
            ENGN_Info info;
            info.bCanAutoGain = true;
            info.bHasDark = false;
            info.bHasRef = true;
            info.bHasVariableSpeed = false;
            info.bMapOK = true;
            //rslt_q.push(info);
            pRq->push(info);
        }
        if(0 == cmd.cmd.compare("exit"))
        {            
            std::cout << "Exit Intrument Control thread ..." << std::endl;
            pCq->push(cmd);
            break;
        }
        std::cout << "cmd.cmd :" << cmd.cmd << std::endl;
        std::cout << "cmd.para1 :" << cmd.para1 << std::endl;
        std::cout << "cmd.para2 :" << cmd.para2 << std::endl;
        std::cout << "cmd.para3 :" << cmd.para3 << std::endl;
        std::cout << "cmd.para4 :" << cmd.para4 << std::endl;
        std::cout << "cmd.para5 :" << cmd.para5 << std::endl;
        std::cout << "cmd.para6 :" << cmd.para6 << std::endl;
        
        
    }
}

void InstrumentCtrl::run()
{
    hw_thread = std::thread(&InstrumentCtrl::control, this);
    
}

void InstrumentCtrl::getInfo(std::promise<ENGN_Info>& prom)
{
    ENGN_Info info;
    info.bCanAutoGain = true;
    info.bHasDark = false;
    info.bHasRef = true;
    info.bHasVariableSpeed = false;
    info.bMapOK = true;
    prom.set_value(info);
}




