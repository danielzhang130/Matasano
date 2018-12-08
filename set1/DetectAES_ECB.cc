#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::min_element;
using std::string;
using std::runtime_error;

bool equal(vector<int> a, vector<int> b){
    if(a.size() != b.size()){
        throw runtime_error(a.size() + " != " + b.size());
    }
    for(size_t i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

int main(){
    vector<vector<int>> lines;
    for(string i; getline(cin, i);){
        vector<int> hex;
        for(size_t j = 0; j < i.size(); j+=2){
            hex.push_back(stoul(i.substr(j, 2), nullptr, 16));
        }
        lines.push_back(hex);
    }

    for(size_t i = 0; i < lines.size(); i++){
        for(size_t j = 0; j < lines[i].size(); j+=16){
            vector<int> block(lines[i].begin()+j, lines[i].begin()+j+16);
            for(size_t m = 0; m < lines.size(); m++){
                for(size_t n = 0; n < lines[m].size(); n+=16){
                    if(m != i || n != j){
                        if(equal(block, vector<int> (lines[m].begin()+n, lines[m].begin()+n+16))){
                            cout << "Block starting " << j+1 << " in line " << i+1 << " also found in block starting " << n+1 << " in line " << m+1 << endl;
                        }
                    }
                }  
            }
        }
    }


    //cout << "Edit distance " << *smallest << endl;
    //cout << "Line " << offset << endl;
    //for(size_t i = 0; i < lines[offset].size(); i++){
    //    cout << std::hex << (lines[offset][i]>>4);
    //    cout << std::hex << (lines[offset][i]&15);
    //}

    //cout << endl;
    return 0;
}

