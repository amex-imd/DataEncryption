#include <iostream>
#include <string>
#include <vector>
#include "data_encryption.h"

std::vector<unsigned long long> string_to_bytes(const std::string &line)
{
    std::vector<unsigned long long> res;
    for (unsigned char c : line)
        res.push_back(c);

    return res;
}

std::string bytes_to_string(const std::vector<unsigned long long> &bytes)
{
    size_t L(bytes.size());
    std::string res;
    res.reserve(L);

    for (size_t i(0); i < L; ++i)
        res.push_back(bytes[i]);

    return res;
}

int main()
{
    std::string line = "Hello, World!";
    std::cout << "Source line: " << line << std::endl;

    std::vector<unsigned long long> nums = string_to_bytes(line);

    std::cout << "Numbers: ";
    for (auto num : nums)
        std::cout << num << " ";
    std::cout << std::endl;

    unsigned long long p = 67, q = 89;
    auto [n, e, d] = IMD::key_pair_gen(p, q);

    std::vector<unsigned long long> enc;
    for (auto num : nums)
        enc.push_back(IMD::RSA_encrypt(num, n, e));

    std::cout << "Encrypted numbers: ";
    for (auto x : enc)
        std::cout << x << " ";
    std::cout << std::endl;

    std::vector<unsigned long long> dec;
    for (auto x : enc)
        dec.push_back(IMD::RSA_decrypt(x, n, d));

    std::cout << "Decrypted numbers: ";
    for (auto x : dec)
        std::cout << x << " ";
    std::cout << std::endl;

    line = bytes_to_string(dec);
    std::cout << "Decrypted line: " << line << std::endl;

    std::cin.get();
    return 0;
}