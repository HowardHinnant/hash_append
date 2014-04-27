//-------------------------------- m16.cpp -------------------------------------
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
#include "city_hash.h"

#include "hash_test.h"

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <chrono>
#include <numeric>

#include "../llvm/include/llvm/ADT/Hashing.h"

int
main()
{
#if 0
    xstd::uhash<acme::fnv1a> h;
#else
    std::hash<unsigned long long> h;
#endif
    std::vector<std::size_t> hashes;
    hashes.reserve(1048576);
    typedef std::chrono::duration<float> secs;
    auto t0 = std::chrono::high_resolution_clock::now();
    unsigned long long x = 0;
    for (unsigned i = 0; i < hashes.capacity(); ++i, x += 16)
#if 1
        hashes.push_back(h(x));
#else
        hashes.push_back(llvm::hash_value(x));
#endif
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << secs(t1-t0).count() << " s\n";
    std::cout << test4(hashes) << '\n';
    std::cout << test5(hashes) << '\n';
}

// llvm / N3333
// 0.00994927 s
// -0.000307719
// 8
// 
// xstd::uhash<acme::siphash>
// 0.0331587 s
// 0.000118891
// 9
// 
// xstd::uhash<acme::fnv1a>
// 0.0142183 s
// -0.161947
// 3
// 
// std::hash<unsigned long long>
// 0.00767278 s
// 4.66667
// 16
