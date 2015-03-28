//----------------------------------- X.h --------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef X_H
#define X_H

#include <tuple>
#include <vector>
#include <utility>
#include <random>

#include "hash_append.h"
#include "n3876.h"

// #include "../llvm/include/llvm/ADT/Hashing.h"

namespace mine
{

class X
{
//     std::tuple<short, unsigned char, unsigned char> date_;
//     std::vector<std::pair<int, int>>                data_;
    std::tuple<int, unsigned char, unsigned char> date_;
    std::vector<std::pair<int, short>>            data_;

public:
    X();
    // ...
    friend bool operator==(X const& x, X const& y)
    {
        return std::tie(x.date_, x.data_) == std::tie(y.date_, y.data_);
    }

    friend bool operator< (X const& x, X const& y)
    {
        return std::tie(x.date_, x.data_) < std::tie(y.date_, y.data_);
    }

    friend struct std::hash<X>;

//     friend
//     llvm::hash_code
//     hash_value(X const& x)
//     {
//         using llvm::hash_value;
//         return llvm::hash_combine
//             (
//                 hash_value(std::get<0>(x.date_)),
//                 hash_value(std::get<1>(x.date_)),
//                 hash_value(std::get<2>(x.date_)),
//                 llvm::hash_combine_range(x.data_.begin(), x.data_.end())
//             );
//     }

    template <class Hasher>
    friend
    void
    hash_append(Hasher& h, X const& x)
    {
        using xstd::hash_append;
        hash_append(h, x.date_);
    }
};

std::mt19937_64 eng;

X::X()
{
    std::uniform_int_distribution<short> yeardata(1914, 2014);
    std::uniform_int_distribution<unsigned char> monthdata(1, 12);
    std::uniform_int_distribution<unsigned char> daydata(1, 28);
    std::uniform_int_distribution<std::size_t> veclen(0, 100);
    std::uniform_int_distribution<int> int1data(1, 10);
    std::uniform_int_distribution<int> int2data(-3, 3);
    std::get<0>(date_) = yeardata(eng);
    std::get<1>(date_) = monthdata(eng);
    std::get<2>(date_) = daydata(eng);
    data_.resize(veclen(eng));
    for (auto& p : data_)
    {
        p.first = int1data(eng);
        p.second = int2data(eng);
    }
}

}  // mine

namespace std
{

template <>
struct hash<mine::X>
{
    size_t
    operator()(mine::X const& x) const noexcept
    {
        using namespace n3876;
        size_t h = hash<tuple_element<0, decltype(x.date_)>::type>{}(get<0>(x.date_));
        hash_combine(h, get<1>(x.date_), get<2>(x.date_));
        for (auto const& p : x.data_)
            hash_combine(h, p.first, p.second);
        return h;
    }
};

}  // std

#endif  // X_H
