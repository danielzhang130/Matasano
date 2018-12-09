#include <openssl/evp.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

using std::string;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::runtime_error;

vector<int> aes_ecb_decrypt(string _key, vector<int> _hex){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    
    unsigned char* key = (unsigned char*) malloc(sizeof(char)*_key.size()+1);
    if(NULL == key){
        throw runtime_error("ERROR: malloc failed on key.");
    }
    for(size_t i = 0; i < _key.size(); i++){
        key[i] = _key[i];
    }
    key[_key.size()] = '\0';
    
    int inl = sizeof(char)*_hex.size();
    unsigned char* in = (unsigned char*) malloc(inl+1);
    if(NULL == in){
        throw runtime_error("ERROR: malloc failed on in.");
    }
    for(size_t i = 0; i < _hex.size(); i++){
        in[i] = _hex[i];
    }
    in[_hex.size()] = '\0';

    int outl = inl + EVP_CIPHER_block_size(EVP_aes_128_ecb());
    unsigned char* out = (unsigned char*) malloc(outl);
    unsigned char* current = out;

    if(!EVP_DecryptInit(ctx, EVP_aes_128_ecb(), key, NULL)){
        throw runtime_error("ERROR: EVP_DecryptInit failed.");
    }

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
    for(int i = 0; out[i] != '\0'; i++){
        ret.push_back(out[i]);
    }

    EVP_CIPHER_CTX_free(ctx);
    free(key);
    free(in);
    free(out);

    return ret;
}

vector<int> aes_ecb_encrypt(string _key, vector<int> _hex){
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    
    unsigned char* key = (unsigned char*) malloc(sizeof(char)*_key.size()+1);
    if(NULL == key){
        throw runtime_error("ERROR: malloc failed on key.");
    }
    for(size_t i = 0; i < _key.size(); i++){
        key[i] = _key[i];
    }
    key[_key.size()] = '\0';
    
    int inl = sizeof(char)*_hex.size();
    unsigned char* in = (unsigned char*) malloc(inl+1);
    if(NULL == in){
        throw runtime_error("ERROR: malloc failed on in.");
    }
    for(size_t i = 0; i < _hex.size(); i++){
        in[i] = _hex[i];
    }
    in[_hex.size()] = '\0';

    int outl = inl + EVP_CIPHER_block_size(EVP_aes_128_ecb());
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

    current += outl;
    out[current-out] = '\0';
    
    vector<int> ret;
    for(int i = 0; out[i] != '\0'; i++){
        ret.push_back(out[i]);
    }

    EVP_CIPHER_CTX_free(ctx);
    free(key);
    free(in);
    free(out);

    return ret;
}
