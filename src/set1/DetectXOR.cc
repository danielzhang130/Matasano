#include "1ByteXOR.cc"

int main(){
    vector<vector<int> > lines;
    string s;
    while(getline(cin, s)){
        vector<int> line;
        for(size_t i = 0; i < s.size(); i +=2){
            line.push_back(stoi(s.substr(i, 2), nullptr, 16));
        }
        lines.push_back(line);
    }
    
    vector<vector<int> > best;

    for(vector<int> line:lines){
        best.push_back(decrypt(line));
    }

    vector<int> plaintext;
    int i = 0;
    for(auto line:best){
        if(score(line) > i){
            i = score(line);
            plaintext= line;
        }
    }
    for(auto c:plaintext){
        cout << (char) c;
    }
    cout << endl;

    return 0;
}

