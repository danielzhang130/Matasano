#include "../bitops/random.h"
#include <openssl/rand.h>
#include <stdexcept>
#include <string>

using std::vector;
using std::runtime_error;
using std::to_string;

vector<int> random(int size){
    unsigned char* c = (unsigned char*) malloc(size);
    if(RAND_bytes(c, size) != 1){
        throw runtime_error("ERROR: unable to generate random number of size " + to_string(size));
    }
    vector<int> v;
    for(int i = 0; i < size; i++){
        v.push_back(c[i]);
    }
    return v;
}
