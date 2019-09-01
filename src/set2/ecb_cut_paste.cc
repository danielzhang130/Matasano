#include "../aes/aes_ecb.h"
#include "../bitops/random.h"
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace ecb_cut_and_paste{
    using std::string;
    using std::map;
    using std::vector;
    using std::runtime_error;
    using std::istringstream;
    using std::cout;
    using std::endl;

    vector<string> split(const string& s, char delimiter){
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)){
            tokens.push_back(token);
        }
        return tokens;
    }

    map<string, string> parse(string s){
        map<string, string> result;
        vector<string> block = split(s, '&');
        for(auto i:block){
            vector<string> temp = split(i, '=');
            if(temp.size() != 2){
                throw runtime_error("ERROR: wrong format " + i);
            }
            result[temp[0]] = temp[1];
        }
        return result;
    }

    vector<int> key;

    vector<int> profile_for(string email){
        if(!key.size()){
            key = random(16);
        }
        for(string::iterator i = email.begin(); i < email.end(); i++){
            if(*i == '&' || *i == '='){
                email.erase(i);
            }
        }

        string _txt = "email=" + email + "&uid=10&role=user";
        vector<int> txt;
        for(auto i:_txt){
            txt.push_back(i);
        }
        return aes_ecb_encrypt(key, txt);
    }

    void read_profile(vector<int> cipher){
        vector<int> decrypt = aes_ecb_decrypt(key, cipher);
        string txt;
        for(auto i:decrypt){
            txt.push_back((char)i);
        }
        map<string, string> parsed = parse(txt);
        for(auto i = parsed.begin(); i != parsed.end(); i++){
            cout << i->first << " " << i->second << endl;
        }
    }

    vector<int> make_admin(){
        vector<int> base = profile_for("test@test.com");
        string special = "foo@bar.coadmin";
        for(int i = 0; i < 11; i++){
            special.push_back(11);
        }
        vector<int> admin = profile_for(special);
        for(int i = 0; i < 16; i++){
            base.pop_back();
        }
        for(int i = 0; i < 16; i++){
            base.push_back(admin[i+16]);
        }
        return base;
    }
}
