#include <iostream>
#include <string>
#include <vector>
#include "FixedXOR.cc"

using namespace std;

bool isEnglish(vector<int> text){
    for(int i: text){
        if(i < 32 || i == '#' || i == '%' || i == '*' || i == '<' || i == '>' || i == '@' || i == '~' || i == '`' || i == '{' || i == '}' || i == 127){
            return false;
        }
    }
    int lower = 0;
    int upper = 0;
    int other = 0;
    for(int i : text){
        if(i > 64 && i < 91){
            upper++;
        }
        else if(i >96 && i < 123){
            lower++;
        }
        else{
            other++;
        }
    }
    if(other > lower + upper){
        return false;
    }
    return lower > upper;
}

void decrypt(vector<int> text){
    for(int i = 0; i < 128; i++){
        vector<int> copy;
        for(int j: text){
            copy.push_back(fixedXOR(vector<int>{j}, vector<int>{i})[0]);
        }
        if(isEnglish(copy)){
            for(int j: copy){
                cout << (char)j;
            }
            cout << endl;
        }
    }
}


int main(){
    string s;
    vector<int> chars;
    cin >> s;
    for(size_t i = 0; i < s.size(); i+=2){
        chars.push_back(stol(s.substr(i,2), nullptr, 16));
    }

    decrypt(chars);
    return 0;
}

