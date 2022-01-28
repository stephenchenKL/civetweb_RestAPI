#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <CivetServer.h>
#include <condition_variable>
#include <thread>
#include <future>

#include "webHandler.h"
#include "threadsafe_queue.h"
#include "command.h"
#include "instrumentCtrl.h"

#define NO_SSL


#ifdef NO_SSL
#define PORT "8089"
#define HOST_INFO "http://localhost:8089"
#else
#define PORT "8089r,8843s"
#define HOST_INFO "https://localhost:8843"
#endif

#define DOCUMENT_ROOT "."
#define EXPERIMENT_URI "/api/exp"
#define EXIT_URI "/api/exit"
#define METHOD_FILES_URI "/api/method-files"
#define METHOD_FILES_DIR "/tmp/"


threadsafe_queue<Command> cmd_q;
threadsafe_queue<ENGN_Info> rslt_q;
std::condition_variable cond_cmd;
std::mutex mtx;

std::promise<ENGN_Info>info_promise;
std::shared_future<ENGN_Info> info_future(info_promise.get_future());







 int main()
 {
    InstrumentCtrl instrumentCtrl(&cmd_q);
    instrumentCtrl.run();
    
    std::thread t_info(&InstrumentCtrl::getInfo, &instrumentCtrl, ref(info_promise) );
    std::cout << info_future.get().bCanAutoGain << std::endl;
    std::cout << info_future.get().bCanAutoGain << std::endl;
    std::cout << info_future.get().bCanAutoGain << std::endl;
    std::cout << info_future.get().bCanAutoGain << std::endl;
    
     

     
    int err = 0;
     
     // Show info
    std::cout << "Experiment Control: " << HOST_INFO << EXPERIMENT_URI << std::endl;
    std::cout << "Method Files: " << HOST_INFO << METHOD_FILES_URI << std::endl;
    std::cout << "Exit Experiment Service: " << HOST_INFO << EXIT_URI << std::endl;

    mg_init_library(0);
	
	const char *options[] = {
	    "document_root", DOCUMENT_ROOT, "listening_ports", PORT, 0};
    
    std::vector<std::string> cpp_options;
    for (int i=0; i<(sizeof(options)/sizeof(options[0])-1); i++) {
        cpp_options.push_back(options[i]);
    }

	CivetServer server(cpp_options); // <-- C++ style start
    
    ExperimentHandler h_experiment;
	server.addHandler(EXPERIMENT_URI, h_experiment);
    

     while (true) {
 		sleep(1);
 	}
	

	
	
	printf("Bye!\n");
	mg_exit_library();

	return 0;
     
 }
