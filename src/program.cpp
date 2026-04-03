#include <iostream>
#include <string>
#include "data_encryption.h"

int main()
{
    std::string line = "Hello";
    std::string key = "12345";

    auto code = IMD::XOR_encrypt(line, key);

    std::cout << "Size: " << code.size() << " Code: " << code << std::endl;

    code = IMD::XOR_encrypt(code, key);

    std::cout << "Size: " << code.size() << " Code: " << code << std::endl;

    std::cin.get();

    return 0;
}