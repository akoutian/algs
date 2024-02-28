// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "radix/msd.hxx"

#include <doctest/doctest.h>

#include <random>

namespace radix
{

namespace
{

template <Integral T, size_t N> std::array<T, N> generate_test_array()
{
    std::mt19937 gen(2023);
    std::uniform_int_distribution<T> d(0, std::numeric_limits<T>::max());

    std::array<T, N> v;
    std::generate(v.begin(), v.end(), [&]() { return d(gen); });

    return v;
}

template <Integral T, size_t N>
std::array<T, N> generate_expected_test_array(const std::array<T, N> &a)
{
    auto t = a;
    std::sort(t.begin(), t.end());
    return t;
}

} // namespace

//
// ------------- char -------------
//

TEST_CASE("Test char array - 0")
{
    auto v = generate_test_array<char, 1>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 1")
{
    auto v = generate_test_array<char, 2>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 2")
{
    auto v = generate_test_array<char, 4>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 3")
{
    auto v = generate_test_array<char, 8>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 4")
{
    auto v = generate_test_array<char, 16>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 5")
{
    auto v = generate_test_array<char, 32>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 6")
{
    auto v = generate_test_array<char, 64>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 7")
{
    auto v = generate_test_array<char, 128>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 8")
{
    auto v = generate_test_array<char, 256>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 9")
{
    auto v = generate_test_array<char, 512>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 10")
{
    auto v = generate_test_array<char, 1024>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 11")
{
    auto v = generate_test_array<char, 2048>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 12")
{
    auto v = generate_test_array<char, 4096>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 13")
{
    auto v = generate_test_array<char, 8192>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 14")
{
    auto v = generate_test_array<char, 16384>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 15")
{
    auto v = generate_test_array<char, 32768>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test char array - 16")
{
    auto v = generate_test_array<char, 65536>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

//
// ------------- short -------------
//

TEST_CASE("Test short array - 0")
{
    auto v = generate_test_array<short, 1>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 1")
{
    auto v = generate_test_array<short, 2>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 2")
{
    auto v = generate_test_array<short, 4>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 3")
{
    auto v = generate_test_array<short, 8>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 4")
{
    auto v = generate_test_array<short, 16>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 5")
{
    auto v = generate_test_array<short, 32>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 6")
{
    auto v = generate_test_array<short, 64>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 7")
{
    auto v = generate_test_array<short, 128>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 8")
{
    auto v = generate_test_array<short, 256>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 9")
{
    auto v = generate_test_array<short, 512>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 10")
{
    auto v = generate_test_array<short, 1024>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 11")
{
    auto v = generate_test_array<short, 2048>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 12")
{
    auto v = generate_test_array<short, 4096>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 13")
{
    auto v = generate_test_array<short, 8192>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 14")
{
    auto v = generate_test_array<short, 16384>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 15")
{
    auto v = generate_test_array<short, 32768>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test short array - 16")
{
    auto v = generate_test_array<short, 65536>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

//
// ------------- int -------------
//

TEST_CASE("Test int array - 0")
{
    auto v = generate_test_array<int, 1>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 1")
{
    auto v = generate_test_array<int, 2>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 2")
{
    auto v = generate_test_array<int, 4>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 3")
{
    auto v = generate_test_array<int, 8>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 4")
{
    auto v = generate_test_array<int, 16>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 5")
{
    auto v = generate_test_array<int, 32>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 6")
{
    auto v = generate_test_array<int, 64>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 7")
{
    auto v = generate_test_array<int, 128>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 8")
{
    auto v = generate_test_array<int, 256>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 9")
{
    auto v = generate_test_array<int, 512>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 10")
{
    auto v = generate_test_array<int, 1024>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 11")
{
    auto v = generate_test_array<int, 2048>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 12")
{
    auto v = generate_test_array<int, 4096>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 13")
{
    auto v = generate_test_array<int, 8192>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 14")
{
    auto v = generate_test_array<int, 16384>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 15")
{
    auto v = generate_test_array<int, 32768>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test int array - 16")
{
    auto v = generate_test_array<int, 65536>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

//
// ------------- long -------------
//

TEST_CASE("Test long array - 0")
{
    auto v = generate_test_array<long, 1>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 1")
{
    auto v = generate_test_array<long, 2>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 2")
{
    auto v = generate_test_array<long, 4>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 3")
{
    auto v = generate_test_array<long, 8>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 4")
{
    auto v = generate_test_array<long, 16>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 5")
{
    auto v = generate_test_array<long, 32>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 6")
{
    auto v = generate_test_array<long, 64>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 7")
{
    auto v = generate_test_array<long, 128>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 8")
{
    auto v = generate_test_array<long, 256>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 9")
{
    auto v = generate_test_array<long, 512>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 10")
{
    auto v = generate_test_array<long, 1024>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 11")
{
    auto v = generate_test_array<long, 2048>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 12")
{
    auto v = generate_test_array<long, 4096>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 13")
{
    auto v = generate_test_array<long, 8192>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 14")
{
    auto v = generate_test_array<long, 16384>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 15")
{
    auto v = generate_test_array<long, 32768>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

TEST_CASE("Test long array - 16")
{
    auto v = generate_test_array<long, 65536>();
    const auto expected = generate_expected_test_array(v);

    msd(v);

    for (size_t ii{}; ii < v.size(); ++ii)
    {
        CHECK(v[ii] == expected[ii]);
    }
}

} // namespace radix
