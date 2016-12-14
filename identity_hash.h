//      Copyright Rein Halbersma 2016
//      Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/users/license.html).
//      (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef IDENTITY_HASH_H
#define IDENTITY_HASH_H

#include "endian.h"     // endian
#include <cstddef>      // size_t

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme {

class identity_hash
{
        std::size_t m_state;
public:
        static constexpr xstd::endian endian = xstd::endian::native;
        using result_type = std::size_t;

        constexpr void operator()(void const* key, std::size_t /* len */) // Throws: Nothing.
        {
                // Pre-condition: callers must be of the form: identity_hash{}(&x, sizeof(x)).
                // In C++1z, we could annotate the len parameter with [[maybe_unused]]
                // and check the pre-condition in debug mode with assert(len == sizeof(result_type)).
                // In C++14, this requires disabling unused-parameter warnings.
                m_state = *static_cast<result_type const*>(key);
        }

        explicit constexpr operator result_type() const noexcept
        {
                return m_state;
        }
};

}       // namespace acme

#endif  // IDENTITY_HASH_H
