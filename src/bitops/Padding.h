#ifndef PADDING_H
#define PADDING_H
#include <vector>

void pad(std::vector<int>& s, unsigned int blockSize);

bool isValidPadding(const std::vector<int>& s);

void unpad(std::vector<int>& s);

// evil
void validate_unpad(std::vector<int>& s);

#endif
