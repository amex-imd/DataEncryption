#include "data_encryption.h"
#include <string>
#include <cstddef>
#include <iostream>

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

bool IMD::is_prime(unsigned long long num)
{
    if (num == 0 || num == 1)
        return false;

    if (num == 2)
        return true;

    if (num % 2 == 0)
        return false;

    for (unsigned long long i(3); i * i <= num; i += 2)
        if (num % i == 0)
            return false;

    return true;
}
unsigned long long IMD::Euler_function(unsigned long long num)
{
    unsigned long long res = num;

    for (unsigned long long d(2); d * d <= num; ++d)
    {
        if (num % d == 0)
        {
            while (num % d == 0)
                num /= d;

            res -= res / d;
        }
    }

    if (num > 1)
        res -= res / num;

    /*
    There may be one large divisor greater than the root of 'num'
    Proof:
    Let there be prime divisors of 'num' - 'p' and 'q', greater than the 'root of num'
    num = p * q * k, where 'k' is a number
    We know that p > sqrt(num) and q > sqrt(num), so num = p * q * k >= p * q * 1 > num
    The statement 'num > num' is false
    */

    return res;
}
