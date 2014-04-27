//-------------------------------- fnv1a.h -------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef FNV1A_H
#define FNV1A_H

#include <cstddef>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class fnv1a
{
    std::size_t state_ = 14695981039346656037u;
public:

    using result_type = std::size_t;

    void
    operator()(void const* key, std::size_t len) noexcept
    {
        unsigned char const* p = static_cast<unsigned char const*>(key);
        unsigned char const* const e = p + len;
        for (; p < e; ++p)
            state_ = (state_ ^ *p) * 1099511628211u;
    }

    explicit
    operator std::size_t() noexcept
    {
        return state_;
    }
};

}  // acme

#endif  // FNV1A_H
