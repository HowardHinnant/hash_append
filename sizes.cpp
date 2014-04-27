//------------------------------- sizes.cpp ------------------------------------
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

#include <iostream>
int
main()
{
    std::cout << sizeof(acme::siphash) << '\n';
    std::cout << sizeof(acme::spooky) << '\n';
    std::cout << sizeof(acme::fnv1a) << '\n';
}

// 48
// 304
// 8
