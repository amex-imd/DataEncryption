#include "data_encryption.h"
#include <string>
#include <cstddef>

std::string IMD::Caesar_cipher_encrypt(const std::string &line, size_t shift, const std::string &alphabet)
{
    size_t L(line.size());
    size_t N(alphabet.size());

    std::string res;
    res.reserve(L);

    for (size_t i(0); i < L; ++i)
        res.push_back(alphabet[(alphabet.find(line[i]) + shift) % N]);

    return res;
}
std::string IMD::Caesar_cipher_decrypt(const std::string &line, size_t shift, const std::string &alphabet)
{
    size_t L(line.size());
    size_t N(alphabet.size());

    std::string res;
    res.reserve(L);

    for (size_t i(0); i < L; ++i)
        res.push_back(alphabet[(alphabet.find(line[i]) - shift) % N]);

    return res;
}
