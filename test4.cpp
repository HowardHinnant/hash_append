#include "xx_hash.h"
#include "hash_append.h"
#include <iostream>

struct S
{
    char c;
    int x;
};

template <class HashAlgorithm>
void
hash_append(HashAlgorithm& h, const S& s)
{
    using xstd::hash_append;
    hash_append(h, s.c, s.x);
}

int
main()
{
    xstd::uhash<acme::xx_hash> my_hash;
    S s[10] = {'a', 1};
    std::cout << my_hash(s) << '\n';
}
