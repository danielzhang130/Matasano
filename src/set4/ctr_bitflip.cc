#include "../aes/aes_ctr.h"
#include "../bitops/random.h"
#include "../bitops/FixedXOR.h"
#include <vector>
#include <string>

namespace ctr_bitflip{
    using std::vector;
    using std::string;

    class Server{
        vector<int> key;

        public:
        vector<int> iv;

        Server() : key(random(16)), iv(16, 0) {}

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
            return aes_ctr_encrypt(key, plain, iv);
        }

        bool isAdmin(vector<int> cipher){
            vector<int> _plain = aes_ctr_decrypt(key, cipher, iv);
            string admin = ";admin=true;";
            string plain(_plain.begin(), _plain.end());
            return plain.find(admin) != string::npos;
        }
    };

    bool bitflip(){
        Server server;
        string _plain("aaaaaaaaaaaa");
        vector<int> cipher(server.encrypt(_plain));
        string _target(";admin=true;");
        vector<int> target(_target.begin(), _target.end());
        vector<int> key(fixedXOR(vector<int>(_plain.begin(), _plain.end()), vector<int>(cipher.begin() + 32, cipher.begin() + 48)));
        vector<int> new_cipher(fixedXOR(key, target));
        cipher.erase(cipher.begin() + 32, cipher.begin() + 48);
        cipher.insert(cipher.begin() + 32, new_cipher.begin(), new_cipher.end());
        return server.isAdmin(cipher);
    }
}
