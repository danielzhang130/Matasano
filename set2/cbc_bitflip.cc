#include "../aes/aes_cbc.cc"
#include "../bitops/random.cc"
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<int> key;

vector<int> encrypt(string s){
    for(size_t i = 0; i < s.size(); i++){
        if(s[i] == ';' || s[i] == '='){
            s.insert(i++, "\"");
            s.insert(++i, "\"");
        }
    }
    string temp = "comment1=cooking%20MCs;userdata=";
    s.insert(s.begin(), temp.begin(), temp.end());
    temp = ";comment2=%20like%20a%20pound%20of%20bacon";
    s.insert(s.end(), temp.begin(), temp.end());
    if(key.empty()){
        key = random(16);
    }
    vector<int> plain(s.begin(), s.end());
    vector<int> iv(16, 0);
    return aes_cbc_encrypt(key, plain, iv);
}

bool isAdmin(vector<int> cipher){
    vector<int> iv(16, 0);
    vector<int> _plain = aes_cbc_decrypt(key, cipher, iv);
    string admin = ";admin=true;";
    string plain(_plain.begin(), _plain.end());
    return plain.find(admin) != string::npos;
}

void bitflip(){
    string _plain_target = "%20MCs;userdata=";
    string _result = ";admin=true;ata=";
    vector<int> plain_target(_plain_target.begin(), _plain_target.end());
    vector<int> result(_result.begin(), _result.end());
    vector<int> cipher = encrypt(" ");
    vector<int> original_first(cipher.begin(), cipher.begin()+16);
    vector<int> before_xor = fixedXOR(original_first, plain_target);
    vector<int> first_block = fixedXOR(before_xor, result);
    cipher.erase(cipher.begin(), cipher.begin()+16);
    cipher.insert(cipher.begin(), first_block.begin(), first_block.end());
    cout << isAdmin(cipher) << endl;
}

