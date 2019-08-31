#include "mersenne.cc"
#include "../bitops/random.cc"
#include <thread>

namespace crack_seed{
    class Server{
        Mersenne* m;
        public:
        Server(){ 
            std::this_thread::sleep_for(std::chrono::seconds(random(1)[0] % 60));
            m = new Mersenne(std::chrono::system_clock::now().time_since_epoch().count());
        }
        unsigned int operator()(){
            std::this_thread::sleep_for(std::chrono::seconds(random(1)[0] % 10));
            return (*m)();
        }
        ~Server(){
            delete m;
        }
    };

    void get_seed(){
        Server server;

        auto first = server();
        
    }
}
