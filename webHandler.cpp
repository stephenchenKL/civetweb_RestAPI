
#include <string>
#include <iostream>
#include <condition_variable>
#include <future>
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;

#include "../cJSON/cJSON.h"

#include "webHandler.h"




std::string str_exit ("exit");
std::string str_scan ("scan");
std::string str_stop ("stop");
std::string str_snap ("snap");
std::string str_saveRef ("saveRef");
std::string str_saveDark ("saveDark");
std::string str_autoGain ("autoGain");
std::string str_lampOn ("lampOn");
std::string str_lampOff ("lampOff");
std::string str_park ("park");
std::string str_homeXYZ ("homeXYZ");
std::string str_eject ("eject");
std::string str_pickSensor ("pickSensor");
std::string str_sample ("sample");
std::string str_shakerOn ("shakerOn");
std::string str_shakerOff ("shakerOff");
std::string str_shaker ("shaker_");
std::string str_setSampleTemp ("setSampleTemp");
std::string str_setSpectTemp ("setSpectTemp");




static int
SendJSON(struct mg_connection *conn, cJSON *json_obj)
{
	char *json_str = cJSON_PrintUnformatted(json_obj);
	size_t json_str_len = strlen(json_str);

	/* Send HTTP message header */
	mg_send_http_ok(conn, "application/json; charset=utf-8", json_str_len);

	/* Send HTTP message content */
	mg_write(conn, json_str, json_str_len);

	/* Free string allocated by cJSON_Print* */
	cJSON_free(json_str);

	return (int)json_str_len;
}



bool ExitHandler::handleGet(CivetServer *server, struct mg_connection *conn)
{
    Command cmd;
    cmd.cmd = str_exit;
    pCq->push_all(cmd);
    return true;
}
bool ExitHandler::handlePost(CivetServer *server, struct mg_connection *conn)
{
    return handleGet(server, conn);
}
bool ExitHandler::handlePut(CivetServer *server, struct mg_connection *conn)
{
    return handleGet(server, conn);
}

bool ExperimentHandler::handleGet(CivetServer *server, struct mg_connection *conn)
{

    const struct mg_request_info *req_info = mg_get_request_info(conn);
    long long tlen = req_info->content_length;
    

    char delim[] = "&";
    char query_string[2048];
    
    if (req_info->query_string != NULL )
    {
        strcpy(query_string, req_info->query_string);
        std::cout << "query_string: " << query_string << std::endl;
    }
    
    char *ptr = strtok(query_string, delim);
    char *pvs[MAX_PARAMETERS] = { 0 };
    int i = 0;
    while (ptr != NULL){
        pvs[i++] = ptr;
        ptr = strtok(NULL, delim);
    }
    for (i = 0; i < MAX_PARAMETERS; ++i) {
        if (pvs[i] != NULL) {
            char delim2[] = "=";
            char *pp = strtok(pvs[i], delim2);
            if (pp != NULL) {
                
                // curl -i http://localhost:8089/api/exp?info -X GET

                std::string str_info ("info");
                std::string var1 = (std::string) pp;
                std::cout << "var1 :" << var1 << std::endl;
                if (0 == str_info.compare(var1)){
                    std::cout << "var1 == info." << std::endl;
                    pp = strtok(NULL, delim2);
                    Command cmd;
                    cmd.cmd = var1;
                    //cmd_q.push(cmd);
                    pCq->push(cmd);
                    ENGN_Info info;
                    //rslt_q.wait_and_pop(info);
                    pRq->wait_and_pop(info);
                    std::cout << "info.bCanAutoGain=" << info.bCanAutoGain << std::endl
                    << "info.bHasDark=" << info.bHasDark << std::endl
                    << "info.bHasRef=" << info.bHasRef << std::endl
                    << "info.bHasVariableSpeed=" << info.bHasVariableSpeed << std::endl
                    << "info.bMapOK=" << info.bMapOK << std::endl;
                }
            }
        }
    }
                        
        
    

    json j;
    // add a number that is stored as double (note the implicit conversion of j to an object)
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;

// add a string that is stored as std::string
j["name"] = "Niels";

// add another null object by passing nullptr
j["nothing"] = nullptr;

// add an object inside the object
j["answer"]["everything"] = 42;

// add an array that is stored as std::vector (using an initializer list)
j["list"] = { 1, 0, 2 };

// add another object (using an initializer list of pairs)
j["object"] = { {"currency", "USD"}, {"value", 42.99} };

	// Send HTTP message header //
	mg_send_http_ok(conn, "application/json; charset=utf-8", j.size());
    
    const void * temp = &j;
    std::cout << "j.size() = " << j.size() << std::endl;

	// Send HTTP message content //
	mg_write(conn, temp, j.size());
    
     
    return true;
}
	
bool ExperimentHandler::handlePost(CivetServer *server, struct mg_connection *conn)
{


    return false;
}

    #define fopen_recursive fopen
    

bool ExperimentHandler::handlePut(CivetServer *server, struct mg_connection *conn)
{
    Command cmd;
    // Handler may access the request info using mg_get_request_info 
    int status = 503;
    
    
    const struct mg_request_info *req_info = mg_get_request_info(conn);
    long long tlen = req_info->content_length;
    
    char delim[] = "&";
    char query_string[2048];
    strcpy(query_string, req_info->query_string);
    char *ptr = strtok(query_string, delim);
    char *pvs[MAX_PARAMETERS] = { 0 };
    int i = 0;
    std::cout << "query_string: " << query_string << std::endl;
    while (ptr != NULL){
        pvs[i++] = ptr;
        ptr = strtok(NULL, delim);
    }
        
    for (i = 0; i < MAX_PARAMETERS; ++i) {
        if (pvs[i] != NULL) {
            char delim2[] = "=";
            char *pp = strtok(pvs[i], delim2);
            if (pp != NULL) {
                
                std::string str_cmd ("command");
                std::string var1 = (std::string) pp;
                
                if (0 == str_cmd.compare(var1)){
                    pp = strtok(NULL, delim2);
                    

                    
                    var1 = (std::string) pp;
                    std::cout << "var1: " << var1 << std::endl;
                    
                    for ( const auto t : AllCmdTypes )
                    {
                        if (0 == var1.find(cmdTypeToStr(t)))
                            std::cout << t;
                        
                    }
                    
                    
                    if (0 == str_eject.compare(var1)){
                        cmd.cmd = var1;
                        //cmd_q.push(cmd);
                        pCq->push(cmd);

                    }
                    else if (0 == var1.find(str_pickSensor)){ 
                        std::string delimiter = "_";
                        std::string row;
                        std::string col;
                            
                        size_t pos = 0;
                        if( (pos = var1.find(delimiter)) != std::string::npos) 
                        {
                            var1.erase(0, pos + delimiter.length());
                        }
                        if( (pos = var1.find(delimiter)) != std::string::npos) 
                        {
                            row = var1.substr(0, pos);
                            var1.erase(0, pos + delimiter.length());
                            col = var1;
                        }
                        std::cout << "pick sensor " + row + " " + col << std::endl;
                        //cmd = pickSensor;
                        cmd.cmd = str_pickSensor;
                        cmd.para1 = row[0]-'A';
                        cmd.para2 = std::stoi(col);
                        //cmd_q.push(cmd);
                        pCq->push(cmd);
                        status = 200;
                    }
                    else if (0 == var1.find(str_shaker)){ 
                        std::string delimiter = "_";
                        int shakerId = 0;
                        int shakerMode = 0;
                        int shakeRpm = 0;
                            
                        size_t pos = 0;
                        if( (pos = var1.find(delimiter)) != std::string::npos) 
                        {
                            var1.erase(0, pos + delimiter.length());
                        }
                        if( (pos = var1.find(delimiter)) != std::string::npos) 
                        {
                            shakerId = std::stoi(var1.substr(0, pos));
                            var1.erase(0, pos + delimiter.length());
                            shakerMode = std::stoi(var1.substr(0, pos));
                            var1.erase(0, pos + delimiter.length());
                            shakeRpm = std::stoi(var1);
                        }
                        std::cout << "shape mode: id = " << shakerId << ", mode = " << shakerMode << ", rpm = " << shakeRpm << std::endl;
                        cmd.cmd = str_shaker;
                        cmd.para1 = shakerId;
                        cmd.para2 = shakerMode;
                        cmd.para3 = shakeRpm;
                        //cmd_q.push(cmd);
                        pCq->push(cmd);
                            
                        status = 200;
                    }
                }
                else{ // unrecognized parameter
                    break;
                }
            }
        }
        else{ // no more parameters
            break;
        }
    }

    
        
    
        
        
        
    
    
        json j;
    // add a number that is stored as double (note the implicit conversion of j to an object)
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;

// add a string that is stored as std::string
j["name"] = "Niels";

// add another null object by passing nullptr
j["nothing"] = nullptr;

// add an object inside the object
j["answer"]["everything"] = 42;

// add an array that is stored as std::vector (using an initializer list)
j["list"] = { 1, 0, 2 };

// add another object (using an initializer list of pairs)
j["object"] = { {"currency", "USD"}, {"value", 42.99} };

	// Send HTTP message header //
	mg_send_http_ok(conn, "application/json; charset=utf-8", j.size());
    
    const void * temp = &j;
    std::cout << "j.size() = " << j.size() << std::endl;

	// Send HTTP message content //
	mg_write(conn, temp, j.size());
    
     
    return status;


    

    return status;
        
}

