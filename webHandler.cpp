
#include <string>
#include <iostream>
#include <condition_variable>
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;

#include "../cJSON/cJSON.h"

#include "webHandler.h"



extern threadsafe_queue<std::string> message_q;
extern threadsafe_queue<std::string> message_q2;
extern std::condition_variable cond_cmd;
extern std::mutex mtx;


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



bool ExperimentHandler::handleGet(CivetServer *server, struct mg_connection *conn)
{

    json j;
    // add a number that is stored as double (note the implicit conversion of j to an object)
    j["exp_status"] = 100;

    const auto s = j.dump();

    std::cout << s << std::endl;

    char* c = const_cast<char*>(s.c_str());
    mg_send_http_ok(conn, "application/json; charset=utf-8", s.size());

	/* Send HTTP message content */
    mg_write(conn, c, s.size());

//    cJSON *obj_return = cJSON_CreateObject();
//    cJSON_AddNumberToObject(obj_return, "exp_status", 100);
//    char *json_str = cJSON_PrintUnformatted(obj_return);
//    size_t json_str_len = strlen(json_str);
//    mg_write(conn, json_str, json_str_len);

    return true;
}
	
bool ExperimentHandler::handlePost(CivetServer *server, struct mg_connection *conn)
{
// 		cJSON *obj_return = cJSON_CreateObject();
//         if (!obj_return) {
//             /* insufficient memory? */
//             mg_send_http_error(conn, 500, "Server error");
//             return 500;
//         }
//         cJSON_AddStringToObject(obj_return, "info", "api/exp POST Not supported");
//         SendJSON(conn, obj_return);
//         cJSON_Delete(obj_return);

    return false;
}

    #define fopen_recursive fopen
    

bool ExperimentHandler::handlePut(CivetServer *server, struct mg_connection *conn)
{
    
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
                    
                    std::string str_eject ("eject");
                    std::string str_pickSensor ("pickSensor");
                    std::string str_shaker ("shaker_");
                    std::string str_setSampleTemp ("setSampleTemp");
                    
                    var1 = (std::string) pp;
                    std::cout << "var1: " << var1 << std::endl;
                    
                    if (0 == str_eject.compare(var1)){
                        
                        message_q2.push(var1);
                            
                        std::lock_guard<std::mutex> lk(mtx);
                        message_q.push(var1);
                        cond_cmd.notify_all();   
                        std::cout << "message_q.push(var1); " << std::endl;
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


        
//  cJSON *obj_return = cJSON_CreateObject();
//         
//     const struct mg_request_info *req_info = mg_get_request_info(conn);
//     long long tlen = req_info->content_length;
//     std::cout << "req_info->query_string: " << req_info->query_string << std::endl;
//     std::string s(req_info->query_string);
//     std::string delimiter = "=";
//     size_t pos = 0;
//     std::string token;
//     while ((pos = s.find(delimiter)) != std::string::npos) {
//         token = s.substr(0, pos);
//         std::cout << token << std::endl;
//         s.erase(0, pos + delimiter.length());
//     }
//     std::cout << s << std::endl;
// 
//     
//         char delim[] = "&";
//         char query_string[2048];
//         strcpy(query_string, req_info->query_string);
//         char *ptr = strtok(query_string, delim);
//         char *pvs[MAX_PARAMETERS] = { 0 };
//         int i = 0;
//         while (ptr != NULL){
//             pvs[i++] = ptr;
//             ptr = strtok(NULL, delim);
//         }
// 
//         for (i = 0; i < MAX_PARAMETERS; ++i) {
//             if (pvs[i] != NULL) {
//                 char delim2[] = "=";
//                 char *pp = strtok(pvs[i], delim2);
//                 if (pp != NULL) {
//                     
//                     std::string str_cmd ("command");
//                     std::string var1 = (std::string) pp;
//                     
//                     if (0 == str_cmd.compare(var1)){
//                         pp = strtok(NULL, delim2);
//                         
//                         std::string str_scan ("scan");
//                         std::string str_stop ("stop");
//                         std::string str_snap ("snap");
//                         var1 = (std::string) pp;
//                         
//                         if (0 == str_scan.compare(var1)){
//                             mqtt.publish("command", var1);
//                             exp_status = 1;
//                             cJSON_AddStringToObject(obj_return, "ack", "received scan command");
//                             cJSON_AddNumberToObject(obj_return, "exp_status", exp_status);
//                             status = 200;
//                         }
//                         else if (0 == str_stop.compare(var1)){
//                             mqtt.publish("command", var1);
//                             exp_status = 0;
//                             cJSON_AddStringToObject(obj_return, "ack", "received stop command");
//                             cJSON_AddNumberToObject(obj_return, "exp_status", exp_status);
//                             status = 200;
//                         }
//                         else if (0 == str_snap.compare(var1)){
//                             mqtt.publish("command", var1);
//                             cJSON_AddStringToObject(obj_return, "ack", "received snap command");
//                             cJSON_AddNumberToObject(obj_return, "exp_status", exp_status);
//                             status = 200;
//                         }
//                         else{
//                             mqtt.publish("command", var1);
//                             cJSON_AddStringToObject(obj_return, "ack", "received unrecognized Experiment command");
//                             cJSON_AddNumberToObject(obj_return, "exp_status", exp_status);
//                             pp = strtok(NULL, delim2);
//                             status =  400;
//                             break;
//                         }
//                         std::cout << "exp_status = " << exp_status << '\n';
//                     }
//                     else{ // unrecognized parameter
//                         cJSON_AddStringToObject(obj_return, "ack", "received unrecognized parameter");
//                         cJSON_AddNumberToObject(obj_return, "exp_status", exp_status);
//                         pp = strtok(NULL, delim2);
//                         status =  400;
//                         break;
//                     }
//                 }
//             }
//             else{ // no more parameters
//                 break;
//             }
//         }
// 	
//         SendJSON(conn, obj_return);
//         cJSON_Delete(obj_return);

    return status;
        
}

