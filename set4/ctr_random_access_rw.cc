
#include <vector>
#include <string>


namespace ctr_random_access_rw{
    using std::vector;
    using std::string;
    class Server{
        vector<int> key;
        vector<int> cipher;

        public:
        Server(){

        }
        vector<int> encrypt(){

        }

        vector<int> edit(size_t offset, vector<int> new_text){

        }
    };

    void decrypt(){
        // idea:
        // by controlling the new_text and the resulting ciphertext,
        // the key can be calculated and the original ciphertext
        // can be decrypted.
    }
}
