//------------------------------ hash_test.h -----------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef HASH_TEST_H
#define HASH_TEST_H

#include <vector>

float test1(std::vector<std::size_t> const& hashes);
float test2(std::vector<std::size_t> const& hashes);
float test3(std::vector<std::size_t> const& hashes);
float test4(std::vector<std::size_t> const& hashess, double lf = 1.0);
float test5(std::vector<std::size_t> const& hashess, double lf = 1.0);

#endif  // HASH_TEST_H
