#include "../aes/aes_cbc.h"
#include "../bitops/random.h"
#include "../bitops/FixedXOR.h"
#include <vector>
#include <string>
#include <iostream>

namespace cbc_iv_key{
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

        void verify(vector<int> cipher){
            vector<int> plain(aes_cbc_decrypt(key, cipher, key));
            for(int c : plain){
                if(c < 0 || c > 127){
                    throw plain;
                }
            }
        }
    };

    bool break_key(){
        Server server;
        vector<int> cipher(server.encrypt(""));
        vector<int> first_block(cipher.begin(), cipher.begin() + 16);
        for(int i = 0; i < 128; ++i){
            cipher.erase(cipher.begin() + 16, cipher.begin() + 64);
            vector<int> bad_block(16, i);
            cipher.insert(cipher.begin() + 16, bad_block.begin(), bad_block.end());
            cipher.insert(cipher.begin() + 32, first_block.begin(), first_block.end());
            try{
                server.verify(cipher);
            }
            catch(vector<int>& plain){
                vector<int> plain_1(plain.begin(), plain.begin() + 16);
                vector<int> plain_3(plain.begin() + 32, plain.begin() + 48);
                vector<int> key(fixedXOR(plain_1, plain_3));
                return server.check_key(key);
            }
        }
        return false;
    }
}
