//-------------------------------- n3876.h -------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef N3876_H
#define N3876_H

#include <functional>

// This is an implementation of N3876 found at:
//   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3876.pdf

namespace n3876
{

inline
void
hash_combine (std::size_t&)
{
}

template <typename T>
inline
void
hash_combine (std::size_t& seed, const T& val)
{
    seed ^= std::hash<T>{}(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template <typename T, typename... Types>
inline
void
hash_combine (std::size_t& seed, const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_combine(seed, args...);
}

template <typename... Types>
inline
std::size_t
hash_val (const Types&... args)
{
    std::size_t seed = 0;
    hash_combine(seed, args...);
    return seed;
}

}  // n3876

#endif  // N3876_H
