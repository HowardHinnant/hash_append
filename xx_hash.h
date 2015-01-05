//------------------------------- xx_hash.h ------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef XX_HASH_H
#define XX_HASH_H

#include "endian.h"
#include "xxhash.h"
#include <climits>
#include <cstddef>
#include <type_traits>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

namespace detail
{

template <std::size_t BITS>
class xx_hash_imp;

template <>
class xx_hash_imp<32>
{
    XXH32_state_t state_;
public:
    xx_hash_imp(unsigned seed = 0) noexcept
    {
        XXH32_reset(&state_, seed);
    }

    void
    update(void const* key, std::size_t len) noexcept
    {
        XXH32_update(&state_, key, len);
    }

    unsigned
    digest() noexcept
    {
        return XXH32_digest(&state_);
    }
};

template <>
class xx_hash_imp<64>
{
    XXH64_state_t state_;
public:
    xx_hash_imp(unsigned long long seed = 0) noexcept
    {
        XXH64_reset(&state_, seed);
    }

    void
    update(void const* key, std::size_t len) noexcept
    {
        XXH64_update(&state_, key, len);
    }

    unsigned long long
    digest() noexcept
    {
        return XXH64_digest(&state_);
    }
};

}  // detail

class xx_hash
    : private detail::xx_hash_imp<sizeof(std::size_t)*CHAR_BIT>
{
    using base = detail::xx_hash_imp<sizeof(std::size_t)*CHAR_BIT>;
    using base_result = std::conditional_t<sizeof(std::size_t)*CHAR_BIT == 32,
                                 unsigned, unsigned long long>;
public:
    // Change to native if XXH_FORCE_NATIVE_FORMAT == 1 in xxhash.c
    static constexpr xstd::endian endian = xstd::endian::little;
    using result_type = std::size_t;

    xx_hash(std::size_t seed = 0) noexcept
        : base(static_cast<base_result>(seed))
    {
    }

    void
    operator()(void const* key, std::size_t len) noexcept
    {
        this->update(key, len);
    }

    explicit
    operator result_type() noexcept
    {
        return static_cast<std::size_t>(this->digest());
    }
};

}  // acme

#endif  // XX_HASH_H
