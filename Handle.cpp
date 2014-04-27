//------------------------------- Handle.h -------------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#include "hash_append.h"
#include "Handle.h"
#include <unordered_set>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class Handle::CheshireCat
{
    std::unordered_set<int> data_;
public:
    CheshireCat(int data1, int data2)
    {
        data_.insert(data1);
        data_.insert(data2);
    }

    friend
    void
    hash_append(Handle::type_erased_hasher& h, CheshireCat const& c);
};

void
hash_append(Handle::type_erased_hasher& h, Handle::CheshireCat const& c)
{
    using xstd::hash_append;
    hash_append(h, c.data_);
}

Handle::Handle()
    : smile(new CheshireCat(1, 2))
{
}

Handle::Handle(int data1, int data2)
    : smile(new CheshireCat(data1, data2))
{
}

Handle::~Handle()
{
    delete smile;
}

}  // acme
