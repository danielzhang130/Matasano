#ifndef SHA1_H
#define SHA1_H
#include <vector>
#include <stdint.h>

std::vector<int> sha1(const std::vector<int>& _message, const uint32_t _state[5] = nullptr, uint64_t ml = 0);
#endif
