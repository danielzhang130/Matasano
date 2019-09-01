#ifndef AES_ECB_H
#define AES_ECB_H
#include <string>
#include <vector>

std::vector<int> aes_ecb_decrypt(const std::string& _key, const std::vector<int>& _hex);

std::vector<int> aes_ecb_encrypt(const std::string& _key, std::vector<int> _hex);

std::vector<int> aes_ecb_encrypt(const std::vector<int>& _key, std::vector<int> _char);

std::vector<int> aes_ecb_decrypt(const std::vector<int>& _key, const std::vector<int>& _char);

#endif
