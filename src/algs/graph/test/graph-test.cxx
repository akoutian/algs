// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/edge.hxx"
#include "graph/graph.hxx"

#include <doctest/doctest.h>

namespace graph::weighted
{

TEST_CASE("Test method \"v\"")
{
    graph<edge> g(2);

    CHECK(g.v() == 2);
}

TEST_CASE("Test method \"e\"")
{
    graph<edge> g(94);

    CHECK(g.e() == 0);
}

TEST_CASE("Test method \"add_edge\" - 1: two vertices, one edge")
{
    graph<edge> g(2);

    auto e = std::make_shared<edge>(0, 1, 0);

    g.add_edge(e);

    CHECK(g.e() == 1);

    auto a = g.adj(0);
    REQUIRE(g.degree(0) == 1);
    REQUIRE(a.size() == 1);
    CHECK(a[0]->other(0) == 1);

    auto b = g.adj(1);
    REQUIRE(g.degree(1) == 1);
    REQUIRE(b.size() == 1);
    CHECK(b[0]->other(1) == 0);
}

TEST_CASE("Test method \"add_edge\" - 2: three vertices, two edges")
{
    graph<edge> g(3);

    auto e1 = std::make_shared<edge>(0, 1, 0);
    auto e2 = std::make_shared<edge>(1, 2, 0);

    g.add_edge(e1);
    g.add_edge(e2);

    CHECK(g.e() == 2);

    auto a = g.adj(0);
    REQUIRE(g.degree(0) == 1);
    REQUIRE(a.size() == 1);
    CHECK(a[0]->other(0) == 1);

    auto b = g.adj(1);
    REQUIRE(g.degree(1) == 2);
    REQUIRE(b.size() == 2);
    CHECK(b[0]->other(1) == 0);
    CHECK(b[1]->other(1) == 2);

    auto c = g.adj(2);
    REQUIRE(g.degree(2) == 1);
    REQUIRE(c.size() == 1);
    CHECK(c[0]->other(2) == 1);
}

TEST_CASE("Test method \"add_edge\" - 3: three vertices, three edges (cycle)")
{
    graph<edge> g(3);

    auto e1 = std::make_shared<edge>(0, 1, 0);
    auto e2 = std::make_shared<edge>(1, 2, 0);
    auto e3 = std::make_shared<edge>(2, 0, 0);

    g.add_edge(e1);
    g.add_edge(e2);
    g.add_edge(e3);

    CHECK(g.e() == 3);

    auto a = g.adj(0);
    REQUIRE(g.degree(0) == 2);
    REQUIRE(a.size() == 2);
    CHECK(a[0]->other(0) == 1);
    CHECK(a[1]->other(0) == 2);

    auto b = g.adj(1);
    REQUIRE(g.degree(1) == 2);
    REQUIRE(b.size() == 2);
    CHECK(b[0]->other(1) == 0);
    CHECK(b[1]->other(1) == 2);

    auto c = g.adj(2);
    REQUIRE(g.degree(2) == 2);
    REQUIRE(c.size() == 2);
    CHECK(c[0]->other(2) == 1);
    CHECK(c[1]->other(2) == 0);
}

TEST_CASE("Test method \"add_edge\" - 4: two vertices, one directed edge")
{
    graph<edge> g(2, true);
    REQUIRE(g.is_directed());

    auto e = std::make_shared<edge>(0, 1, 0);

    g.add_edge(e);

    CHECK(g.e() == 1);

    auto a = g.adj(0);
    REQUIRE(g.degree(0) == 1);
    REQUIRE(a.size() == 1);
    CHECK(a[0]->other(0) == 1);

    auto b = g.adj(1);
    REQUIRE(g.degree(1) == 0);
    REQUIRE(b.size() == 0);
}

TEST_CASE("Test method \"add_edge\" - 5: three vertices, two directed edges")
{
    graph<edge> g(3, true);
    REQUIRE(g.is_directed());

    auto e1 = std::make_shared<edge>(0, 1, 0);
    auto e2 = std::make_shared<edge>(1, 2, 0);

    g.add_edge(e1);
    g.add_edge(e2);

    CHECK(g.e() == 2);

    auto a = g.adj(0);
    REQUIRE(g.degree(0) == 1);
    REQUIRE(a.size() == 1);
    CHECK(a[0]->other(0) == 1);

    auto b = g.adj(1);
    REQUIRE(g.degree(1) == 1);
    REQUIRE(b.size() == 1);
    CHECK(b[0]->other(1) == 2);

    auto c = g.adj(2);
    REQUIRE(g.degree(2) == 0);
    REQUIRE(c.size() == 0);
}

TEST_CASE("Test method \"add_edge\" - 6: three vertices, three edges (directed cycle)")
{
    graph<edge> g(3, true);
    REQUIRE(g.is_directed());

    auto e1 = std::make_shared<edge>(0, 1, 0);
    auto e2 = std::make_shared<edge>(1, 2, 0);
    auto e3 = std::make_shared<edge>(2, 0, 0);

    g.add_edge(e1);
    g.add_edge(e2);
    g.add_edge(e3);

    CHECK(g.e() == 3);

    auto a = g.adj(0);
    REQUIRE(g.degree(0) == 1);
    REQUIRE(a.size() == 1);
    CHECK(a[0]->other(0) == 1);

    auto b = g.adj(1);
    REQUIRE(g.degree(1) == 1);
    REQUIRE(b.size() == 1);
    CHECK(b[0]->other(1) == 2);

    auto c = g.adj(2);
    REQUIRE(g.degree(2) == 1);
    REQUIRE(c.size() == 1);
    CHECK(b[0]->other(2) == 1);
}

TEST_CASE("Test method \"edges\"")
{
    graph<edge> g(3);

    auto e1 = std::make_shared<edge>(0, 1, 0);
    auto e2 = std::make_shared<edge>(1, 2, 0);
    auto e3 = std::make_shared<edge>(2, 0, 0);

    g.add_edge(e1);
    g.add_edge(e2);
    g.add_edge(e3);

    CHECK(g.e() == 3);
    auto e = g.edges();
    REQUIRE(e.size() == 3);
}

} // namespace graph::weighted
