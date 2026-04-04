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

unsigned long long IMD::mod_pow(unsigned long long base, unsigned long long pow, unsigned long long mod)
{
    if (pow == 0 && base == 0)
        throw std::invalid_argument("The arguments 'base' and 'pow' can't be equal to 0 the same time");
    if (mod == 0)
        throw std::invalid_argument("The argument 'mod' can't be equal to 0");

    if (base == 1 || pow == 0)
        return 1 % mod;
    if (pow == 1)
        return base % mod;

    base %= mod;
    unsigned long long res(1);

    while (pow > 0)
    {
        if (pow % 2 != 0)
        {
            res = (res * base) % mod;
            --pow;
        }
        else
        {
            base = (base * base) % mod;
            pow /= 2;
        }
    }

    return res;
}

std::tuple<long long, long long> IMD::linear_gcd_representation(unsigned long long a, unsigned long long b)
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
    return {u0, v0};
}
unsigned long long IMD::mod_inverse(unsigned long long a, unsigned long long mod)
{
    auto [x, y] = IMD::linear_gcd_representation(a, mod);
    auto gcd = IMD::gcd(a, mod);

    if (gcd != 1)
    {
        throw std::invalid_argument("Обратного элемента не существует");
    }
    return (x % mod + mod) % mod;
}
std::tuple<unsigned long long, unsigned long long, unsigned long long> IMD::key_pair_gen(unsigned long long p, unsigned long long q)
{
    if (!is_prime(p) || !is_prime(q))
        throw std::invalid_argument("The both arguments 'p' and 'q' must be prime");

    unsigned long long n(p * q);

    unsigned long long phi = Euler_function(n); // The Euler function will be even if n > 2
    unsigned long long e = 65537;               // Open key

    if (phi % e == 0)
    {
        for (e = 3; e < phi; e += 2)
        {
            if (phi % e != 0)
                break;
        }
    }

    unsigned long long d = mod_inverse(e, phi); // Close key

    return {n, e, d};
}
unsigned long long IMD::RSA_encrypt(unsigned long long message, unsigned long long n, unsigned long long e)
{
    if (message >= n)
        throw std::invalid_argument("TODO");

    return IMD::mod_pow(message, e, n);
}

unsigned long long IMD::RSA_decrypt(unsigned long long cipher, unsigned long long n, unsigned long long d)
{
    return mod_pow(cipher, d, n);
}