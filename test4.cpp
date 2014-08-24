#include "sha256.h"
#include "hash_append.h"
#include <iostream>
#include <iomanip>

int
main()
{
    xstd::uhash<acme::sha256> h;
    auto r = h(std::array<char, 4>{'a', 'b', 'c', 'd'});
    std::cout << std::hex;
    std::cout.fill('0');
    for (auto c : r)
        std::cout << std::setw(2) << (unsigned)c;
    std::cout << '\n';
}
