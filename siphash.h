//------------------------------- siphash.h ------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
//
// Derived from:
// 
// SipHash reference C implementation
// 
// Written in 2012 by Jean-Philippe Aumasson <jeanphilippe.aumasson@gmail.com>
// Daniel J. Bernstein <djb@cr.yp.to>
// 
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
// 
// You should have received a copy of the CC0 Public Domain Dedication along
// with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.
// 
//------------------------------------------------------------------------------

#ifndef SIPHASH_H
#define SIPHASH_H

#include "endian.h"
#include <cstddef>
#include <cstdint>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class siphash
{
    std::uint64_t v0_ = 0x736f6d6570736575ULL;
    std::uint64_t v1_ = 0x646f72616e646f6dULL;
    std::uint64_t v2_ = 0x6c7967656e657261ULL;
    std::uint64_t v3_ = 0x7465646279746573ULL;
    unsigned char buf_[8];
    unsigned bufsize_ = 0;
    unsigned total_length_ = 0;
public:
    static constexpr xstd::endian endian = xstd::endian::native;
    using result_type = std::size_t;

    siphash() = default;
    explicit siphash(std::uint64_t k0, std::uint64_t k1 = 0) noexcept;

    void
    operator()(void const* key, std::size_t len) noexcept;

    explicit
    operator std::size_t() noexcept;
};

}  // acme

#endif  // SIPHASH_H
