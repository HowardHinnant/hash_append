//------------------------------- test3.cpp ------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#include "hash_append.h"

#include <cassert>
#include <iostream>

struct X
{
    static constexpr xstd::endian desired_endian = xstd::endian::big;
};

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <type_traits>

#if 1

#ifdef htonl
#undef htonl
#undef htons
#undef ntohl
#undef ntohs
#endif

template <class T>
constexpr
inline
T
reverse_bytes(T t)
{
    unsigned char* bytes = static_cast<unsigned char*>
                (std::memmove(std::addressof(t), std::addressof(t), sizeof(T)));
    for (unsigned i = 0; i < sizeof(T)/2; ++i)
        std::swap(bytes[i], bytes[sizeof(T)-1-i]);
    return t;
}

template <class T>
constexpr
inline
T
reverse_bytes_if(T t, std::true_type)
{
    return reverse_bytes(t);
}

template <class T>
constexpr
inline
T
reverse_bytes_if(T t, std::false_type)
{
    return t;
}

std::uint32_t
constexpr
inline
htonl(std::uint32_t x)
{
    return reverse_bytes_if(x, std::integral_constant<bool,
                               xstd::endian::native == xstd::endian::little>{});
}

std::uint16_t
constexpr
inline
htons(std::uint16_t x)
{
    return reverse_bytes_if(x, std::integral_constant<bool,
                               xstd::endian::native == xstd::endian::little>{});
}

std::uint32_t
constexpr
inline
ntohl(std::uint32_t x)
{
    return reverse_bytes_if(x, std::integral_constant<bool,
                               xstd::endian::native == xstd::endian::little>{});
}

std::uint16_t
constexpr
inline
ntohs(std::uint16_t x)
{
    return reverse_bytes_if(x, std::integral_constant<bool,
                               xstd::endian::native == xstd::endian::little>{});
}

template <class T,
          class = std::enable_if_t<std::is_integral<T>{}>
         >
constexpr
inline
T
hton(T t)
{
    return reverse_bytes_if(t, std::integral_constant<bool,
                               xstd::endian::native == xstd::endian::little>{});
}

template <class T,
          class = std::enable_if_t<std::is_integral<T>{}>
         >
constexpr
inline
T
ntoh(T t)
{
    return reverse_bytes_if(t, std::integral_constant<bool,
                               xstd::endian::native == xstd::endian::little>{});
}

#endif

int
test(int x)
{
    return htonl(x);
}

// int
// main()
// {
//     using namespace xstd;
//     if (endian::native == endian::little)
//         std::cout << "little endian\n";
//     else if (endian::native == endian::big)
//         std::cout << "little endian\n";
//     else
//         assert(false);
//     if (X::desired_endian != endian::native)
//         std::cout << "X needs work\n";
// }
