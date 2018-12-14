#include <vector>
#include <stdexcept>

using std::vector;
using std::runtime_error;

void pad(vector<int>& s, unsigned int blockSize){
    if(blockSize == 0){
        throw runtime_error("Block size cannot be 0");
    }
    char c = blockSize - s.size() % blockSize;
    while(s.size() % blockSize != 0){
        s.push_back(c);
    }
}

void unpad(vector<int>& s){
    int sz = s.size();
    int c = s[sz-1];
    if(c >= sz){
        return;
    }
    for(int i = 1; i < c; i++){
        if(s[sz-1-i] != c){
            return;
        }
    }
    while(c){
        s.pop_back();
        c--;
    }
}