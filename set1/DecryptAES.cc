#include "../bitops/B642Hex.cc"
#include "../aes/aes_ecb.cc"
#include <iostream>

using std::cout;

int main(){
    string s;
    for(string i; getline(std::cin, i);){
        s.append(i);
    }
    vector<int> hex = b64toHex(s, 8);

    vector<int> plaintext = aes_ecb_decrypt("YELLOW SUBMARINE", hex);
    for(auto i:plaintext){
        cout << (char) i;
    }
    cout << endl;
    return 0;
}

