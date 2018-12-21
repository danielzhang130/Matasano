#include "../bitops/FixedXOR.cc"

int main(){
    vector<vector<int> > lines;
    string s;
    while(getline(cin, s)){
        vector<int> line;
        for(size_t i = 0; i<s.size(); i ++){
            line.push_back(s[i]);
        }
        if(cin.peek() != EOF){
            line.push_back(10);
        }
        lines.push_back(line);
    }

    vector<int> key{'I', 'C', 'E'};

    vector<vector<int> > ciphertexts;
    int i = 0;
    for(auto line:lines){
        vector<int> cipher;
        vector<int> longKey;
        for(size_t j = 0; j < line.size(); j++){
            longKey.push_back(key.at(i%3));
            i++;
        }
        cipher = fixedXOR(line, longKey);
        ciphertexts.push_back(cipher);
    }

    for(auto line:ciphertexts){
        for(int c:line){
            cout << hex << (c >> 4) << (c & 15);
        }
    }

    cout << endl;
    return 0;
}
