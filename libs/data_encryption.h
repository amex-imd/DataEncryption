#ifndef __IMD_DATA_ENCRYPTION_
#define __IMD_DATA_ENCRYPTION_

#include <string>
#include <cstddef>
#include <stdexcept>
namespace IMD
{
    // -------- CAESAR CIPHER--------
    std::string Caesar_cipher_encrypt(const std::string &line, size_t shift, const std::string &alphabet);
    std::string Caesar_cipher_decrypt(const std::string &line, size_t shift, const std::string &alphabet);

    // --------XOR ENCRYPTION--------

    template <typename Container>
    Container XOR_transform(const Container &data, const Container &key)
    {
        size_t N(data.size());
        size_t L(key.size());

        if (N != L)
            throw std::runtime_error("The arguments 'data' and 'key' must have the same size");

        Container res;
        res.reserve(N);

        for (size_t i(0); i < N; ++i)
            res.push_back(data[i] ^ key[i]);

        return res;
    }
}

#endif