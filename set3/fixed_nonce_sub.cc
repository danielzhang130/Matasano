#include "../aes/aes_ctr.cc"
#include "../bitops/B642Hex.cc"
#include "../bitops/random.cc"

class Server{
    private:
        vector<int> key;
        vector<int> nonce;
        vector<string> plains = {
            "SSBoYXZlIG1ldCB0aGVtIGF0IGNsb3NlIG9mIGRheQ==",
            "Q29taW5nIHdpdGggdml2aWQgZmFjZXM=",
            "RnJvbSBjb3VudGVyIG9yIGRlc2sgYW1vbmcgZ3JleQ==",
            "RWlnaHRlZW50aC1jZW50dXJ5IGhvdXNlcy4=",
            "SSBoYXZlIHBhc3NlZCB3aXRoIGEgbm9kIG9mIHRoZSBoZWFk",
            "T3IgcG9saXRlIG1lYW5pbmdsZXNzIHdvcmRzLA==",
            "T3IgaGF2ZSBsaW5nZXJlZCBhd2hpbGUgYW5kIHNhaWQ=",
            "UG9saXRlIG1lYW5pbmdsZXNzIHdvcmRzLA==",
            "QW5kIHRob3VnaHQgYmVmb3JlIEkgaGFkIGRvbmU=",
            "T2YgYSBtb2NraW5nIHRhbGUgb3IgYSBnaWJl",
            "VG8gcGxlYXNlIGEgY29tcGFuaW9u",
            "QXJvdW5kIHRoZSBmaXJlIGF0IHRoZSBjbHViLA==",
            "QmVpbmcgY2VydGFpbiB0aGF0IHRoZXkgYW5kIEk=",
            "QnV0IGxpdmVkIHdoZXJlIG1vdGxleSBpcyB3b3JuOg==",
            "QWxsIGNoYW5nZWQsIGNoYW5nZWQgdXR0ZXJseTo=",
            "QSB0ZXJyaWJsZSBiZWF1dHkgaXMgYm9ybi4=",
            "VGhhdCB3b21hbidzIGRheXMgd2VyZSBzcGVudA==",
            "SW4gaWdub3JhbnQgZ29vZCB3aWxsLA==",
            "SGVyIG5pZ2h0cyBpbiBhcmd1bWVudA==",
            "VW50aWwgaGVyIHZvaWNlIGdyZXcgc2hyaWxsLg==",
            "V2hhdCB2b2ljZSBtb3JlIHN3ZWV0IHRoYW4gaGVycw==",
            "V2hlbiB5b3VuZyBhbmQgYmVhdXRpZnVsLA==",
            "U2hlIHJvZGUgdG8gaGFycmllcnM/",
            "VGhpcyBtYW4gaGFkIGtlcHQgYSBzY2hvb2w=",
            "QW5kIHJvZGUgb3VyIHdpbmdlZCBob3JzZS4=",
            "VGhpcyBvdGhlciBoaXMgaGVscGVyIGFuZCBmcmllbmQ=",
            "V2FzIGNvbWluZyBpbnRvIGhpcyBmb3JjZTs=",
            "SGUgbWlnaHQgaGF2ZSB3b24gZmFtZSBpbiB0aGUgZW5kLA==",
            "U28gc2Vuc2l0aXZlIGhpcyBuYXR1cmUgc2VlbWVkLA==",
            "U28gZGFyaW5nIGFuZCBzd2VldCBoaXMgdGhvdWdodC4=",
            "VGhpcyBvdGhlciBtYW4gSSBoYWQgZHJlYW1lZA==",
            "QSBkcnVua2VuLCB2YWluLWdsb3Jpb3VzIGxvdXQu",
            "SGUgaGFkIGRvbmUgbW9zdCBiaXR0ZXIgd3Jvbmc=",
            "VG8gc29tZSB3aG8gYXJlIG5lYXIgbXkgaGVhcnQs",
            "WWV0IEkgbnVtYmVyIGhpbSBpbiB0aGUgc29uZzs=",
            "SGUsIHRvbywgaGFzIHJlc2lnbmVkIGhpcyBwYXJ0",
            "SW4gdGhlIGNhc3VhbCBjb21lZHk7",
            "SGUsIHRvbywgaGFzIGJlZW4gY2hhbmdlZCBpbiBoaXMgdHVybiw=",
            "VHJhbnNmb3JtZWQgdXR0ZXJseTo=",
            "QSB0ZXJyaWJsZSBiZWF1dHkgaXMgYm9ybi4="
        };

    public:
        Server(){
            key = random(16);
            nonce = vector<int>(16, 0);
        }

        vector<vector<int>> encrypt(){
            vector<vector<int>> ciphers;
            for(auto plain:plains){
                ciphers.push_back(aes_ctr_encrypt(key, b64toHex(plain, 8), nonce));
            }
            return ciphers;
        }
};

void decrypt(){
    Server server = Server();
    vector<vector<int>> ciphers = server.encrypt();
    vector<vector<int>> plains;
    for(size_t i = 0; i < ciphers.size(); i++){
        plains.push_back(vector<int>());
    }

    size_t j = 0;
    size_t max = ciphers[0].size();
    for(size_t i = 1; i < ciphers.size(); i++){
        if(ciphers[i].size() > max){
            max = ciphers[i].size();
        }
    }
    int ref = 0;

    while(j < max){
        string _guess;
        cout << "Guess first letter:" << std::flush;
        getline(cin, _guess);
        int guess = _guess[0];

        int diff = fixedXOR(vector<int>{guess}, vector<int>{ciphers[ref][j]})[0];

        for(size_t i = 0; i < ciphers.size(); i++){
            if(j < ciphers[i].size()){
                int c = ciphers[i][j];
                plains[i].push_back(fixedXOR(vector<int>{c}, vector<int>{diff})[0]);
            }
            for(auto a:plains[i]){
                cout << (char) a;
            }
            cout << endl;
        }
        
        string ans;
        while(ans != "y" && ans != "n" && ans != "r"){
            cout << "Right guess [y/n/r]?" << std::flush;
            getline(cin, ans);
        }
        if(ans == "y"){
            j++;
            while(j >= ciphers[ref].size()){
                ref++;
            }
        }
        else if(ans == "r"){
            for(size_t i = 0; i < plains.size(); i++){
                if(plains[i].size() >= j){
                    plains[i].pop_back();
                    plains[i].pop_back();
                }
            }
            j--;
        }
        else{
            for(size_t i = 0; i < plains.size(); i++){
                if(plains[i].size() >= j){
                    plains[i].pop_back();
                }
            }
        }
    }
}
