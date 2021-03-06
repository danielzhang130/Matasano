#include "../aes/aes_ctr.h"
#include "../aes/aes_ecb.h"
#include "../bitops/FixedXOR.h"
#include <algorithm>

using std::vector;
using std::reverse;

vector<int> aes_ctr_encrypt(const vector<int>& key, const vector<int>& plain, vector<int> nonce){
    reverse(nonce.begin(), nonce.end());
    uint64_t _counter = 0;
    vector<int> counter(8,0);
    vector<int> cipher;

    for(auto i = plain.begin(); i < plain.end(); i+=16){
        for(int j = 0; j < 8; j++){
            counter[j] = (_counter >> (j*8)) & 255;
        }
        vector<int> t(nonce.begin(), nonce.end());
        t.insert(t.end(), counter.begin(), counter.end());
        t = aes_ecb_encrypt(key, t);
        vector<int> plainBlock;
        if(i+16 > plain.end()){
            plainBlock = vector<int> (i, plain.end());
        }
        else{
            plainBlock = vector<int> (i, i+16);
        }
        t = vector<int>(t.begin(), t.begin()+plainBlock.size());
        t = fixedXOR(t, plainBlock);
        cipher.insert(cipher.end(), t.begin(), t.end());
        _counter++;
    }
    
    return cipher;
}

