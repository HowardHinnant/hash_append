//----------------------------- debug_hash.h -----------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef DEBUG_HASH_H
#define DEBUG_HASH_H

#include <cstddef>
#include <vector>
#include <iostream>
#include <iomanip>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class debugHasher
{
    std::vector<unsigned char> buf_;
public:
    using result_type = std::size_t;

    void
    operator()(void const* key, std::size_t len) noexcept
    {
        unsigned char const* p = static_cast<unsigned char const*>(key);
        unsigned char const* const e = p + len;
        for (; p < e; ++p)
            buf_.push_back(*p);
    }

    explicit
    operator std::size_t() noexcept
    {
        std::cout << std::hex;
        std::cout << std::setfill('0');
        unsigned int n = 0;
        for (auto c : buf_)
        {
            std::cout << std::setw(2) << (unsigned)c << ' ';
            if (++n == 16)
            {
                std::cout << '\n';
                n = 0;
            }
        }
        std::cout << '\n';
        std::cout << std::dec;
        std::cout << std::setfill(' ');
        return buf_.size();
    }
};

}  // acme

#endif  // DEBUG_HASH_H
