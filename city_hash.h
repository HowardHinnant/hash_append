//------------------------------ city_hash.h -----------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef CITY_HASH_H
#define CITY_HASH_H

#include <cstddef>
#include <vector>
#include "city.h"

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class city
{
    std::vector<char> buf_;
public:
    using result_type = std::size_t;

    void
    operator()(void const* key, std::size_t len) noexcept
    {
        char const* p = static_cast<char const*>(key);
        char const* const e = p + len;
        for (; p < e; ++p)
            buf_.push_back(*p);
    }

    explicit
    operator std::size_t() noexcept
    {
        return CityHash64(buf_.data(), buf_.size());
    }
};

}  // acme

#endif  // CITY_HASH_H
