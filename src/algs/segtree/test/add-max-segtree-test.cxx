// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "segtree/add-max-segtree.hxx"

#include <doctest/doctest.h>
#include <numeric>

TEST_CASE("Test method `get`")
{
    std::vector<int> values(7);
    std::iota(values.begin(), values.end(), 0);
    segtree::add_max_segtree st(values);

    for (size_t ii{}; ii < values.size(); ++ii)
    {
        CHECK(st.get(ii) == values[ii]);
    }
}

TEST_CASE("Test method `add`: 1 - update one element")
{
    std::vector<int> values(7);
    segtree::add_max_segtree st(values);

    st.add(2, 44);

    for (size_t ii{}; ii < 2; ++ii)
    {
        CHECK(st.get(ii) == values[ii]);
    }

    CHECK(st.get(2) == 44);

    for (size_t ii{3}; ii < values.size(); ++ii)
    {
        CHECK(st.get(ii) == values[ii]);
    }
}

TEST_CASE("Test method `add`: 2 - update multiple elements")
{
    std::vector<int> values(7);
    segtree::add_max_segtree st(values);

    st.add(2, 44);
    st.add(3, 44);
    st.add(5, 23);

    CHECK(st.get(0) == values[0]);
    CHECK(st.get(1) == values[1]);
    CHECK(st.get(2) == 44);
    CHECK(st.get(3) == 44);
    CHECK(st.get(4) == values[4]);
    CHECK(st.get(5) == 23);
    CHECK(st.get(6) == values[6]);
}

TEST_CASE("Test method `add`: 3 - large segtree")
{
    std::vector<int> values(1'000'000);
    segtree::add_max_segtree st(values);

    st.add(1'000, 800'000, 3);
    st.add(100, 500'000, 8);

    for (size_t ii{100}; ii < 1'000; ++ii)
    {
        CHECK(st.get(ii) == 8);
    }

    for (size_t ii{1'000}; ii <= 500'000; ++ii)
    {
        CHECK(st.get(ii) == 11);
    }

    for (size_t ii{500'001}; ii <= 800'000; ++ii)
    {
        CHECK(st.get(ii) == 3);
    }
}

TEST_CASE("Test method `get_max`: 1 - all elements equal")
{
    std::vector<int> values(7);
    segtree::add_max_segtree st(values);

    const auto max = st.get_max();

    CHECK(max == 0);
}

TEST_CASE("Test method `get_max`: 2 - all elements equal - subarrays")
{
    std::vector<int> values(7);
    segtree::add_max_segtree st(values);

    const auto max0 = st.get_max(0, 2);
    CHECK(max0 == 0);

    const auto max1 = st.get_max(4, 6);
    CHECK(max1 == 0);
}

TEST_CASE("Test method `get_max`: 3 - unique max")
{
    std::vector<int> values(7);
    std::iota(values.begin(), values.end(), 0);
    segtree::add_max_segtree st(values);

    CHECK(st.get_max() == 6);

    st.add(1);

    CHECK(st.get_max() == 7);
}

TEST_CASE("Test method `get_max`: 4 - unique max - subarrays")
{
    std::vector<int> values(7);
    std::iota(values.begin(), values.end(), 0);
    segtree::add_max_segtree st(values);

    const auto max0 = st.get_max(0, 2);
    CHECK(max0 == 2);

    const auto max1 = st.get_max(4, 6);
    CHECK(max1 == 6);
}

TEST_CASE("Test method `get_max`: 5 - multiple max")
{
    const std::vector<int> values{0, 7, 2, 7, 4, 5, 6};
    segtree::add_max_segtree st(values);

    const auto max = st.get_max();

    CHECK(max == 7);
}

TEST_CASE("Test method `get_max`: 6 - multiple max - subarrays")
{
    const std::vector<int> values{0, 7, 2, 7, 4, 5, 6};
    segtree::add_max_segtree st(values);

    const auto max0 = st.get_max(0, 3);
    CHECK(max0 == 7);

    const auto max1 = st.get_max(4, 6);
    CHECK(max1 == 6);
}

// TODO: "sliding window" tests would be cool
// TODO: test all methods
