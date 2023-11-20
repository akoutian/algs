// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "pq/index-min-pq.hxx"

#include <doctest/doctest.h>

#include <array>

namespace pq
{

template <typename T, size_t N>
std::array<T, N> generate_expected_test_array(const std::array<T, N> &a)
{
    auto t = a;
    std::sort(t.begin(), t.end());
    return t;
}

// TODO: extract common functions

//
// ------------- is_empty -------------
//

TEST_CASE("Test method \"is_empty\" - 1: initial queue is empty")
{
    index_min_pq<std::string> pq(0);

    CHECK(pq.is_empty());
}

TEST_CASE("Test method \"is_empty\" - 2: add one element and remove it")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_min();

    CHECK(pq.is_empty());
}

TEST_CASE("Test method \"is_empty\" - 3: add two elements and remove one")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);
    pq.remove_min();

    CHECK(!pq.is_empty());
}

TEST_CASE("Test method \"is_empty\" - 4: add two elements and remove both")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);
    pq.remove_min();
    pq.remove_min();

    CHECK(pq.is_empty());
}

//
// ------------- contains -------------
//

TEST_CASE("Test method \"contains\" - 1: invalid query: index equal to capacity")
{
    index_min_pq<std::string> pq(0);

    CHECK_THROWS_WITH_AS(pq.contains(0), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"contains\" - 2: invalid query: index exceeding capacity")
{
    index_min_pq<std::string> pq(0);

    CHECK_THROWS_WITH_AS(pq.contains(24), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"contains\" - 3: valid query - hit")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.contains(0));
}

TEST_CASE("Test method \"contains\" - 4: valid query - hit")
{
    index_min_pq<std::string> pq(13);

    pq.insert("foo", 4);

    CHECK(pq.contains(4));
}

TEST_CASE("Test method \"contains\" - 5: valid query - miss")
{
    index_min_pq<std::string> pq(9);

    pq.insert("foo", 0);

    CHECK(!pq.contains(5));
}

//
// ------------- size -------------
//

TEST_CASE("Test method \"size\" - 1")
{
    index_min_pq<std::string> pq(0);

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"size\" - 2")
{
    index_min_pq<std::string> pq(1);

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"size\" - 3")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.size() == 1);
}

TEST_CASE("Test method \"size\" - 4")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};

    index_min_pq<std::string> pq(v.size());

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    CHECK(pq.size() == v.size());
}

//
// ------------- insert -------------
//

TEST_CASE("Test method \"insert\" - 1: index already present")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.insert("bar", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is already in the priority queue.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"insert\" - 2: index equal to capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.insert("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"insert\" - 3: index exceeding capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.insert("bar", 5); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"insert\" - 4: indexes recover original keys")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};

    index_min_pq<std::string> pq(v.size());

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    CHECK(pq.size() == v.size());

    size_t jj{};
    for (const auto &s : v)
    {
        CHECK(pq.key_of(jj++) == s);
    }
}

//
// ------------- min_index -------------
//

TEST_CASE("Test method \"min_index\" - 1: min index is correct with one element")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.min_index() == 0);
}

TEST_CASE("Test method \"min_index\" - 2: min index is correct with two elements")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.min_index() == 1);
}

TEST_CASE("Test method \"min_index\" - 3: initially empty priority queue throws")
{
    index_min_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.min_index(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE(
    "Test method \"min_index\" - 4: priority queue throws after one insertion and one removal")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_min();

    const auto will_throw = [&]() { pq.min_index(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

//
// ------------- min_key -------------
//

TEST_CASE("Test method \"min_key\" - 1: min key is correct with one element")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.min_key() == "foo");
}

TEST_CASE("Test method \"min_key\" - 2: min key is correct with two elements")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.min_key() == "bar");
}

TEST_CASE("Test method \"min_key\" - 3: initially empty priority queue throws")
{
    index_min_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.min_key(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE("Test method \"min_key\" - 4: priority queue throws after one insertion and one removal")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_min();

    const auto will_throw = [&]() { pq.min_key(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

//
// ------------- remove_min -------------
//

TEST_CASE("Test method \"remove_min\" - 1: removed index is correct with one element")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.remove_min() == 0);
}

TEST_CASE("Test method \"min_key\" - 2: removed index is correct with two elements")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.remove_min() == 1);
    CHECK(pq.remove_min() == 0);
}

TEST_CASE("Test method \"remove_min\" - 3: initally empty priority queue throws")
{
    index_min_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.remove_min(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE(
    "Test method \"remove_min\" - 4: priority queue throws after one insertion and one removal")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_min();

    const auto will_throw = [&]() { pq.remove_min(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE("Test method \"remove_min\" - 5: check that keys are removed in increasing order")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};
    constexpr auto n = v.size();

    index_min_pq<std::string> pq(v.size());

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    const auto expected = generate_expected_test_array(v);
    for (size_t jj{}; jj < n; ++jj)
    {
        auto removed = pq.remove_min();
        CHECK(v[removed] == expected[jj]);
    }

    CHECK(pq.size() == 0);
}

//
// ------------- key_of -------------
//

TEST_CASE("Test method \"key_of\" - 1: key is correct with one element")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.key_of(0) == "foo");
}

TEST_CASE("Test method \"key_of\" - 2: key is correct with two elements")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.key_of(1) == "bar");
}

TEST_CASE("Test method \"key_of\" - 3: invalid query: index equal to capacity")
{
    index_min_pq<std::string> pq(1);

    const auto will_throw = [&]() { pq.key_of(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"key_of\" - 4: invalid query: index exceeding capacity")
{
    index_min_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.key_of(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"key_of\" - 5: invalid query: missing index")
{
    index_min_pq<std::string> pq(10);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    const auto will_throw = [&]() { pq.key_of(8); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

//
// ------------- change_key -------------
//

TEST_CASE("Test method \"change_key\" - 1: change one key")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.change_key("bar", 0);

    CHECK(pq.key_of(0) == "bar");
}

TEST_CASE("Test method \"change_key\" - 2: swap two keys")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    pq.change_key("bar", 0);
    pq.change_key("foo", 1);

    CHECK(pq.key_of(0) == "bar");
    CHECK(pq.key_of(1) == "foo");
}

TEST_CASE("Test method \"change_key\" - 3: reverse all keys")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};
    constexpr auto n = v.size();

    index_min_pq<std::string> pq(n);

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    size_t jj{n - 1};
    for (const auto &s : v)
    {
        pq.change_key(s, jj--);
    }

    size_t kk{n - 1};
    for (const auto &s : v)
    {
        CHECK(pq.key_of(kk--) == s);
    }
}

TEST_CASE("Test method \"change_key\" - 4: invalid query: index equal to capacity")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.change_key("bar", 2); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"change_key\" - 5: invalid query: index exceeding capacity")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.change_key("bar", 3); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"change_key\" - 6: invalid query: missing index")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.change_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

//
// ------------- decrease_key -------------
//

TEST_CASE("Test method \"decrease_key\" - 1: decrease one key")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.decrease_key("aoo", 0);

    CHECK(pq.key_of(0) == "aoo");
}

TEST_CASE("Test method \"decrease_key\" - 2: change the order of two keys")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.min_key() == "bar");

    pq.decrease_key("aoo", 0);

    CHECK(pq.min_key() == "aoo");

    CHECK(pq.key_of(0) == "aoo");
    CHECK(pq.key_of(1) == "bar");
}

TEST_CASE("Test method \"decrease_key\" - 3: invalid query: index equal to capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 4: invalid query: index exceeding capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("bar", 3); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 5: invalid query: missing index")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 6: invalid query: equal key")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("foo", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Given key is equal to the key already present.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 7: invalid query: key strictly greater")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("goo", 0); };

    CHECK_THROWS_WITH_AS(will_throw(),
                         "Given key is strictly greater than the key already present.",
                         const std::invalid_argument &);
}

//
// ------------- increase_key -------------
//

TEST_CASE("Test method \"increase_key\" - 1: increase one key")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.increase_key("goo", 0);

    CHECK(pq.key_of(0) == "goo");
}

TEST_CASE("Test method \"increase_key\" - 2: change the order of two keys")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.min_key() == "bar");

    pq.increase_key("gar", 1);

    CHECK(pq.min_key() == "foo");

    CHECK(pq.key_of(0) == "foo");
    CHECK(pq.key_of(1) == "gar");
}

TEST_CASE("Test method \"increase_key\" - 3: invalid query: index equal to capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 4: invalid query: index exceeding capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("bar", 2); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 5: invalid query: missing index")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 6: invalid query: equal key")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("foo", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Given key is equal to the key already present.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 7: invalid query: key strictly less")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("doo", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Given key is strictly less than the key already present.",
                         const std::invalid_argument &);
}

//
// ------------- remove -------------
//

TEST_CASE("Test method \"remove\" - 1: add one key and remove it")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.remove(0);

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"remove\" - 2: add multiple keys and remove one")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};
    constexpr auto n = v.size();

    index_min_pq<std::string> pq(v.size());

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    CHECK(pq.size() == n);

    pq.remove(4);

    CHECK(pq.size() == n - 1);
}

TEST_CASE("Test method \"remove\" - 3: add multiple keys and remove all of them")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};
    constexpr auto n = v.size();

    index_min_pq<std::string> pq(v.size());

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    for (size_t jj{}; jj < n; ++jj)
    {
        pq.remove(jj);
    }

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"remove\" - 4: invalid query: index equal to capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.remove(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"remove\" - 5: invalid query: index exceeding capacity")
{
    index_min_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.remove(3); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 6: invalid query: missing index")
{
    index_min_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.remove(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

} // namespace pq
