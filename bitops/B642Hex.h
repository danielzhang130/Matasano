#ifndef B64_2_HEX_H
#define B64_2_HEX_H
#include <vector>
#include <string>

typedef int outputFormat;

std::vector<int> _b2hex(std::string b64, outputFormat of);

std::vector<int> b64toHex(std::string b64, outputFormat of);

#endif
