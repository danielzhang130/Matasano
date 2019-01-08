#include "../aes/aes_cbc.cc"
#include "../bitops/B642Hex.cc"
#include "../bitops/random.cc"
#include <vector>
#include <stdexcept>

using std::vector;
using std::runtime_error;

class Server{

    private:
    static vector<int> key;
    static vector<int> choice;
    Server(){}

    public:
    static vector<int> cbc_oracle(){
        vector<vector<int>> choices;
        string s = "MDAwMDAwTm93IHRoYXQgdGhlIHBhcnR5IGlzIGp1bXBpbmc=";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDAxV2l0aCB0aGUgYmFzcyBraWNrZWQgaW4gYW5kIHRoZSBWZWdhJ3MgYXJlIHB1bXBpbic=";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDAyUXVpY2sgdG8gdGhlIHBvaW50LCB0byB0aGUgcG9pbnQsIG5vIGZha2luZw==";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDAzQ29va2luZyBNQydzIGxpa2UgYSBwb3VuZCBvZiBiYWNvbg==";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDA0QnVybmluZyAnZW0sIGlmIHlvdSBhaW4ndCBxdWljayBhbmQgbmltYmxl";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDA1SSBnbyBjcmF6eSB3aGVuIEkgaGVhciBhIGN5bWJhbA==";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDA2QW5kIGEgaGlnaCBoYXQgd2l0aCBhIHNvdXBlZCB1cCB0ZW1wbw==";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDA3SSdtIG9uIGEgcm9sbCwgaXQncyB0aW1lIHRvIGdvIHNvbG8=";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDA4b2xsaW4nIGluIG15IGZpdmUgcG9pbnQgb2g=";
        choices.push_back(b64toHex(s, 8));
        s = "MDAwMDA5aXRoIG15IHJhZy10b3AgZG93biBzbyBteSBoYWlyIGNhbiBibG93";
        choices.push_back(b64toHex(s, 8));
        
        if(key.empty()){
            key = random(16);
        }
        
        if(choice.empty()){
            choice = choices[random(1)[0] % choices.size()];
        }
        
        if(iv.empty()){
            iv = vector<int>(16, 0);
        }

        return aes_cbc_encrypt(key, choice, iv);
    }

    static bool padding_validation_oracle(vector<int> cipher){
        vector<int> plain = aes_cbc_decrypt(key, cipher, iv);
        return cipher.size() != plain.size();
    }

    static vector<int> iv;
};

vector<int> Server::iv = vector<int>();
vector<int> Server::key = vector<int>();
vector<int> Server::choice = vector<int>();

void decrypt(){
    vector<int> secret = Server::cbc_oracle();
    vector<int> iv = Server::iv;

    vector<int> test = random(15);
    for(size_t k = 0; k * 16 < secret.size(); k++){
        vector<int> beforeXOR;
    for(int j = 0; j < 16; j++){
        for(int i = 0; i < 256; i++){
            test = vector<int>(test.begin(), test.begin()+15-j);
            test.push_back(i);
            if(j){
                vector<int> v(j, j+1);
                v = fixedXOR(v, vector<int>(beforeXOR.begin(), beforeXOR.end()));
                test.insert(test.end(), v.begin(), v.end());
            }
            if(test.size() != 16){
                throw runtime_error("ERROR: test has size " + to_string(test.size()));
            }
            test.insert(test.end(), secret.begin() + 16*k, secret.begin()+16*(k+1));
            //for(auto a:test){
            //    cerr << std::hex << (a>>4) << (a&15);
            //}
            
            if(Server::padding_validation_oracle(test)){
                //cerr << " valid" << endl;
                vector<int> padding = {j+1};
                vector<int> prev = {test[test.size()-j-1-16]};
                beforeXOR.insert(beforeXOR.begin(), fixedXOR(padding, prev)[0]);
                break;
            }
            //cerr << " invalid" << endl;
        }
    }
        vector<int> plain;    
        if(k == 0){
            //if(beforeXOR.size() != 16){
            //    throw runtime_error("ERROR: first block not completely decrypted. Size of " + to_string(beforeXOR.size()));
            //}
            plain = fixedXOR(beforeXOR, iv);
        }
        else{
            //if(beforeXOR.size() % 16){
            //    throw runtime_error("ERROR: block " + to_string(k+1) + " not completely decrypted.");
            //}
            //plain = fixedXOR(vector<int>(beforeXOR.end() - 16, beforeXOR.end()), vector<int>(secret.end() - 32, secret.end() - 16));
            plain = fixedXOR(beforeXOR, vector<int>(secret.begin() + 16*(k-1), secret.begin() + 16*k));
        }
        unpad(plain);
        for(auto i = plain.begin(); i < plain.end(); i++){
            cout << (char)*i;
        }

    }
    cout << endl;

   }

