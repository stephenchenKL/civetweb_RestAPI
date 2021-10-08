#pragma once

#include "CivetServer.h"

class ExperimentHandler : public CivetHandler{
public:
    bool handleGet(CivetServer *server, struct mg_connection *conn);
    bool handlePost(CivetServer *server, struct mg_connection *conn);
    bool handlePut(CivetServer *server, struct mg_connection *conn);
    
};
