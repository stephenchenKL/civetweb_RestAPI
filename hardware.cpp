#include <thread>
#include <iostream>
#include "hardware.h"



Hardware::Hardware(threadsafe_queue<Command>* p)
{
    p_mq = p;
}

Hardware::~Hardware()
{
}

void  Hardware::control()
{
    std::cout << "Ctrl thread is waiting for cmd ... ";
    Command cmd;
    while(true){
        p_mq->wait_and_pop(cmd);
        std::cout << "cmd.cmd :" << cmd.cmd << std::endl;
        std::cout << "cmd.para1 :" << cmd.para1 << std::endl;
        std::cout << "cmd.para2 :" << cmd.para2 << std::endl;
        std::cout << "cmd.para3 :" << cmd.para3 << std::endl;
        std::cout << "cmd.para4 :" << cmd.para4 << std::endl;
        std::cout << "cmd.para5 :" << cmd.para5 << std::endl;
        std::cout << "cmd.para6 :" << cmd.para6 << std::endl;
        
    }
}

void Hardware::run()
{
    hw_thread = std::thread(&Hardware::control, this);
    
}

