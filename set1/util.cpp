#include <vector>
#include <string>

#include "util.h"

namespace cryptopals {
int hammingDist(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        // Error: Strings have different lengths
        return -1;
    }
    
    int count = 0;

    char t;
    for (size_t i = 0; i < str1.length(); i += 1) {
        t = str1[i] ^ str2[i];
        while (t != 0) {
            count += 1;
            t = t & (t - 1);
        }
    }

    return count;
}

int hammingDist(const std::vector<unsigned char>& buffer1, 
                const std::vector<unsigned char>& buffer2) {
    if (buffer1.size() != buffer2.size()) {
        // Error: Byte vectors have different sizes
        return -1;
    }

    int count = 0;

    unsigned char t;
    for (size_t i = 0; i < buffer1.size(); i += 1) {
        t = buffer1[i] ^ buffer2[i];
        while (t != 0) {
            count += 1;
            t = t & (t - 1);
        }
    }

    return count;
}
}
