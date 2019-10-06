#include "../hash/sha1.h"
#include "../bitops/random.h"
#include <vector>
#include <string>
#include <cassert>

namespace keyed_mac{
    using std::vector;
    using std::string;

    class Server{
        vector<int> key;
        public:
        Server() : key(random(16)){}
        vector<int> hash(const vector<int>& message){
            vector<int> tmp(key);
            tmp.insert(tmp.end(), message.begin(), message.end());
            return sha1(tmp);
        }
        bool verify(const vector<int>& message, const vector<int>& digest){
            return hash(message) == digest;
        }
        bool is_admin(const vector<int>& message){
            string admin = ";admin=true;";
            string text(message.begin(), message.end());
            return text.find(admin) != string::npos;
        }
    };

    vector<int> md_padding(const vector<int>& message){
        vector<int> padded(message);
        padded.push_back(128);
        while((padded.size() + 16 /* account for the key length */) % 64 != 56){
            padded.push_back(0);
        }
        uint64_t ml = message.size() + 16 /* account for the key length */;
        ml *= 8;
        for(int i = 7; i >= 0; --i){
            padded.push_back(ml >> (i * 8) & 255);
        }
        return padded;
    }

    bool length_extension(){
        string _input("comment1=cooking%20MCs;userdata=foo;comment2=%20like%20a%20pound%20of%20bacon");
        vector<int> input(_input.begin(), _input.end());
        Server server;
        auto hash = server.hash(input);
        uint32_t state[5];
        assert(hash.size() == 20);
        for(size_t i = 0; i < 20; ++i){
            if(i % 4 == 0){
                state[i / 4] = hash[i];
            }
            else{
                state[i / 4] <<= 8;
                state[i / 4] += hash[i];
            }
        }
        auto final_message = md_padding(input);
        string _extend(";admin=true;");
        vector<int> extend(_extend.begin(), _extend.end());
        auto length_extended = sha1(extend, state, final_message.size() + 16);
        final_message.insert(final_message.end(), extend.begin(), extend.end());
        return server.verify(final_message, length_extended) && server.is_admin(final_message);
    }
}
