#include "../bitops/FixedXOR.h"
#include <cassert>

using std::vector;

vector<int> fixedXOR(const vector<int>& a, const vector<int>& b){
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
