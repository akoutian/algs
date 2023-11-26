// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/bfs.hxx"
#include "graph/edge.hxx"
#include "graph/graph.hxx"

#include <doctest/doctest.h>

namespace graph::bfs
{

using graph = graph<edge>;

namespace
{

// Tiny BFS from "Algorithms, 4th Edition" by R. Sedgewick and K. Wayne (2011), chapter 4.1:
// "Undirected Graphs", page 538
graph build_test_graph()
{
    constexpr size_t v = 6;
    graph g(v);

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

TEST_CASE("Obvious BFS")
{
    graph g(2);

    const auto e = std::make_shared<edge>(0, 1);

    g.add_edge(e);

    bfs bfs(g, 0);

    CHECK(bfs.has_path_to(1));
    CHECK(bfs.dist_to(1) == 1);

    const auto path = bfs.path_to(1);
    REQUIRE(path.size() == 1);
    CHECK(path[0] == 1);
}

TEST_CASE("Check method \"has_path_to\"")
{
    const auto g = build_test_graph();

    bfs bfs(g, 0);

    for (size_t ii{}; ii < g.v(); ++ii)
    {
        CHECK(bfs.has_path_to(ii));
    }
}

TEST_CASE("Check method \"dist_to\"")
{
    const auto g = build_test_graph();

    bfs bfs(g, 0);

    CHECK(bfs.dist_to(0) == 0);

    CHECK(bfs.dist_to(1) == 1);
    CHECK(bfs.dist_to(2) == 1);
    CHECK(bfs.dist_to(5) == 1);

    CHECK(bfs.dist_to(3) == 2);
    CHECK(bfs.dist_to(4) == 2);
}

TEST_CASE("Check method \"path_to\"")
{
    const auto g = build_test_graph();

    bfs bfs(g, 0);

    const auto path1 = bfs.path_to(1);
    REQUIRE(path1.size() == 1);
    CHECK(path1[0] == 1);

    const auto path2 = bfs.path_to(2);
    REQUIRE(path2.size() == 1);
    CHECK(path2[0] == 2);

    const auto path5 = bfs.path_to(5);
    REQUIRE(path5.size() == 1);
    CHECK(path5[0] == 5);

    const auto path3 = bfs.path_to(3);
    REQUIRE(path3.size() == 2);
    CHECK(path3[0] == 3);
    CHECK(path3[1] == 2);

    const auto path4 = bfs.path_to(4);
    REQUIRE(path4.size() == 2);
    CHECK(path4[0] == 4);
    CHECK(path4[1] == 2);
}

// TODO: test multiple-source bfs

} // namespace graph::bfs
