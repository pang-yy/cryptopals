#include <vector>
#include <string>
#include "string-operation.h"

namespace cryptopals {
// assume hexString is lower case
std::vector<unsigned char> hexToBinary(const std::string& hexString) {
    if (hexString.length() % 2 != 0) {
        return {};     
    }
    std::vector<unsigned char> binary = {};
    for (size_t i = 0; i < hexString.length(); i += 2) {
        char c1 = hexString[i];
        char c2 = hexString[i+1];
        if (c1 >= '0' && c1 <= '9') {
            c1 -= '0';
        } else { // assume lower case only
            c1 = c1 - 'a' + 10;
        }
        if (c2 >= '0' && c2 <= '9') {
            c2 -= '0';
        } else {
            c2 = c2 - 'a' + 10;
        }
        binary.push_back((c1 << 4) | c2);
    }
    return binary;
}

std::string binaryToHex(const std::vector<unsigned char>& binary) {
    std::string hexString = "";
    for (unsigned char byte : binary) {
        hexString += hexCharacters[((byte & 0xf0) >> 4)];
        hexString += hexCharacters[(byte & 0x0f)];
    }
    return hexString; 
}

// RFC 4648
// https://en.wikipedia.org/wiki/Base64
std::string binaryToBase64(const std::vector<unsigned char>& binary) {
    std::string b64String = "";
    if (binary.size() == 1) {
        b64String += base64Characters[(binary[0] >> 2)];
        b64String += base64Characters[((binary[0] & 0x03) << 4)];
        b64String += "==";
    } else if (binary.size() == 2) {
        b64String += base64Characters[(binary[0] >> 2)];
        b64String += base64Characters[((binary[0] & 0x03) << 4) | ((binary[1] & 0xf0) >> 4)];
        b64String += base64Characters[((binary[1] & 0x0f) << 2)];
        b64String += "=";
    } else if (binary.size() >= 3) {
        size_t i = 0;
        for (; (i+2) < binary.size(); i += 3) {
            // first 6-bit
            b64String += base64Characters[(binary[i] >> 2)];
            
            // second 6-bit
            b64String += base64Characters[((binary[i] & 0x03) << 4) | ((binary[i+1] & 0xf0) >> 4)];

            // third 6-bit
            b64String += base64Characters[(((binary[i+1] & 0x0f) << 2) | ((binary[i+2] & 0xc0) >> 6))];

            // fourth 6-bit
            b64String += base64Characters[(binary[i+2] & 0x3f)];
        }
        // remaining characters
        if (i < binary.size()) {
            if ((binary.size() - i) == 1) {
                b64String += base64Characters[(binary[i] >> 2)];
                b64String += base64Characters[((binary[i] & 0x03) << 4)];
                b64String += "==";
            } else {
                b64String += base64Characters[(binary[i] >> 2)];
                b64String += base64Characters[((binary[i] & 0x03) << 4) | ((binary[i+1] & 0xf0) >> 4)];
                b64String += base64Characters[((binary[i+1] & 0x0f) << 2)];
                b64String += "=";
            }
        }
    }

    return b64String;
}

unsigned char b64charToIndex(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 65;
    } else if (c >= 'a' && c <= 'z') {
        return c - 71;
    } else if (c >= '0' && c <= '9') {
        return c + 4;
    } else if (c == '+') {
        return 62;
    } else if (c == '/') {
        return 63;
    } else if (c == '=') {
        return 0;
    }
    // Error: not a base64 characters
    return -1;
}

std::vector<unsigned char> base64ToBinary(const std::string& b64String) {
    if (b64String.length() % 4 != 0) {
        // Error: b64String is not padded
        return {}; 
    }
    std::vector<unsigned char> binary{};
    unsigned char temp[4] = {0};
    for (size_t i = 0; (i+3) < b64String.length(); i += 4) {
        for (int j = 0; j < 4; j += 1) {
            temp[j] = b64charToIndex(b64String[i+j]);
        }

        // first byte
        unsigned char fb = (temp[0] << 2) | ((temp[1] & 0b00110000) >> 4);
        // second byte
        unsigned char sb = (temp[1] << 4) | ((temp[2] & 0b00111100) >> 2);

        // third byte
        unsigned char tb = (temp[2] << 6) | (temp[3] & 0b00111111);

        binary.push_back(fb);
        if (b64String[i+2] != '=') {
            binary.push_back(sb);
        }
        if (b64String[i+3] != '=') {
            binary.push_back(tb);
        }
    }

    return binary;
}

std::string hexToBase64(const std::string& hexString) {
    std::vector<unsigned char> binary = hexToBinary(hexString);
    if (binary.size() <= 0) {
        return "";
    }
    return binaryToBase64(binary);
}

std::string base64ToHex(const std::string& b64String) {
    std::vector<unsigned char> binary = base64ToBinary(b64String);
    if (binary.size() <= 0) {
        return "";
    }
    return binaryToHex(binary);
}
}
