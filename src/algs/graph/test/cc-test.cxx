// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/cc.hxx"
#include "graph/edge.hxx"
#include "graph/graph.hxx"

#include <doctest/doctest.h>

namespace graph::cc
{

using graph = graph<edge>;

namespace
{

// TinyG.txt from "Algorithms, 4th Edition" by R. Sedgewick and K. Wayne (2011), chapter 4.1:
// "Undirected Graphs", page 545
graph build_test_graph()
{
    constexpr size_t v = 13;
    graph g(v);

    const auto edges = []()
    {
        std::vector<std::shared_ptr<edge>> e;
        e.reserve(v);
        e.push_back(std::make_shared<edge>(0, 1));
        e.push_back(std::make_shared<edge>(0, 2));
        e.push_back(std::make_shared<edge>(0, 5));
        e.push_back(std::make_shared<edge>(0, 6));
        e.push_back(std::make_shared<edge>(5, 3));
        e.push_back(std::make_shared<edge>(5, 4));
        e.push_back(std::make_shared<edge>(6, 4));
        e.push_back(std::make_shared<edge>(7, 8));
        e.push_back(std::make_shared<edge>(9, 10));
        e.push_back(std::make_shared<edge>(9, 11));
        e.push_back(std::make_shared<edge>(9, 12));
        e.push_back(std::make_shared<edge>(11, 12));
        return e;
    }();

    for (auto e : edges)
    {
        g.add_edge(e);
    }

    return g;
}

} // namespace

TEST_CASE("Test method \"count\"")
{
    const auto g = build_test_graph();

    cc cc(g);

    CHECK(cc.count() == 3);
}

TEST_CASE("Test method \"id\": 1 - valid queries")
{
    const auto g = build_test_graph();

    cc cc(g);

    CHECK(cc.id(0) == 0);
    CHECK(cc.id(1) == 0);
    CHECK(cc.id(2) == 0);
    CHECK(cc.id(3) == 0);
    CHECK(cc.id(4) == 0);
    CHECK(cc.id(5) == 0);
    CHECK(cc.id(6) == 0);
    CHECK(cc.id(7) == 1);
    CHECK(cc.id(8) == 1);
    CHECK(cc.id(9) == 2);
    CHECK(cc.id(10) == 2);
    CHECK(cc.id(11) == 2);
    CHECK(cc.id(12) == 2);
}

TEST_CASE("Test method \"id\": 2 - invalid query")
{
    const auto g = build_test_graph();

    cc cc(g);

    const auto will_throw = [&]() { [[maybe_unused]] const auto i = cc.id(51); };

    CHECK_THROWS_WITH_AS(will_throw(), "Vertex 51 is not between 0 and 12",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"size\": 1 - valid queries")
{
    const auto g = build_test_graph();

    cc cc(g);

    CHECK(cc.size(0) == 7);
    CHECK(cc.size(1) == 7);
    CHECK(cc.size(2) == 7);
    CHECK(cc.size(3) == 7);
    CHECK(cc.size(4) == 7);
    CHECK(cc.size(5) == 7);
    CHECK(cc.size(6) == 7);
    CHECK(cc.size(7) == 2);
    CHECK(cc.size(8) == 2);
    CHECK(cc.size(9) == 4);
    CHECK(cc.size(10) == 4);
    CHECK(cc.size(11) == 4);
    CHECK(cc.size(12) == 4);
}

TEST_CASE("Test method \"size\": 2 - invalid query")
{
    const auto g = build_test_graph();

    cc cc(g);

    const auto will_throw = [&]() { [[maybe_unused]] const auto s = cc.size(51); };

    CHECK_THROWS_WITH_AS(will_throw(), "Vertex 51 is not between 0 and 12",
                         const std::invalid_argument &);
}

TEST_CASE("Test method \"connected\": 1 - valid queries")
{
    const auto g = build_test_graph();

    cc cc(g);

    CHECK(cc.connected(0, 1));
    CHECK(cc.connected(1, 2));
    CHECK(cc.connected(2, 3));
    CHECK(cc.connected(3, 4));
    CHECK(cc.connected(4, 5));
    CHECK(cc.connected(5, 6));
    CHECK(!cc.connected(6, 7));
    CHECK(cc.connected(7, 8));
    CHECK(!cc.connected(8, 9));
    CHECK(cc.connected(9, 10));
    CHECK(cc.connected(10, 11));
    CHECK(cc.connected(11, 12));
}

TEST_CASE("Test method \"connected\": 2 - invalid query")
{
    const auto g = build_test_graph();

    cc cc(g);

    const auto will_throw = [&]() { [[maybe_unused]] const auto c = cc.connected(51, 2); };
    const auto will_also_throw = [&]() { [[maybe_unused]] const auto c = cc.connected(3, 89); };

    CHECK_THROWS_WITH_AS(will_throw(), "Vertex 51 is not between 0 and 12",
                         const std::invalid_argument &);
    CHECK_THROWS_WITH_AS(will_also_throw(), "Vertex 89 is not between 0 and 12",
                         const std::invalid_argument &);
}

} // namespace graph::cc
