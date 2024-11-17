#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

namespace cryptopals {
int hammingDist(const std::string& str1, const std::string& str2);

int hammingDist(const std::vector<unsigned char>& buffer1,
                const std::vector<unsigned char>& buffer2);
}

#endif /* UTIL_H */
