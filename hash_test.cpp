//----------------------------- hash_test.cpp ----------------------------------
// 
// This software is in the public domain.  The only restriction on its use is
// that no one can remove it from the public domain by claiming ownership of it,
// including the original authors.
// 
// There is no warranty of correctness on the software contained herein.  Use
// at your own risk.
// 
//------------------------------------------------------------------------------

#include "hash_test.h"
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include <set>
#include <cmath>
#include <cassert>

template <class T>
inline
T
sqr(T t)
{
    return t*t;
}

// what fraction can be hashed without collision?
float
test2 (std::vector<std::size_t> const& hashes)
{
    std::set<std::size_t> s(hashes.begin(), hashes.end());
    return 1 - static_cast<float>(s.size()) / hashes.size();
}

float
test1(std::vector<std::size_t> const& hashes)
{
    const unsigned nbits = CHAR_BIT * sizeof(std::size_t);
    const unsigned rows = nbits / 4;
    unsigned counts[rows][16] = {0};
    for (auto h : hashes)
    {
        std::size_t mask = 0xF;
        for (unsigned i = 0; i < rows; ++i, mask <<= 4)
            counts[i][(h & mask) >> 4*i] += 1;
    }
    float mean_rows[rows] = {0};
    float mean_cols[16] = {0};
    for (unsigned i = 0; i < rows; ++i)
    {
        for (unsigned j = 0; j < 16; ++j)
        {
            mean_rows[i] += counts[i][j];
            mean_cols[j] += counts[i][j];
        }
    }
    for (unsigned i = 0; i < rows; ++i)
        mean_rows[i] /= 16;
    for (unsigned j = 0; j < 16; ++j)
        mean_cols[j] /= rows;
//     for (unsigned i = 0; i < rows; ++i)
//     {
//         for (unsigned j = 0; j < 16; ++j)
//             std::cout << counts[i][j] << ' ';
//         std::cout << '\n';
//     }
//     std::cout << '\n';
//     for (unsigned i = 0; i < rows; ++i)
//         std::cout << mean_rows[i] << ' ';
//     std::cout << '\n';
//     for (unsigned j = 0; j < 16; ++j)
//         std::cout << mean_cols[j] << ' ';
//     std::cout << '\n';
    std::pair<float, float> dev[rows][16];
//     std::cout << std::fixed;
//     std::cout << std::setprecision(2);
    for (unsigned i = 0; i < rows; ++i)
    {
        for (unsigned j = 0; j < 16; ++j)
        {
            dev[i][j].first = std::abs(counts[i][j] - mean_rows[i]) / mean_rows[i];
            dev[i][j].second = std::abs(counts[i][j] - mean_cols[j]) / mean_cols[j];
        }
    }
    float max_err = 0;
    for (unsigned i = 0; i < rows; ++i)
    {
        for (unsigned j = 0; j < 16; ++j)
        {
//             std::cout << '{' << dev[i][j].first << ", " << dev[i][j].second << "} ";
            if (max_err < dev[i][j].first)
                max_err = dev[i][j].first;
            if (max_err < dev[i][j].second)
                max_err = dev[i][j].second;
        }
//         std::cout << '\n';
    }
//     std::cout << max_err << '\n';
    return max_err;
}

template <class T>
std::uint32_t
window (T* blob, int start, int count )
{
    std::size_t const len = sizeof(T);
    static_assert((len & 3) == 0, "");
    if(count == 0)
        return 0;
    int const nbits = len * CHAR_BIT;
    start %= nbits;
    int ndwords = len / 4;
    std::uint32_t const* k = static_cast<std::uint32_t const*>(static_cast<void const*>(blob));
    int c = start & (32-1);
    int d = start / 32;
    if(c == 0)
        return (k[d] & ((1 << count) - 1));
    int ia = (d + 1) % ndwords;
    int ib = (d + 0) % ndwords;
    std::uint32_t a = k[ia];
    std::uint32_t b = k[ib];
    std::uint32_t t = (a << (32-c)) | (b >> c);
    t &= ((1 << count)-1);
    return t;
}

double
calcScore (const int* bins, const std::size_t bincount, const double k)
{
    double const n = bincount;
    // compute rms^2 value
    double rms_sq = 0;
    for(std::size_t i = 0; i < bincount; ++i)
        rms_sq += sqr(bins[i]);;
    rms_sq /= n;
    // compute fill factor
    double const f = (sqr(k) - 1) / (n*rms_sq - k);
    // rescale to (0,1) with 0 = good, 1 = bad
    return 1 - (f / n);
}

namespace detail
{

inline
char
score2ascii (double n)
{
    char c = static_cast<char>(n);
    if (c == 0)
        c = '.';
    else if (c > 9)
        c = 'X';
    else
        c += '0';
    return c;
}

inline
double
clip (double n, double min, double max)
{
    if (n < min)
        return min;
    if (n > max)
        return max;
    return n;
}

}  // detail

float
test3 (std::vector<std::size_t> const& hashes)
{
    int maxwidth = 20;
    // We need at least 5 keys per bin to reliably test distribution biases
    // down to 1%, so don't bother to test sparser distributions than that
    while (static_cast<double>(hashes.size()) / (1 << maxwidth) < 5.0)
        maxwidth--;
    double worst = 0;
    int worstStart = -1;
    int worstWidth = -1;
    std::vector<int> bins (1 << maxwidth);
    int const hashbits = sizeof(std::size_t) * CHAR_BIT;
    for (int start = 0; start < hashbits; ++start)
    {
        int width = maxwidth;
        bins.assign (1 << width, 0);
        for (std::size_t j = 0; j < hashes.size(); ++j)
            ++bins[window(&hashes[j], start, width)];
        // Test the distribution, then fold the bins in half,
        // repeat until we're down to 256 bins
        while (bins.size() >= 256)
        {
            double score = calcScore(bins.data(), bins.size(), hashes.size());
            if (score > worst)
            {
                worst = score;
                worstStart = start;
                worstWidth = width;
            }
            if (--width < 8)
                break;
            for (std::size_t i = 0, j = bins.size() / 2; j < bins.size(); ++i, ++j)
                bins[i] += bins[j];
            bins.resize(bins.size() / 2);
        }
    }
    return worst;
}

float
test4(std::vector<std::size_t> const& hashes, double lf)
{
    assert(lf > 0);
    std::vector<std::size_t> b(static_cast<std::size_t>(hashes.size() / lf), 0);
    for (auto x : hashes)
        b[x % b.size()]++;
    double c = 0;
    for (auto x : b)
        c += x*(x+1)/2.;
    if (hashes.size() != 0)
        c /= hashes.size();
    return c / (lf/2 + 1) - 1;
}

float
test5(std::vector<std::size_t> const& hashes, double lf)
{
    assert(lf > 0);
    std::vector<std::size_t> b(static_cast<std::size_t>(hashes.size() / lf), 0);
    for (auto x : hashes)
        b[x % b.size()]++;
    std::size_t m = 0;
    for (auto x : b)
        m = std::max(m, x);
    return m;
}
