//----------------------------- sherlock.cpp -----------------------------------
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
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <vector>
#include <chrono>
#include <numeric>

#include "../llvm/include/llvm/ADT/Hashing.h"

int
main()
{
    std::ifstream infile("sherlock.txt");
    std::istream_iterator<std::string> first(infile), eof;
    std::set<std::string> s;
    for (; first != eof; ++first)
    {
        std::string str = *first;
        str.erase(std::remove_if(str.begin(), str.end(), [](char c)
                                                         {
                                                            return !std::isalpha(c);
                                                         }), str.end());
        if (!str.empty())
            s.insert(str);
    }
    double avg = 0;
    for (auto const& str : s)
        avg += str.size();
    avg /= s.size();
    std::cout << "avg = " << avg << '\n';
#if 1
    xstd::uhash<acme::city> h;
#endif
    std::vector<std::size_t> hashes;
    hashes.reserve(s.size());
    typedef std::chrono::duration<float> secs;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (auto const& str : s)
#if 1
        hashes.push_back(h(str));
#else
        hashes.push_back(llvm::hash_value(str));
#endif
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << secs(t1-t0).count() << " s\n";
    std::cout << test4(hashes) << '\n';
    std::cout << test5(hashes) << '\n';
}

// avg = 7.08971

// llvm / N3333
// 0.000532726 s
// -0.00304038
// 7
// 
// xstd::uhash<acme::siphash>
// 0.000772055 s
// -0.00225346
// 7
// 
// xstd::uhash<acme::fnv1a>
// avg = 7.08971
// 0.000400899 s
// 0.00311192
// 6
