#include "../hash/sha1.h"
#include <stdexcept>
#include <openssl/evp.h>

using std::vector;
using std::runtime_error;

vector<int> sha1(const vector<int>& _message){
    size_t message_len = _message.size();
    auto message = (unsigned char*) malloc(sizeof(unsigned char) * message_len);
    if(NULL == message){
        throw runtime_error("Error with malloc of message.");
    }
    for(size_t i = 0; i < _message.size(); i++){
        message[i] = _message[i];
    }

	EVP_MD_CTX *mdctx;

	if((mdctx = EVP_MD_CTX_create()) == NULL){
        throw runtime_error("Error when creating EVP_MD_CTX");
    }

	if(1 != EVP_DigestInit(mdctx, EVP_sha1())){
        throw runtime_error("Error when initializing SHA1.");
    }

	if(1 != EVP_DigestUpdate(mdctx, message, message_len)){
        throw runtime_error("Error when calculated hash.");
    }

    unsigned int digestl = EVP_MD_size(EVP_sha256());
    auto digest = (unsigned char *) malloc(sizeof(unsigned int) * digestl);
    if(digest == NULL){
        throw runtime_error("Error with malloc of hash.");
    }

	if(1 != EVP_DigestFinal(mdctx, digest, &digestl)){
        throw runtime_error("Error finishing up hash.");
    }

    vector<int> sha1_digest(digest, digest + digestl);
    free(message);
    free(digest);
    return sha1_digest;
}

