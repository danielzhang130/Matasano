#ifndef AES_CTR_H
#define AES_CTR_H
#include <vector>

#define aes_ctr_decrypt aes_ctr_encrypt

std::vector<int> aes_ctr_encrypt(std::vector<int> key, std::vector<int> plain, std::vector<int> nonce);

#endif
