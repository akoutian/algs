// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/dfs.hxx"
#include "graph/edge.hxx"
#include "graph/graph.hxx"

#include <doctest/doctest.h>

namespace graph
{

namespace
{

// Graph from "Algorithms, 4th Edition" by R. Sedgewick and K. Wayne (2011),
// chapter 4.1: "Undirected Graphs", page 538
graph<edge> build_test_graph()
{
    constexpr size_t v = 6;
    graph<edge> g(v);

    const auto edges = []()
    {
        std::vector<std::shared_ptr<edge>> e;
        e.reserve(v);
        e.push_back(std::make_shared<edge>(0, 1));
        e.push_back(std::make_shared<edge>(0, 2));
        e.push_back(std::make_shared<edge>(0, 5));
        e.push_back(std::make_shared<edge>(2, 1));
        e.push_back(std::make_shared<edge>(2, 3));
        e.push_back(std::make_shared<edge>(2, 4));
        e.push_back(std::make_shared<edge>(3, 4));
        e.push_back(std::make_shared<edge>(3, 5));
        return e;
    }();

    for (auto e : edges)
    {
        g.add_edge(e);
    }

    return g;
}

} // namespace

TEST_CASE("Obvious DFS")
{
    graph<edge> g(2);

    const auto e = std::make_shared<edge>(0, 1);

    g.add_edge(e);

    dfs dfs(g, 0);

    CHECK(dfs.has_path_to(1));

    const auto path = dfs.path_to(1);
    REQUIRE(path.size() == 2);
    CHECK(path[0] == 1);
    CHECK(path[1] == 0);
}

TEST_CASE("Check method \"has_path_to\"")
{
    const auto g = build_test_graph();

    dfs dfs(g, 0);

    // this graph is connected, so DFS must visit all vertices
    for (size_t ii{}; ii < g.v(); ++ii)
    {
        CHECK(dfs.has_path_to(ii));
    }
}

TEST_CASE("Check method \"path_to\"")
{
    const auto g = build_test_graph();

    dfs dfs(g, 0);

    const auto path1 = dfs.path_to(1);
    REQUIRE(path1.size() == 2);
    CHECK(path1[0] == 1);
    CHECK(path1[1] == 0);

    const auto path2 = dfs.path_to(2);
    REQUIRE(path2.size() == 3);
    CHECK(path2[0] == 2);
    CHECK(path2[1] == 1);
    CHECK(path2[2] == 0);

    const auto path5 = dfs.path_to(5);
    REQUIRE(path5.size() == 5);
    CHECK(path5[0] == 5);
    CHECK(path5[1] == 3);
    CHECK(path5[2] == 2);
    CHECK(path5[3] == 1);
    CHECK(path5[4] == 0);

    const auto path3 = dfs.path_to(3);
    REQUIRE(path3.size() == 4);
    CHECK(path3[0] == 3);
    CHECK(path3[1] == 2);
    CHECK(path3[2] == 1);
    CHECK(path3[3] == 0);

    const auto path4 = dfs.path_to(4);
    REQUIRE(path4.size() == 5);
    CHECK(path4[0] == 4);
    CHECK(path4[1] == 3);
    CHECK(path4[2] == 2);
    CHECK(path4[3] == 1);
    CHECK(path4[4] == 0);
}

} // namespace graph
