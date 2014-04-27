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

#ifndef HANDLE_H
#define HANDLE_H

#include "hash_adaptors.h"

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class Handle
{
    struct CheshireCat;               // Not defined here
    CheshireCat* smile;               // Handle

public:
    Handle();                         // Default Constructor
    ~Handle();                        // Destructor
    Handle(Handle const&) = delete;
    Handle& operator=(Handle const&) = delete;
    Handle(int data1, int data2);
    // Other operations...

    // Hash support
    using type_erased_hasher = acme::type_erased_hasher<std::size_t>;

    friend
    void
    hash_append(type_erased_hasher&, CheshireCat const&);

    template <class Hasher>
    friend
    void
    hash_append(Hasher& h, Handle const& x)
    {
        using xstd::hash_append;
        if (x.smile == nullptr)
            hash_append(h, nullptr);
        else
        {
            type_erased_hasher temp(std::move(h));
            hash_append(temp, *x.smile);
            h = std::move(*temp.target<Hasher>());
        }
    }
};

}  // acme

#endif  // HANDLE_H
