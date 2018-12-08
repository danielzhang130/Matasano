#include "1ByteXOR.cc"
#include "B642Hex.cc"
#include <map>
#include <iterator>
#include <exception>

int distance(vector<int> a, vector<int> b){
    vector<int> diff = fixedXOR(a, b);
    int distance = 0;
    for(auto i:diff){
        if(i & 128) distance++;
        if(i & 64) distance++;
        if(i & 32) distance++;
        if(i & 16) distance++;
        if(i & 8) distance++;
        if(i & 4) distance++;
        if(i & 2) distance++;
        if(i & 1) distance++; 
    }
    return distance;
}

int main(){
    string b64;
    for(string s; getline(cin,s);){
        b64.append(s);
    }

    vector<int> hex = b64toHex(b64, 1);
    //for(int i:hex){
    //    cout << i;
    //}

    vector<int> keySizes = {400};;
    vector<double> keyDistances = {9999};
    int maxKeySize = 40;
    for(int i = 16; i < 8*maxKeySize; i+=8){
        double avg = 0;
        size_t j = 0;
        for(; j+2 < hex.size()/i; j++){
        vector<int> a(hex.begin()+i*j, hex.begin() + i*(j+1));
        vector<int> b(hex.begin()+i*(j+1), hex.begin() + i*(j+2));
        //vector<int> c(hex.begin()+2*i, hex.begin() + i*3);
        //vector<int> d(hex.begin()+3*i, hex.begin() + i*4);
            avg += distance(a, b);
        }
        avg = avg/i/j*8;
        //avg = distance(a, b) + distance(b,c) + distance(c, d);
        //avg = avg /i/3*8;
        vector<double>::iterator pos = lower_bound(keyDistances.begin(), keyDistances.end(), avg);
        int diff = std::distance(keyDistances.begin(), pos);
        keyDistances.insert(pos, avg);
        keySizes.insert(keySizes.begin() + diff, i);
        //if(avg < keyDistances[0]){
        //    keyDistance = avg;
        //    keySize = i;
        //}
    }
    int keySize = keySizes[0];
    double keyDistance = keyDistances[0];
    cout << "distance " <<keyDistance << endl;
    cout << "key size " << keySize << endl;

    vector<vector<int>> keyBitBlocks;
    for(int i = 0; i < keySize/8; i++){
        keyBitBlocks.push_back(vector<int>());
    }
    for(size_t i = 0; i < hex.size(); i++){
        keyBitBlocks[(i%keySize)/8].push_back(hex[i]);
    }

    vector<vector<int>> keyByteBlocks;
    for(int i = 0; i < keySize/8; i++){
        keyByteBlocks.push_back(vector<int>());
    }
    for(size_t i = 0; i < keyBitBlocks.size(); i++){
        for(size_t j = 0; j < keyBitBlocks[i].size(); j+=8){
            int sum = 0;
            for(int k = 0; k < 8; k++){
                sum = sum << 1;
                sum += keyBitBlocks[i][j+k];
            }
            keyByteBlocks[i].push_back(sum);
        }
    }

    //for(size_t i = 0; i < keyByteBlocks[0].size(); i++){
    //    for(size_t j = 0; j < keyByteBlocks.size(); j++){
    //        cout << std::hex << (keyByteBlocks[j][i] >> 4);
    //        cout << std::hex << (keyByteBlocks[j][i] & 15);
    //    }
    //}
    //cout << endl;
    //return 0;

    vector<vector<int>> decrypted;
    for(size_t i = 0; i < keyByteBlocks.size(); i++){
        decrypted.push_back(vector<int>());
    }
    for(size_t i = 0; i < keyByteBlocks.size(); i++){
        decrypted[i] = decrypt(keyByteBlocks[i]);
    }
    for(size_t i = 0; i < decrypted[0].size(); i++){
        for(size_t j = 0; j < decrypted.size(); j++){
            try{
                cout << (char)decrypted.at(j).at(i);
            }
            catch(out_of_range& e){
                continue;
            }   
        }
    }
    cout << endl;

    cout << "Key is ";
    for(size_t i = 0; i < decrypted.size(); i++){
        cout << (char)fixedXOR(vector<int> {keyByteBlocks[i]}, vector<int> {decrypted[i]})[0];
    }
    cout << endl;


    //vector<int> a = {'t', 'h', 'i', 's',' ','i','s',' ','a',' ','t','e','s','t'};
    //vector<int> b = {'w','o','k','k','a',' ','w','o','k','k','a','!','!','!'};
    //cout << distance(a, b);
    
    return 0;
}
