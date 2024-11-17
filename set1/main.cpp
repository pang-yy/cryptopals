#include <iostream>
#include <fstream>
#include <string>

#include "string-operation.h"
#include "xor.h"
#include "util.h"

bool test64() {
    std::string b64String = "";
    std::ifstream inputFile("6.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open 6.txt\n";
    }
    while (std::getline(inputFile, b64String)) {
        std::cout << "Base64: " << b64String << std::endl;
        std::string hexString = cryptopals::base64ToHex(b64String);
        std::cout << "Hex: " << hexString << std::endl;
        std::string convertBack = cryptopals::hexToBase64(hexString);
        std::cout << "Convert Back: " << convertBack << std::endl;

        if (b64String != convertBack) {
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        }
    }
    return true;
}

bool challenge6(const std::string& str1, const std::string& str2) {
    std::ifstream inputFile("6.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open 6.txt\n";
        return false;
    }

    std::string line = "";
    std::string fileContent = "";
    while(std::getline(inputFile, line)) {
        fileContent += line;
    }
    
    if (fileContent.length() % 4 == 0) {
        std::cout << "yes\n";
    } else {
        std::cout << "no\n";
    }

    return false;
}

bool challenge5(const std::string& input, const std::string& output) {
    std::vector<unsigned char> inputVec(input.length());
    for (int i = 0; i < input.length(); i += 1) {
        inputVec[i] = input[i];
    }
    const std::string key = "ICE";
    std::vector<unsigned char> binAnswer = cryptopals::repeatedXor(inputVec, key);
    std::string answer = cryptopals::binaryToHex(binAnswer);
    return answer == output;
}

bool challenge4() {
    std::ifstream inputFile("4.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open 4.txt\n";
        return false;
    }

    std::string line = "";
    std::ofstream outputFile("4.out");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open 4.out\n";
        return false;
    }

    std::vector<unsigned char> bin = {};
    std::vector<unsigned char> ans = {};
    while(std::getline(inputFile, line)) {
        bin = cryptopals::hexToBinary(line);
        for (unsigned char c : cryptopals::base64Characters) {
            ans = cryptopals::xorBytes(bin, c);
            for (unsigned char b : ans) {
                outputFile << (char)b;
            }
            outputFile << '\n';
        }
    }
    outputFile.close();

    // The answer should be: Now that the party is jumping
    // Key: '5'
    // Hex: "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f"

    return true;
}

bool challenge3(const std::string& input) {
    const std::vector<unsigned char> bin = cryptopals::hexToBinary(input);
    std::vector<unsigned char> answer = {};
    
    /* 
    for (unsigned char c : cryptopals::base64Characters) {
        answer = cryptopals::xorBytes(bin, c);
        std::cout << "[" << c << "]: ";
        for (unsigned char a: answer) {
            std::cout << a;
        }
        std::cout << std::endl;
    }
    */
    answer = cryptopals::xorBytes(bin, 'X');
    for (unsigned char c : answer) {
        std::cout << c;
    }
    std::cout << std::endl;
    return true;
}

bool challenge2(const std::string& input1, const std::string& input2,
        const std::string& output) {
    const std::vector<unsigned char> bin1 = cryptopals::hexToBinary(input1);
    const std::vector<unsigned char> bin2 = cryptopals::hexToBinary(input2);
    std::string answer = cryptopals::binaryToHex(cryptopals::xorBytes(bin1, bin2));
    return answer == output;
}

bool challenge1(const std::string& input, const std::string& output) {
    std::string answer = cryptopals::hexToBase64(input);
    return answer == output;
}

int main() {
/*
    if (challenge1("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d", "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t")) {
        std::cout << "passed c1\n";
    } else {
        std::cout << "failed c1\n";
    }
*/
/*
    if (challenge2("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965", "746865206b696420646f6e277420706c6179")) {
        std::cout << "passed c2\n";
    } else {
        std::cout << "failed c2\n";
    }
*/
    //challenge3("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    //challenge4();
/*
    if (challenge5("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f")) {
        std::cout << "passed c5\n";
    } else {
        std::cout << "failed c5\n";
    }
*/
    challenge6("this is a test", "wokka wokka!!!");
    return 0;
}
