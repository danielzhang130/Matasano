#include "../aes/aes_cbc.h"
#include "../bitops/random.h"
#include "../bitops/FixedXOR.h"
#include <vector>
#include <string>
#include <iostream>

namespace cbc_bitflip{
    using std::vector;
    using std::string;
    using std::cout;
    using std::endl;

    class Server{
        vector<int> key;
        public:
        Server() : key(random(16)) {}

        vector<int> encrypt(string s){
            for(size_t i = 0; i < s.size(); i++){
                if(s[i] == ';' || s[i] == '='){
                    s.insert(i++, "\"");
                    s.insert(++i, "\"");
                }
            }
            string temp = "comment1=cooking%20MCs;userdata=";
            s.insert(s.begin(), temp.begin(), temp.end());
            temp = ";comment2=%20like%20a%20pound%20of%20bacon";
            s.insert(s.end(), temp.begin(), temp.end());
            vector<int> plain(s.begin(), s.end());
            return aes_cbc_encrypt(key, plain, key);
        }

        bool check_key(vector<int> _key){
            return _key == key;
        }
    };

    void break_key(){

    }
}
