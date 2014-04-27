//------------------------------- pairii.cpp -----------------------------------
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
#include "spooky.h"

#include "hash_test.h"

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <chrono>
#include <numeric>
#include <random>

#include "n3876.h"
#include "../llvm/include/llvm/ADT/Hashing.h"

int
main()
{
#if 0
    xstd::uhash<acme::spooky> h;
#elif 1
    std::mt19937_64 eng;
#else
    std::hash<unsigned long long> h;
#endif
    std::vector<std::size_t> hashes;
    hashes.reserve(1048576);
    typedef std::chrono::duration<float> secs;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < 1024; ++i)
        for (unsigned j = 0; j < 1024; ++j)
#if 0
            hashes.push_back(h(std::make_pair(i, j)));
#elif 0
            hashes.push_back(n3876::hash_val(i, j));
#elif 1
            hashes.push_back(eng());
#else
            hashes.push_back(llvm::hash_value(std::make_pair(i, j)));
#endif
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << secs(t1-t0).count() << " s\n";
    std::cout << test4(hashes) << '\n';
    std::cout << test5(hashes) << '\n';
}

// llvm / N3333
// 0.00886668 s
// -0.000547409
// 9
// 
// xstd::uhash<acme::siphash>
// 0.0332836 s
// 0.000781377
// 9
// 
// xstd::uhash<acme::fnv1a>
// 0.011603 s
// -0.0115
// 4
// 
// n3876::hash_val(i, j)
// 0.00748404 s
// 4.75246
// 33
// 
// xstd::uhash<acme::spooky>
// 0.0265555 s
// -8.90096e-06
// 9
//
// random hash
// 0.0128204 s
// 0.000203451
// 8
