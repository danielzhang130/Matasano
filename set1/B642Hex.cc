#ifndef B64_2_HEX_H
#define B64_2_HEX_H
#include <map>
#include <vector>
#include <stdexcept>

using std::vector;
using std::string;
using std::map;
using std::logic_error;
using std::to_string;

typedef int outputFormat;

vector<int> _b2hex(string b64, outputFormat of){
    map<int, int> b64Table;
    for(int i = 0; i < 26; i++){
        b64Table[65+i] = i;
    }
    for(int i = 0; i < 26; i++){
        b64Table[97+i] = i+26;
    }
    for(int i = 0; i < 10; i++){
        b64Table[48+i] = i+52;
    }
    b64Table['+'] = 62;
    b64Table['/'] = 63;
    b64Table['='] = 0;
    int sum = 0;
    for(size_t i = 0; i < b64.size(); i++){
        sum = sum << 6;
        sum += b64Table[b64[i]];
    }
    vector<int> r;
    int end = -1;
    if('=' == b64[2]){
        end = 15;
    }
    else if('=' == b64[3]){
        end = 7;
    }

    if(1 == of){ // vector of bits
        for(int i = 23; i > end; i--){
            r.push_back((sum>>i) & 1);
        }
    }
    else if(4 == of){ // vector of hex
        for(int i = 20; i > end; i-=4){
            r.push_back((sum>>i) & 15);
        }
    }
    else if(8 == of){ // vector of bytes
        for(int i = 16; i > end; i-=8){
            r.push_back((sum>>i) & 255);
        }
    }
    else{
        throw logic_error("ERROR: output format " + to_string(of) + " not valid.");
    }
    return r;
}

vector<int> b64toHex(string b64, outputFormat of){
    vector<int> hex;
    for(size_t i = 0; i < b64.size(); i+=4){
        vector<int> temp = _b2hex(b64.substr(i,4), of);
        hex.insert(hex.end(), temp.begin(), temp.end());
    }
    return hex;
}

#endif
