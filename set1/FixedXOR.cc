#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>

using namespace std;

vector<int> fixedXOR(vector<int> a, vector<int> b){
    assert(a.size() == b.size());
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int OR = 0;
    unsigned int AND = 0;
    vector<int> out;
    for(size_t i = 0; i < a.size(); i++){
        x = a[i];
        // x = stoi(string(1, a[i]), nullptr, 16);
        y = b[i];
        //y = stoi(string(1, b[i]), nullptr, 16);
        OR = x | y;
        AND = x & y;
        out.push_back(OR & ~AND);
    }

    return out;
}

//int main(){
//    string s, t;
//    cin >> s;
//    cin >> t;
//    vector<int> a, b;
//    for(size_t i = 0; i < s.size(); i++){
//        a.push_back(stoi(s.substr(i, 1), nullptr, 16));
//        b.push_back(stoi(t.substr(i, 1), nullptr, 16));
//    }
//    vector<int> result = fixedXOR(a,b);
//    for(int i:result){
//        cout << hex << i;
//    }
//    cout << endl;
//    return 0;
//}
