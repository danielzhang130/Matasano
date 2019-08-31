#ifndef AES_ECB_H
#define AES_ECB_H
#include <string>
#include <vector>

std::vector<int> aes_ecb_decrypt(std::string _key, std::vector<int> _hex);

std::vector<int> aes_ecb_encrypt(std::string _key, std::vector<int> _hex);

std::vector<int> aes_ecb_encrypt(std::vector<int> _key, std::vector<int> _char);

std::vector<int> aes_ecb_decrypt(std::vector<int> _key, std::vector<int> _char);

#endif
