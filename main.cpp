#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <CivetServer.h>

#include "webHandler.h"
//#include "threadsafe_queue.h"

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




#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
template<typename T>
class threadsafe_queue
{
private:
mutable std::mutex mut;
std::queue<T> data_queue;
std::condition_variable data_cond;
public:
threadsafe_queue()
{}
threadsafe_queue(threadsafe_queue const& other)
{
std::lock_guard<std::mutex> lk(other.mut);
data_queue=other.data_queue;
}
void push(T new_value)
{
std::lock_guard<std::mutex> lk(mut);
data_queue.push(new_value);
data_cond.notify_one();
}
void wait_and_pop(T& value)
{
std::unique_lock<std::mutex> lk(mut);
data_cond.wait(lk,[this]{return !data_queue.empty();});
value=data_queue.front();
data_queue.pop();
}
std::shared_ptr<T> wait_and_pop()
{
std::unique_lock<std::mutex> lk(mut);
data_cond.wait(lk,[this]{return !data_queue.empty();});
std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
data_queue.pop();
return res;
}
bool try_pop(T& value)
{
std::lock_guard<std::mutex> lk(mut);
if(data_queue.empty())
return false;
value=data_queue.front();
data_queue.pop();
return true;
}
std::shared_ptr<T> try_pop()
{
std::lock_guard<std::mutex> lk(mut);
if(data_queue.empty())
return std::shared_ptr<T>();
std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
data_queue.pop();
return res;
}
bool empty() const
{
std::lock_guard<std::mutex> lk(mut);
return data_queue.empty();
}
};



 int main()
 {
     
threadsafe_queue<int> message_q;
     
     
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
