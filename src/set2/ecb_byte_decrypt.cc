#ifndef ECB_BYTE_DECRYPT_H
#define ECB_BYTE_DECRYPT_H
#include "../bitops/B642Hex.h"
#include "../bitops/random.h"
#include "../bitops/Padding.h"
#include "../aes/aes_ecb.h"
#include <vector>
#include <stdexcept>
#include <map>
#include <string>
#include <iostream>

namespace ecb_byte_decrypt{
    using std::vector;
    using std::runtime_error;
    using std::map;
    using std::to_string;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::string;

    vector<int> key;

    vector<int> ecb_oracle(vector<int> plaintext){
        string _secret = "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK";
        vector<int> secret = b64toHex(_secret, 8);
        plaintext.insert(plaintext.end(), secret.begin(), secret.end());
        if(key.empty()){
            key = random(16);
        }
        return aes_ecb_encrypt(key, plaintext);
    }

    size_t blocksize(vector<int> (*f)(vector<int>)){
        size_t length;
        vector<int> plaintext = {0};
        length = f(plaintext).size();
        while(length == f(plaintext).size()){
            plaintext.push_back(0);
        }
        return f(plaintext).size() - length;
    }

    bool isECB(vector<int> (*f)(vector<int>)){
        vector<int> plaintext(32, 0);
        vector<int> ciphertext = f(plaintext);
        vector<vector<int>> blocks;
        vector<int> t;
        for(size_t i = 0; i < ciphertext.size(); i++){
            if(i != 0 && i%16==0){
                blocks.push_back(t);
                t = vector<int>();
                //cout << endl;
            }
            t.push_back(ciphertext[i]);
            //cout << std::hex << (ciphertext[i]>>4);
            //cout << std::hex << (ciphertext[i]&15);
        }
        //cout << endl;
        if(blocks[0] == blocks[1]){
            return true;
        }
        return false;
    }

    void decrypt(vector<int> (*f)(vector<int>)){
        size_t bs = blocksize(f);
        if(!isECB(f)){
            throw runtime_error("ERROR: not ECB");
        }
        
        size_t length = f(vector<int>()).size()/bs;
        
        vector<int> result;
        for(size_t m = 0; m < length; m++){
            vector<int> plaintext(bs-1 ,0);
            for(size_t i = 0; i < bs; i++){
                vector<int> ciphertext = f(plaintext);
                map<vector<int>, int> lastByte;    
                for(int i = 0; i < 256; i++){
                    vector<int> test;
                    test.insert(test.end(), plaintext.begin(), plaintext.end());
                    test.insert(test.end(), result.begin(), result.end());
                    test = vector<int>(test.end()-15, test.end());
                    test.push_back(i);
                    if(test.size() != bs){
                        throw runtime_error("ERROR: test block size " + to_string(test.size()));
                    }
                    vector<int> block = f(test);
                    block = vector<int>(block.begin(), block.begin()+16);
                    // for(auto j:block){
                    //     cerr << std::hex << (j>>4) << (j&15);
                    // }
                    // cerr << std::dec << " " << i << endl;
                    lastByte[block] = i;
                }
                char c = lastByte.at(vector<int>(ciphertext.begin() + m * 16, ciphertext.begin()+ (m+1) * 16));
                result.push_back(c);
                if(isValidPadding(result)){
                    cout << "Valid padding encountered. Stopping." << endl;
                    break;
                }
                cout << c << std::flush;
                plaintext.pop_back();
            }
            
        }
        cout << endl;
    }
}
#endif
