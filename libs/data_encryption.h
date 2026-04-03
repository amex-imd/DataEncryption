#ifndef __IMD_DATA_ENCRYPTION_
#define __IMD_DATA_ENCRYPTION_

#include <string>
#include <cstddef>

namespace IMD
{
    std::string Caesar_cipher_encrypt(const std::string &line, size_t shift, const std::string &alphabet);
    std::string Caesar_cipher_decrypt(const std::string &line, size_t shift, const std::string &alphabet);

}

#endif