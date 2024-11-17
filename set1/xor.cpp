#include <vector>
#include <string>

#include "xor.h"

namespace cryptopals {
// Normal xor function
std::vector<unsigned char> xorBytes(
        const std::vector<unsigned char>& buffer1,
        const std::vector<unsigned char>& buffer2) {
    if (buffer1.size() != buffer2.size()) {
        // Error: Byte vectors have different sizes
        return {};
    }

    std::vector<unsigned char> result(buffer1.size());

    for (int i = 0; i < buffer1.size(); i += 1) {
        result[i] = buffer1[i] ^ buffer2[i];
    }

    return result;
}

// Single byte xor function
std::vector<unsigned char> xorBytes(
        const std::vector<unsigned char>& buffer,
        unsigned char singleByte) {
    std::vector<unsigned char> results(buffer.size());
    for (size_t i = 0; i < buffer.size(); i += 1) {
        results[i] = buffer[i] ^ singleByte;
    }
    return results;
}

// Repeated xor function
std::vector<unsigned char> xorBytes(
        const std::vector<unsigned char>& buffer,
        const std::string& xorString) {
    std::vector<unsigned char> extendedBytes(buffer.size());
    int j = 0;
    for (size_t i = 0; i < extendedBytes.size(); i += 1) {
        extendedBytes[i] = xorString[j];
        j = (j + 1) % xorString.length();
    }
    return xorBytes(buffer, extendedBytes);
}

std::vector<unsigned char> singleXor(
        const std::vector<unsigned char>& buffer,
        unsigned char singleByte) {
    return xorBytes(buffer, singleByte);
}

std::vector<unsigned char> repeatedXor(
        const std::vector<unsigned char>& buffer,
        const std::string& xorString) {
    return xorBytes(buffer, xorString);
}
}
