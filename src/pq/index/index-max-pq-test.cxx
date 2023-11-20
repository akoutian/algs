// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "index-max-pq.hxx"

#include <doctest/doctest.h>

#include <array>
#include <functional>

namespace pq
{

template <typename T, size_t N>
std::array<T, N> generate_expected_test_array(const std::array<T, N> &a)
{
    auto t = a;
    std::sort(t.begin(), t.end(), std::greater<T>());
    return t;
}

// TODO: extract common functions

//
// ------------- is_empty -------------
//

TEST_CASE("Test method \"is_empty\" - 1: initial queue is empty")
{
    index_max_pq<std::string> pq(0);

    CHECK(pq.is_empty());
}

TEST_CASE("Test method \"is_empty\" - 2: add one element and remove it")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_max();

    CHECK(pq.is_empty());
}

TEST_CASE("Test method \"is_empty\" - 3: add two elements and remove one")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);
    pq.remove_max();

    CHECK(!pq.is_empty());
}

TEST_CASE("Test method \"is_empty\" - 4: add two elements and remove both")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);
    pq.remove_max();
    pq.remove_max();

    CHECK(pq.is_empty());
}

//
// ------------- contains -------------
//

TEST_CASE("Test method \"contains\" - 1: invalid query: index equal to capacity")
{
    index_max_pq<std::string> pq(0);

    CHECK_THROWS_WITH_AS(pq.contains(0), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"contains\" - 2: invalid query: index exceeding capacity")
{
    index_max_pq<std::string> pq(0);

    CHECK_THROWS_WITH_AS(pq.contains(24), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"contains\" - 3: valid query - hit")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.contains(0));
}

TEST_CASE("Test method \"contains\" - 4: valid query - hit")
{
    index_max_pq<std::string> pq(13);

    pq.insert("foo", 4);

    CHECK(pq.contains(4));
}

TEST_CASE("Test method \"contains\" - 5: valid query - miss")
{
    index_max_pq<std::string> pq(9);

    pq.insert("foo", 0);

    CHECK(!pq.contains(5));
}

//
// ------------- size -------------
//

TEST_CASE("Test method \"size\" - 1")
{
    index_max_pq<std::string> pq(0);

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"size\" - 2")
{
    index_max_pq<std::string> pq(1);

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"size\" - 3")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.size() == 1);
}

TEST_CASE("Test method \"size\" - 4")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};

    index_max_pq<std::string> pq(v.size());

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
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.insert("bar", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is already in the priority queue.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"insert\" - 2: index equal to capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.insert("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"insert\" - 3: index exceeding capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.insert("bar", 5); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"insert\" - 4: indexes recover original keys")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};

    index_max_pq<std::string> pq(v.size());

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
// ------------- max_index -------------
//

TEST_CASE("Test method \"max_index\" - 1: max index is correct with one element")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.max_index() == 0);
}

TEST_CASE("Test method \"max_index\" - 2: max index is correct with two elements")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.max_index() == 0);
}

TEST_CASE("Test method \"max_index\" - 3: initially empty priority queue throws")
{
    index_max_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.max_index(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE(
    "Test method \"max_index\" - 4: priority queue throws after one insertion and one removal")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_max();

    const auto will_throw = [&]() { pq.max_index(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

//
// ------------- max_key -------------
//

TEST_CASE("Test method \"max_key\" - 1: max key is correct with one element")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.max_key() == "foo");
}

TEST_CASE("Test method \"max_key\" - 2: max key is correct with two elements")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.max_key() == "foo");
}

TEST_CASE("Test method \"max_key\" - 3: initially empty priority queue throws")
{
    index_max_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.max_key(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE("Test method \"max_key\" - 4: priority queue throws after one insertion and one removal")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_max();

    const auto will_throw = [&]() { pq.max_key(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

//
// ------------- remove_max -------------
//

TEST_CASE("Test method \"remove_max\" - 1: removed index is correct with one element")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.remove_max() == 0);
}

TEST_CASE("Test method \"max_key\" - 2: removed index is correct with two elements")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.remove_max() == 0);
    CHECK(pq.remove_max() == 1);
}

TEST_CASE("Test method \"remove_max\" - 3: initally empty priority queue throws")
{
    index_max_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.remove_max(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE(
    "Test method \"remove_max\" - 4: priority queue throws after one insertion and one removal")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);
    pq.remove_max();

    const auto will_throw = [&]() { pq.remove_max(); };

    CHECK_THROWS_WITH_AS(will_throw(), "Priority queue underflow.", const std::invalid_argument &);
}

TEST_CASE("Test method \"remove_max\" - 5: check that keys are removed in decreasing order")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};
    constexpr auto n = v.size();

    index_max_pq<std::string> pq(v.size());

    size_t ii{};
    for (const auto &s : v)
    {
        pq.insert(s, ii++);
    }

    const auto expected = generate_expected_test_array(v);
    for (size_t jj{}; jj < n; ++jj)
    {
        auto removed = pq.remove_max();
        CHECK(v[removed] == expected[jj]);
    }

    CHECK(pq.size() == 0);
}

//
// ------------- key_of -------------
//

TEST_CASE("Test method \"key_of\" - 1: key is correct with one element")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    CHECK(pq.key_of(0) == "foo");
}

TEST_CASE("Test method \"key_of\" - 2: key is correct with two elements")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.key_of(1) == "bar");
}

TEST_CASE("Test method \"key_of\" - 3: invalid query: index equal to capacity")
{
    index_max_pq<std::string> pq(1);

    const auto will_throw = [&]() { pq.key_of(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"key_of\" - 4: invalid query: index exceeding capacity")
{
    index_max_pq<std::string> pq(0);

    const auto will_throw = [&]() { pq.key_of(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"key_of\" - 5: invalid query: missing index")
{
    index_max_pq<std::string> pq(10);

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
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.change_key("bar", 0);

    CHECK(pq.key_of(0) == "bar");
}

TEST_CASE("Test method \"change_key\" - 2: swap two keys")
{
    index_max_pq<std::string> pq(2);

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

    index_max_pq<std::string> pq(n);

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
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.change_key("bar", 2); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"change_key\" - 5: invalid query: index exceeding capacity")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.change_key("bar", 3); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"change_key\" - 6: invalid query: missing index")
{
    index_max_pq<std::string> pq(2);

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
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.decrease_key("aoo", 0);

    CHECK(pq.key_of(0) == "aoo");
}

TEST_CASE("Test method \"decrease_key\" - 2: change the order of two keys")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.max_key() == "foo");

    pq.decrease_key("aoo", 0);

    CHECK(pq.max_key() == "bar");

    CHECK(pq.key_of(0) == "aoo");
    CHECK(pq.key_of(1) == "bar");
}

TEST_CASE("Test method \"decrease_key\" - 3: invalid query: index equal to capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 4: invalid query: index exceeding capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("bar", 3); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 5: invalid query: missing index")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 6: invalid query: equal key")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.decrease_key("foo", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Given key is equal to the key already present.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"decrease_key\" - 7: invalid query: key strictly greater")
{
    index_max_pq<std::string> pq(1);

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
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.increase_key("goo", 0);

    CHECK(pq.key_of(0) == "goo");
}

TEST_CASE("Test method \"increase_key\" - 2: change the order of two keys")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);
    pq.insert("bar", 1);

    CHECK(pq.max_key() == "foo");

    pq.increase_key("gar", 1);

    CHECK(pq.max_key() == "gar");

    CHECK(pq.key_of(0) == "foo");
    CHECK(pq.key_of(1) == "gar");
}

TEST_CASE("Test method \"increase_key\" - 3: invalid query: index equal to capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 4: invalid query: index exceeding capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("bar", 2); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 5: invalid query: missing index")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("bar", 1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 6: invalid query: equal key")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.increase_key("foo", 0); };

    CHECK_THROWS_WITH_AS(will_throw(), "Given key is equal to the key already present.",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 7: invalid query: key strictly less")
{
    index_max_pq<std::string> pq(1);

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
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    pq.remove(0);

    CHECK(pq.size() == 0);
}

TEST_CASE("Test method \"remove\" - 2: add multiple keys and remove one")
{
    static constexpr std::array<std::string, 10> v{"it",    "was", "the", "best", "of",
                                                   "times", "it",  "was", "the",  "worst"};
    constexpr auto n = v.size();

    index_max_pq<std::string> pq(v.size());

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

    index_max_pq<std::string> pq(v.size());

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
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.remove(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"remove\" - 5: invalid query: index exceeding capacity")
{
    index_max_pq<std::string> pq(1);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.remove(3); };

    CHECK_THROWS_WITH_AS(will_throw(), "index >= capacity", const std::invalid_argument &);
}

TEST_CASE("Test method \"increase_key\" - 6: invalid query: missing index")
{
    index_max_pq<std::string> pq(2);

    pq.insert("foo", 0);

    const auto will_throw = [&]() { pq.remove(1); };

    CHECK_THROWS_WITH_AS(will_throw(), "Index is not in the priority queue.",
                         const std::invalid_argument &);
}

} // namespace pq
