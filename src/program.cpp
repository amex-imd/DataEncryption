#include <iostream>
#include <string>
#include "data_encryption.h"

int main()
{
    std::string line = "HelloWorld";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t shift = 4;

    std::cout << "Source line: " << line << std::endl;
    std::string enc = IMD::Caesar_cipher_encrypt(line, shift, alphabet);
    std::cout << "Encrypted line: " << enc << std::endl;
    std::string dec = IMD::Caesar_cipher_decrypt(enc, shift, alphabet);
    std::cout << "Decrypted line: " << dec << std::endl;

    std::cin.get();

    return 0;
}