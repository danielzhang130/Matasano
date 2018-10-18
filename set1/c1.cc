#include <iostream> 
#include <string>
#include <sstream>
#include <map>

using namespace std;

map<int, string> B64;

string encodeB64(int bytes){
    int mask = 63; // Right 6 bits
    int temp = bytes & mask; 
    string c3 = B64[temp];
    temp = bytes >> 6;
    temp = temp & mask;
    string c2 = B64[temp];
    temp = bytes >> 12;
    temp = temp & mask;
    string c1 = B64[temp];
    temp = bytes >> 18;
    temp = temp & mask;
    string c0 = B64[temp];
    stringstream r;
    r << c0 << c1 << c2 << c3;
    return r.str();
}

int main(){
    int a = 'A';
    for (int i = 0; i < 26; i++){
        B64[i] = string(1, a + i);
    }
    a = 'a';
    for (int i = 26; i< 52; i++){
        B64[i] = string(1, a + i - 26);
    }
    for (int i = 0; i< 10; i++){
        B64[i+52] = to_string(i);
    }
    B64[62] = '+';
    B64[63] = '/';

    string in;
    cin >> in;

    stringstream ss;
    int start = 0;
    
    while(start < in.size()){
        int bytes = 0;
        string sub = in.substr(start, 6); //three bytes
        for( int i = 0; i < 6; i ++){
            int c = stoi(string(1, sub[i]), nullptr, 16);
            bytes = bytes << 4;
            bytes = bytes | c;
        }

        ss << encodeB64(bytes);
        start += 6;

    }

    cout << ss.str() << endl;
    return 0;
}

