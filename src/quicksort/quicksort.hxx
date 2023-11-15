// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>

namespace qs
{

namespace util
{

// deliberately not using std::swap
template <typename T> inline static void exch(T &a, size_t ii, size_t jj)
{
    auto v = a[ii];
    a[ii] = a[jj];
    a[jj] = v;
}

// deliberately not using std::partition
template <typename T> inline static size_t partition(T &a, size_t lo, size_t hi)
{
    size_t ii = lo;
    size_t jj = hi + 1;

    const auto v = a[lo];

    while (true)
    {
        while (a[++ii] < v)
        {
            if (ii == hi)
            {
                break;
            }
        }

        while (v < a[--jj])
        {
            if (jj == lo)
            {
                break;
            }
        }

        if (ii >= jj)
        {
            break;
        }

        exch(a, ii, jj);
    }

    exch(a, lo, jj);

    return jj;
}

template <typename T> inline static void sort(T &a, size_t lo, size_t hi)
{
    if (hi <= lo)
    {
        return;
    }

    size_t jj = partition(a, lo, hi);

    if (jj > 0)
    {
        sort(a, lo, jj - 1);
    }
    if (jj < std::numeric_limits<size_t>::max())
    {
        sort(a, jj + 1, hi);
    }

    assert(std::is_sorted(a.begin() + static_cast<long>(lo), a.end() + static_cast<long>(hi)));
}

} // namespace util

template <typename T> void sort(T &a)
{
    util::sort(a, 0, a.size() - 1);
    assert(std::is_sorted(a.begin(), a.end()));
}

} // namespace qs
