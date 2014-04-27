//------------------------------- test2.cpp ------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#include "X.h"
#include "fnv1a.h"
#include <cassert>

std::size_t
hash_contiguous(int (&data)[3])
{
    acme::fnv1a h;
    h(data, sizeof(data));
    return static_cast<std::size_t>(h);
}

std::size_t
hash_discontiguous(int data1, int data2, int data3)
{
    acme::fnv1a h;
    h(&data1, sizeof(data1));
    h(&data2, sizeof(data2));
    h(&data3, sizeof(data3));
    return static_cast<std::size_t>(h);
}

int
main()
{
    int data[] = {5, 3, 8};
    assert((hash_contiguous(data) == hash_discontiguous(5, 3, 8)));
}
