//--------------------------- hash_functors.cpp --------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#include "hash_functors.h"

#include <random>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

namespace
{

std::tuple<std::uint64_t, std::uint64_t>
init_seeds()
{
    std::mt19937_64 eng{std::random_device{}()};
    return std::tuple<std::uint64_t, std::uint64_t>{eng(), eng()};
}

}   // unnamed

std::tuple<std::uint64_t, std::uint64_t>&
get_process_seed()
{
    static std::tuple<std::uint64_t, std::uint64_t> seeds = init_seeds();
    return seeds;
}

}  // acme
