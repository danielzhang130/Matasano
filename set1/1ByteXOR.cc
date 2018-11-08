#include <iostream>
#include <string>
#include <vector>
#include "FixedXOR.cc"

using namespace std;

int score(vector<int>& text){
    int score = 0;
    for(auto i : text){
        if(i == ' ' || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')){
            score++;
        }
    }
    return score;
}

vector<int> decrypt(vector<int>& text){
    vector<int> best;
    int bestScore = 0;
    for(int i = 0; i < 128; i++){
        vector<int> copy;
        for(int j: text){
            copy.push_back(fixedXOR(vector<int>{j}, vector<int>{i})[0]);
        }
        if(score(copy) > bestScore){
            bestScore = score(copy);
            best = copy;
        }
    }
    return best;
}


//int main(){
//    string s;
//    vector<int> chars;
//    cin >> s;
//    for(size_t i = 0; i < s.size(); i+=2){
//        chars.push_back(stol(s.substr(i,2), nullptr, 16));
//    }
//
//    decrypt(chars);
//    return 0;
//}
//
