//------------------------------- murmur2A.h -----------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#ifndef MURMUR2A_H
#define MURMUR2A_H

#include <cstddef>

// namespace acme is used to demonstrate example code.  It is not proposed.

namespace acme
{

class MurmurHash2A
{
    unsigned int m_hash;
    unsigned int m_tail;
    unsigned int m_count;
    unsigned int m_size;

public:
    using result_type = unsigned int;

    MurmurHash2A ( unsigned int seed = 0 ) noexcept
        : m_hash{seed}
        , m_tail{0}
        , m_count{0}
        , m_size{0}
    {
    }

    void
    operator() ( const void* p, std::size_t len ) noexcept
    {
        const unsigned char* data = static_cast<const unsigned char*>(p);
        m_size += len;

        MixTail(data,len);

        while(len >= 4)
        {
            unsigned int k = *(unsigned int*)data;

            mmix(m_hash,k);

            data += 4;
            len -= 4;
        }

        MixTail(data,len);
    }

    explicit
    operator result_type () noexcept
    {
        mmix(m_hash,m_tail);
        mmix(m_hash,m_size);

        m_hash ^= m_hash >> 13;
        m_hash *= m;
        m_hash ^= m_hash >> 15;

        return m_hash;
    }

private:

    static const unsigned int m = 0x5bd1e995;
    static const int r = 24;

    static
    void
    mmix(unsigned int& h, unsigned int& k) noexcept
    {
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
    }


    void
    MixTail ( const unsigned char * & data, std::size_t & len ) noexcept
    {
        while( len && ((len<4) || m_count) )
        {
            m_tail |= (*data++) << (m_count * 8);

            m_count++;
            len--;

            if(m_count == 4)
            {
                mmix(m_hash,m_tail);
                m_tail = 0;
                m_count = 0;
            }
        }
    }
};

}  // acme

#endif  // MURMUR2A_H
