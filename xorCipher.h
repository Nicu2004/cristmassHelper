#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H
#include <string>
using std::string;
using std::move;
std::string xorCipher(std::string data, char key) {
    std::string output = data;
    
    for (int i = 0; i < data.length(); i++) {
        output[i] = data[i] ^ key;
    }
    
    return output;
}

#endif