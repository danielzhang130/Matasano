#include "../aes/aes_cbc.h"
#include "../aes/aes_ecb.h"
#include "../bitops/FixedXOR.h"
#include "../bitops/Padding.h"
#include <vector>
#include <stdexcept>

using std::runtime_error;
using std::vector;
using std::string;

vector<int> aes_cbc_encrypt(const string& _key, const vector<int>& _char, const vector<int>& _iv){
    vector<int> out;
    vector<vector<int>> blocks;
    for(size_t i = 0; i < _char.size(); i+=16){
        auto end = (_char.end() > _char.begin() +i +16) ? _char.begin()+i+16 : _char.end();
        vector<int> t(_char.begin()+i, end);
        pad(t, 16);
        blocks.push_back(t);
    }
    
    if(16 != _iv.size()){
        throw runtime_error("Initialization vector has incorrect size.");
    }

    for(size_t i = 0; i < blocks.size(); i++){
        if(0 == i){
            blocks[i] = fixedXOR(_iv, blocks[i]);
        }
        else{
            blocks[i] = fixedXOR(blocks[i-1], blocks[i]);
        }
        blocks[i] = aes_ecb_encrypt(_key, blocks[i]);
    }

    for(size_t i = 0; i < blocks.size(); i++){
        out.insert(out.end(), blocks[i].begin(), blocks[i].end());
    }
    return out;
}

vector<int> aes_cbc_decrypt(const string& _key, const vector<int>& _char, const vector<int>& _iv){
    vector<int> out;
    vector<vector<int>> blocks;
    for(size_t i = 0; i < _char.size(); i+=16){
        vector<int> t(_char.begin()+i, _char.begin()+i+16);
        blocks.push_back(t);
    }

    if(16 != _iv.size()){
        throw runtime_error("Initialization vector has incorrect size.");
    }

    vector<int> prev;
    for(size_t i = 0; i < blocks.size(); i++){
        vector<int> temp = blocks[i];
        blocks[i] = aes_ecb_decrypt(_key, blocks[i]);
        pad(blocks[i], 16);

        if(0 == i){
            blocks[i] = fixedXOR(_iv, blocks[i]);
        }
        else{
            blocks[i] = fixedXOR(prev, blocks[i]);
        }
        prev = temp;
    }
    
    for(size_t i = 0; i < blocks.size(); i++){
        out.insert(out.end(), blocks[i].begin(), blocks[i].end());
    }
    unpad(out);
    return out;
}

vector<int> aes_cbc_encrypt(const vector<int>& _key, const vector<int>& _char, const vector<int>& _iv){
    string _k;
    _k.append(_key.begin(), _key.end());
    return aes_cbc_encrypt(_k, _char, _iv);
}

vector<int> aes_cbc_decrypt(const vector<int>& _key, const vector<int>& _char, const vector<int>& _iv){
    string _k;
    _k.append(_key.begin(), _key.end());
    return aes_cbc_decrypt(_k, _char, _iv);
}
