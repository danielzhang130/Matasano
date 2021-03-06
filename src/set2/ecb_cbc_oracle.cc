#ifndef ECB_CBC_ORACLE_H
#define ECB_CBC_ORACLE_H
#include "../bitops/random.h"
#include "../bitops/FixedXOR.h"
#include "../aes/aes_cbc.h"
#include "../aes/aes_ecb.h"
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>

namespace ecb_cbc_oracle{
    using std::vector;
    using std::runtime_error;
    using std::to_string;
    using std::cout;
    using std::endl;

    vector<int> ecb_or_cbc_encrypt(vector<int> plaintext){
        vector<int> key = random(16);
        int mode = random(1)[0];
        vector<int> prepend = random(random(1)[0] % 6 + 5);
        vector<int> postpend = random(random(1)[0] % 6 + 5);
        plaintext.insert(plaintext.begin(), prepend.begin(), prepend.end());
        plaintext.insert(plaintext.end(), postpend.begin(), postpend.end());
        vector<int> ciphertext;
        if(mode % 2){ // ecb
            ciphertext = aes_ecb_encrypt(key, plaintext);
        }
        else{ // cbc
            vector<int> iv = random(16);
            ciphertext = aes_cbc_encrypt(key, plaintext, iv);
        }
        return ciphertext;
    }

    void detection_oracle(vector<int> (*f)(vector<int>)){
        vector<int> testString(43, 0);
        vector<int> result = f(testString);
        vector<vector<int>> blocks;
        vector<int> b;
        for(size_t i = 0; i < result.size(); i++){
            if(i != 0 && i%16 == 0){
                blocks.push_back(b);
                b.clear();
                cout << endl;
            }
            b.push_back(result[i]);
            cout << std::hex << (result[i]>>4);
            cout << std::hex << (result[i]&15);
        }
        cout << endl;
        if(blocks[1] == blocks[2]){
            cout << "ECB mode" << endl;
        }
        else{
            cout << "CBC mode" << endl;
        }
    }
}
#endif
