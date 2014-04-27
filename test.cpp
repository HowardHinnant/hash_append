//------------------------------- test.cpp -------------------------------------
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
#include "spooky.h"
#include "fnv1a.h"
#include "jenkins1.h"
#include "murmur2A.h"
#include "spooky.h"
#include "siphash.h"
#include "hash_functors.h"
#include "hash_adaptors.h"
#include "X.h"
#include "hash_test.h"

#include <iostream>
#include <chrono>
#include <set>

int
main()
{
    typedef std::chrono::duration<float> secs;
    std::set<mine::X> x;
    while (x.size() < 1000000)
        x.insert(mine::X{});
    std::vector<std::size_t> hashes;
    hashes.reserve(x.size());
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        for (auto const& i : x)
            hashes.push_back(std::hash<mine::X>{}(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "std::hash<X>> " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
    std::cout << '\n';
    hashes.clear();
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        for (auto const& i : x)
            hashes.push_back(hash_value(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "llvm::hash_value " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
    std::cout << '\n';
    hashes.clear();
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        xstd::uhash<acme::fnv1a> h;
        for (auto const& i : x)
            hashes.push_back(h(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "fnv1a " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
    std::cout << '\n';
    hashes.clear();
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        xstd::uhash<acme::jenkins1> h;
        for (auto const& i : x)
            hashes.push_back(h(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "jenkins1 " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
    std::cout << '\n';
    hashes.clear();
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        xstd::uhash<acme::MurmurHash2A> h;
        for (auto const& i : x)
            hashes.push_back(h(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "MurmurHash2A " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
    std::cout << '\n';
    hashes.clear();
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        xstd::uhash<acme::spooky> h;
        for (auto const& i : x)
            hashes.push_back(h(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "spooky " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
    std::cout << '\n';
    hashes.clear();
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        xstd::uhash<acme::siphash> h;
        for (auto const& i : x)
            hashes.push_back(h(i));
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "siphash " << '\n' << std::hex;
        std::cout << secs(t1-t0).count() << " s\n";
        std::cout << test1(hashes) << '\n';
        std::cout << test2(hashes) << '\n';
        std::cout << test3(hashes) << '\n';
        std::cout << test4(hashes) << '\n';
        std::cout << test5(hashes) << '\n';
    }
}
