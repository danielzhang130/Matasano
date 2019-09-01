#ifndef AES_CBC_H
#define AES_CBC_H
#include <vector>
#include <string>

std::vector<int> aes_cbc_encrypt(const std::string& _key, const std::vector<int>& _char, const std::vector<int>& _iv);

std::vector<int> aes_cbc_decrypt(const std::string& _key, const std::vector<int>& _char, const std::vector<int>& _iv);

std::vector<int> aes_cbc_encrypt(const std::vector<int>& _key, const std::vector<int>& _char, const std::vector<int>& _iv);

std::vector<int> aes_cbc_decrypt(const std::vector<int>& _key, const std::vector<int>& _char, const std::vector<int>& _iv);

#endif
