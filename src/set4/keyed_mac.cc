#include "../hash/sha1.h"
#include "../bitops/random.h"
#include <vector>

namespace keyed_mac{
    using std::vector;
    class Server{
        vector<int> key;
        public:
        Server() : key(random(16)){}
        vector<int> hash(const vector<int>& message){
            vector<int> tmp(key);
            tmp.insert(tmp.end(), message.begin(), message.end());
            return sha1(tmp);
        }
    };
}
