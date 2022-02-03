#pragma once

#include "CivetServer.h"
#include "threadsafe_queue.h"
#include "command.h"

#define MAX_PARAMETERS 16

class ExperimentHandler : public CivetHandler{
private:
    threadsafe_queue<Command>* pCq;    
    threadsafe_queue<ENGN_Info>* pRq;
    
public:
    void setCmd_q(threadsafe_queue<Command>* p_cmd_q){pCq = p_cmd_q;};
    void setRslt_q(threadsafe_queue<ENGN_Info>* p_rslt_q){pRq = p_rslt_q;};
    
    bool handleGet(CivetServer *server, struct mg_connection *conn);
    bool handlePost(CivetServer *server, struct mg_connection *conn);
    bool handlePut(CivetServer *server, struct mg_connection *conn);
    
};


class ExitHandler : public CivetHandler{
private:
    threadsafe_queue<Command>* pCq;  
    
public:
    void setCmd_q(threadsafe_queue<Command>* p_cmd_q){pCq = p_cmd_q;};
    
    bool handleGet(CivetServer *server, struct mg_connection *conn);
    bool handlePost(CivetServer *server, struct mg_connection *conn);
    bool handlePut(CivetServer *server, struct mg_connection *conn);
    
};
