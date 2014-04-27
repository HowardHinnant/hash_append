//------------------------------- spooky.h -------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef SPOOKY_H
#define SPOOKY_H

#include <cstddef>
#include "SpookyV2.h"

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class spooky
{
    SpookyHash state_;
public: 
    using result_type = std::size_t;

    spooky(std::size_t seed1 = 1, std::size_t seed2 = 2) noexcept
    {
        state_.Init(seed1, seed2);
    }

    void
    operator()(void const* key, std::size_t len) noexcept
    {
        state_.Update(key, len);
    }

    explicit
    operator result_type() noexcept
    {
        std::uint64_t h1, h2;
        state_.Final(&h1, &h2);
        return h1;
    }
};

}  // acme

#endif  // SPOOKY_H
