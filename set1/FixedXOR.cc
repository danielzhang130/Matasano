#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;

string fixedXOR(string a, string b){
    assert(a.size() == b.size());
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int OR = 0;
    unsigned int AND = 0;
    stringstream out;
    for(int i = 0; i < a.size(); i++){
        x = stoi(string(1, a[i]), nullptr, 16);
        y = stoi(string(1, b[i]), nullptr, 16);
        OR = x | y;
        AND = x & y;
        out << hex << (OR & ~AND);
    }

    return out.str();
}

int main(){
    string s, t;
    cin >> s;
    cin >> t;
    cout << fixedXOR(s,t) << endl;
    return 0;
}
