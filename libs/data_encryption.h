#ifndef __IMD_DATA_ENCRYPTION_
#define __IMD_DATA_ENCRYPTION_

#include <string>
#include <cstddef>
#include <stdexcept>
#include <cstdarg>
#include <tuple>
#include <vector>
#include <iostream>

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

    bool is_prime(unsigned long long num);

    unsigned long long Euler_function(unsigned long long num);

    unsigned long long mod_pow(unsigned long long base, unsigned long long pow, unsigned long long mod);

    unsigned long long mod_inverse(unsigned long long a, unsigned long long mod);

    template <typename T>
    std::tuple<T, std::vector<long long>> linear_gcd_representation(T a, T b)
    {
        long long u0 = 1, v0 = 0;
        long long u1 = 0, v1 = 1;

        while (b != 0)
        {
            long long q = a / b;
            long long r = a % b;

            long long u = u0 - u1 * q, v = v0 - v1 * q;
            a = b;
            b = r;
            u0 = u1;
            v0 = v1;
            u1 = u;
            v1 = v;
        }
        return {a, {u0, v0}};
    }

    template <typename T, typename... Args>
    std::tuple<T, std::vector<long long>> linear_gcd_representation(T a, T b, Args... args)
    {
        auto [ab_gcd, ab_coeffs] = linear_gcd_representation(a, b);

        if constexpr (sizeof...(args) == 0)
            return {ab_gcd, ab_coeffs};
        else
        {
            auto [general_gcd, rest_coeffs] = linear_gcd_representation(ab_gcd, args...);

            std::vector<long long> res;       // final coefficients
            res.reserve(2 + sizeof...(args)); // Don't forget about coefficients 'a' and 'b'

            res.push_back(rest_coeffs[0] * ab_coeffs[0]);
            res.push_back(rest_coeffs[0] * ab_coeffs[1]);

            res.insert(res.end(), rest_coeffs.begin() + 1, rest_coeffs.end());

            return {general_gcd, res};
        }
    }

    // --------RSA--------

    std::tuple<unsigned long long, unsigned long long, unsigned long long> key_pair_gen(unsigned long long p, unsigned long long q);

    unsigned long long RSA_encrypt(unsigned long long message, unsigned long long n, unsigned long long e);

    unsigned long long RSA_decrypt(unsigned long long cipher, unsigned long long n, unsigned long long d);

}

#endif