//------------------------------- jenkins1.h -----------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef JENKINS1_H
#define JENKINS1_H

#include <cstddef>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class jenkins1
{
    std::size_t state_ = 0;

public:
    using result_type = std::size_t;

    void
    operator()(void const* key, std::size_t len) noexcept
    {
        unsigned char const* p = static_cast<unsigned char const*>(key);
        unsigned char const* const e = p + len;
        for (; p < e; ++p)
        {
            state_ += *p;
            state_ += state_ << 10;
            state_ ^= state_ >> 6;
        }
    }

    explicit
    operator std::size_t() noexcept
    {
        state_ += state_ << 3;
        state_ ^= state_ >> 11;
        state_ += state_ << 15;
        return state_;
    }
};

}  // acme

#endif  // JENKINS1_H
