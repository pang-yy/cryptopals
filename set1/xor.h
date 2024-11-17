#ifndef XOR_H
#define XOR_H

#include <vector>
#include <string>

namespace cryptopals {
std::vector<unsigned char> xorBytes(
    const std::vector<unsigned char>& buffer1,
    const std::vector<unsigned char>& buffer2);

std::vector<unsigned char> xorBytes(
    const std::vector<unsigned char>& buffer,
    unsigned char singleByte);

std::vector<unsigned char> xorBytes(
    const std::vector<unsigned char>& buffer,
    const std::string& xorString);

std::vector<unsigned char> singleXor(
    const std::vector<unsigned char>& buffer,
    unsigned char singleByte);

std::vector<unsigned char> repeatedXor(
    const std::vector<unsigned char>& buffer,
    const std::string& xorString);
}

#endif /* XOR_H */
