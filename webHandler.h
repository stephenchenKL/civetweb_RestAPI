#pragma once

#include "CivetServer.h"
#include "threadsafe_queue.h"

#define MAX_PARAMETERS 16

class ExperimentHandler : public CivetHandler{
public:
    
    bool handleGet(CivetServer *server, struct mg_connection *conn);
    bool handlePost(CivetServer *server, struct mg_connection *conn);
    bool handlePut(CivetServer *server, struct mg_connection *conn);
    
};
