#ifndef AES_CBC_H
#define AES_CBC_H
#include <vector>
#include <string>

std::vector<int> aes_cbc_encrypt(std::string _key, std::vector<int> _char, std::vector<int> _iv);

std::vector<int> aes_cbc_decrypt(std::string _key, std::vector<int> _char, std::vector<int> _iv);

std::vector<int> aes_cbc_encrypt(std::vector<int> _key, std::vector<int> _char, std::vector<int> _iv);

std::vector<int> aes_cbc_decrypt(std::vector<int> _key, std::vector<int> _char, std::vector<int> _iv);

#endif
