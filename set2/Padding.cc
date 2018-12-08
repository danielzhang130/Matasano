#include <vector>
#include <stdexcept>

using std::vector;
using std::runtime_error;

vector<int> pad(vector<int>& s, unsigned int blockSize){
    if(blockSize == 0){
        throw runtime_error("Block size cannot be 0");
    }
    char c = blockSize - s.size() % blockSize;
    while(s.size() % blockSize != 0){
        s.push_back(c);
    }
    return s;
}
