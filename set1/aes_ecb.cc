#include "../aes/aes_ecb.h"
#include "../bitops/Padding.h"
#include <openssl/evp.h>
#include <stdexcept>
#include <cmath>
#include <cstring>

using std::string;
using std::vector;
using std::runtime_error;

vector<int> aes_ecb_decrypt(string _key, vector<int> _hex){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    unsigned char* key = (unsigned char*) malloc(sizeof(char)*_key.size());
    if(NULL == key){
        throw runtime_error("ERROR: malloc failed on key.");
    }
    for(size_t i = 0; i < _key.size(); i++){
        key[i] = _key[i];
    }
    
    int inl = sizeof(char)*_hex.size();
    unsigned char* in = (unsigned char*) malloc(inl);
    if(NULL == in){
        throw runtime_error("ERROR: malloc failed on in.");
    }
    for(size_t i = 0; i < _hex.size(); i++){
        in[i] = _hex[i];
    }

    //int outl = inl + EVP_CIPHER_block_size(EVP_aes_128_ecb());
    int outl = inl;
    unsigned char* out = (unsigned char*) malloc(outl);
    unsigned char* current = out;

    if(!EVP_DecryptInit(ctx, EVP_aes_128_ecb(), key, NULL)){
        throw runtime_error("ERROR: EVP_DecryptInit failed.");
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0);
    
    if(!EVP_DecryptUpdate(ctx, out, &outl, in, inl)){
        throw runtime_error("ERROR: EVP_DecryptUpdate failed.");
    }

    current += outl;
    if(!EVP_DecryptFinal(ctx, current, &outl)){
        throw runtime_error("ERROR: EVP_DecryptFinal failed.");
    }

    current += outl;
    out[current-out] = '\0';
    
    vector<int> ret;
    for(int i = 0; i < current-out; i++){
        ret.push_back(out[i]);
    }

    EVP_CIPHER_CTX_free(ctx);
    free(key);
    free(in);
    free(out);

    unpad(ret);
    return ret;
}

vector<int> aes_ecb_encrypt(string _key, vector<int> _hex){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int block = EVP_CIPHER_block_size(EVP_aes_128_ecb());
    
    unsigned char* key = (unsigned char*) malloc(sizeof(char)*_key.size());
    if(NULL == key){
        throw runtime_error("ERROR: malloc failed on key.");
    }
    for(size_t i = 0; i < _key.size(); i++){
        key[i] = _key[i];
    }
    
    pad(_hex, block);
    int inl = sizeof(char)*_hex.size();
    unsigned char* in = (unsigned char*) malloc(inl);
    if(NULL == in){
        throw runtime_error("ERROR: malloc failed on in.");
    }
    for(size_t i = 0; i < _hex.size(); i++){
        in[i] = _hex[i];
    }

    int outl = inl + block;
    unsigned char* out = (unsigned char*) malloc(outl);
    unsigned char* current = out;

    if(!EVP_EncryptInit(ctx, EVP_aes_128_ecb(), key, NULL)){
        throw runtime_error("ERROR: EVP_EncryptInit failed.");
    }

    if(!EVP_EncryptUpdate(ctx, out, &outl, in, inl)){
        throw runtime_error("ERROR: EVP_EncryptUpdate failed.");
    }

    current += outl;
    if(!EVP_EncryptFinal(ctx, current, &outl)){
        throw runtime_error("ERROR: EVP_EnryptFinal failed.");
    }

    EVP_CIPHER_CTX_free(ctx);
    
    vector<int> ret;
    int sz = ceil(inl/block)*block;
    for(int i = 0; i < sz; i++){
        ret.push_back(out[i]);
    }

    free(key);
    free(in);
    free(out);

    return ret;
}

vector<int> aes_ecb_encrypt(vector<int> _key, vector<int> _char){
    string _k;
    _k.append(_key.begin(), _key.end());
    return aes_ecb_encrypt(_k, _char);
}

vector<int> aes_ecb_decrypt(vector<int> _key, vector<int> _char){
    string _k;
    _k.append(_key.begin(), _key.end());
    return aes_ecb_decrypt(_k, _char);
}
