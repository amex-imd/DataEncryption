#ifndef __IMD_DATA_ENCRYPTION_
#define __IMD_DATA_ENCRYPTION_

#include <string>
#include <cstddef>
#include <stdexcept>
#include <cstdarg>
#include <tuple>
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

    // --------EXTRA FUNCTIONS--------

    template <typename T>
    T gcd(T a, T b)
    {
        while (b != 0)
        {
            T t = b;
            b = a % b;
            a = t;
        }
        return a < 0 ? -a : a;
    }

    template <typename T, typename... Args>
    T gcd(T first, Args... args)
    {
        T rest = gcd(args...);
        return gcd(first, rest);
    }

    bool is_prime(unsigned long long num);

    unsigned long long Euler_function(unsigned long long num);

    unsigned long long mod_pow(unsigned long long base, unsigned long long pow, unsigned long long mod);

    unsigned long long mod_inverse(unsigned long long a, unsigned long long mod);

    std::tuple<long long, long long> linear_gcd_representation(unsigned long long a, unsigned long long b);

    // --------RSA--------

    std::tuple<unsigned long long, unsigned long long, unsigned long long> key_pair_gen(unsigned long long p, unsigned long long q);

    unsigned long long RSA_encrypt(unsigned long long message, unsigned long long n, unsigned long long e);

    unsigned long long RSA_decrypt(unsigned long long cipher, unsigned long long n, unsigned long long d);

}

#endif