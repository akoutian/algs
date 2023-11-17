#pragma once

#include <array>
#include <climits>
#include <cstddef>

namespace radix
{

namespace msd
{

namespace
{

template <typename T>
concept Integral = std::is_integral_v<T>;

template <Integral T, size_t N> inline T bin(size_t lo, const std::array<T, N> &array, size_t index)
{
    return lo + array[index];
}

// The radix i.e. number of possible values of one byte.
// The macro CHAR_WIDTH is used because a `char` is guaranteed by the C++
// standard to be represented by one byte.
static constexpr size_t R = 1 << CHAR_WIDTH;

// Extract the i-th byte from an integral type `a`.
// Example: consider the 32-bit integer a = 456789012:
//
//     |.......|.......|.......|.......
// a = 00011011001110100000110000010100
//
// The `shift` moves the desired byte all the way to the right:
//
// i = 0:
// shift(0) = 8*(4 - 1) = 24
//                 ------------------------|.......
// a >> shift(0) = 00000000000000000000000000011011
//
// i = 1:
// shift(1) = 8*(4 - 2) = 16
//                 ----------------|.......|.......
// a >> shift(1) = 00000000000000000001101100111010
//
// etc...
//
// Then, the `mask` zeroes out all the bits except those of the desired byte:
//                 ----------------|.......|.......
// a >> shift(1) = 00000000000000000001101100111010
//          mask = 00000000000000000000000011111111
//        result = 00000000000000000000000000111010
//
// We cast the result up to a size_t so it can easily be used as an index.
template <Integral T> inline size_t byte_at(T a, size_t index)
{
    const auto shift = CHAR_WIDTH * (sizeof(T) - index - 1);
    static const auto mask = static_cast<T>(R - 1);

    return static_cast<size_t>((a >> shift) & mask);
}

template <size_t R> inline size_t high(size_t lo, const std::array<size_t, R> &count, size_t index)
{
    auto o = bin(lo, count, index);
    return o > 0 ? o - 1 : 0;
}

template <Integral T, size_t N>
inline void msd(std::array<T, N> &items, size_t lo, size_t hi, size_t digit, std::array<T, N> &aux)
{
    std::array<size_t, R + 1> count{};

    if (digit > sizeof(T))
    {
        return;
    }

    if (hi <= lo)
    {
        return;
    }

    for (auto ii{lo}; ii <= hi; ++ii)
    {
        const auto b = byte_at(items[ii], digit);
        ++count[b + 1];
    }

    for (size_t jj{1}; jj < R; ++jj)
    {
        count[jj] += count[jj - 1];
    }

    for (auto ii{lo}; ii <= hi; ++ii)
    {
        const auto b = byte_at(items[ii], digit);
        aux[lo + count[b]++] = items[ii];
    }

    std::copy(aux.begin() + lo, aux.begin() + hi + 1, items.begin() + lo);

    msd(items, lo, high(lo, count, 0), digit + 1, aux);

    for (size_t jj{}; jj < R - 1; ++jj)
    {
        const auto low = bin(lo, count, jj);
        msd(items, low, high(lo, count, jj + 1), digit + 1, aux);
    }
}

} // namespace

// MSD radix sort for integral types
template <Integral T, size_t N> void msd(std::array<T, N> &items)
{
    auto aux = items;
    msd(items, 0, N - 1, 0, aux);
}

} // namespace msd

} // namespace radix
