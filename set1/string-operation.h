#ifndef STRING_OPERATION_H
#define STRING_OPERATION_H

#include <string>
#include <vector>

namespace cryptopals {
const std::vector<char> hexCharacters = {
    '0', '1', '2', '3', 
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};

// RFC 4648
const std::vector<char> base64Characters = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};
const char base64Padding = '=';

std::vector<unsigned char> hexToBinary(const std::string& hexString);
std::string binaryToHex(const std::vector<unsigned char>& binary);

std::string binaryToBase64(const std::vector<unsigned char>& binary);
std::vector<unsigned char> base64ToBinary(const std::string& b64String);

std::string hexToBase64(const std::string& hexString);
std::string base64ToHex(const std::string& b64String);
}

#endif /* STRING_OPERATION_H */
