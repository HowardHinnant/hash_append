//------------------------------- dates.cpp ------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

// The proposal
#include "hash_append.h"

// Example Hashers
#include "siphash.h"
#include "fnv1a.h"
#include "spooky.h"
#include "city_hash.h"

#include "hash_test.h"

#include <iostream>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <vector>
#include <chrono>
#include <numeric>

#include "../llvm/include/llvm/ADT/Hashing.h"

template <class Int>
inline
constexpr
bool
is_leap(Int y) noexcept
{
    return  y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

inline
constexpr
unsigned
last_day_of_month_common_year(unsigned m) noexcept
{
    constexpr unsigned char a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return a[m-1];
}

template <class Int>
inline
constexpr
unsigned
last_day_of_month(Int y, unsigned m) noexcept
{
    return m != 2 || !is_leap(y) ? last_day_of_month_common_year(m) : 29u;
}

int
main()
{
    typedef std::chrono::duration<float> secs;
    std::vector<std::size_t> hashes;
//     xstd::uhash<acme::spooky> h;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (short y = 1914; y < 2014; ++y)
    {
        for (unsigned char m = 1; m <= 12; ++m)
        {
            unsigned char l = last_day_of_month(y, m);
            for (unsigned char d = 1; d <= l; ++d)
            {
                auto date = std::make_tuple(y, m, d);
#if 1
//                 hashes.push_back(llvm::hash_combine(llvm::hash_value(std::get<0>(date)),
//                                                     llvm::hash_value(std::get<1>(date)),
//                                                     llvm::hash_value(std::get<2>(date))));
#elif 0
                hashes.push_back(h(date));
#endif
            }
        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << secs(t1-t0).count() << " s\n";
    std::cout << test2(hashes) << '\n';
    std::cout << test4(hashes) << '\n';
    std::cout << test5(hashes) << '\n';
}

// llvm
// 0.00127408 s
// 0
// 0.00214465
// 7

// siphash
// 0.00152026 s
// 0
// 0.0021629
// 7

// fnv1a
// 0.00068684 s
// 0
// -0.0923842
// 4

// spooky
// 0.00157705 s
// 0
// -0.00161533
// 7
