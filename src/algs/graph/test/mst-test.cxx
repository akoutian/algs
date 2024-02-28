// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/edge.hxx"
#include "graph/graph.hxx"
#include "graph/prim-mst.hxx"

#include <doctest/doctest.h>

namespace graph
{

void assert_edge_appears_once_in_mst(std::shared_ptr<weighted::edge> e,
                                     const std::vector<std::shared_ptr<weighted::edge>> &mst_edges)
{
    REQUIRE(e);

    const auto edge = *e;
    const auto predicate = [&](auto p) { return *p == edge; };

    const auto found = std::find_if(mst_edges.begin(), mst_edges.end(), predicate);
    const auto found_another = std::find_if(std::next(found), mst_edges.end(), predicate);

    CHECK(found != mst_edges.end());
    CHECK(found_another == mst_edges.end());
}

TEST_CASE("Obvious MST")
{
    graph<weighted::edge> g(2);

    const auto e = std::make_shared<weighted::edge>(0, 1, 1);

    g.add_edge(e);

    prim_mst<graph<weighted::edge>, weighted::edge> mst(g);
    CHECK(mst.weight() == 1);

    const auto mst_edges = mst.edges();
    REQUIRE(mst_edges.size() == 1);
    assert_edge_appears_once_in_mst(e, mst_edges);
}

TEST_CASE("Tiny MST from \"Algorithms, 4th Edition\" by R. Sedgewick and K. Wayne (2011), chapter "
          "4.3: \"Minimum Spanning Trees\", page 604")
{
    graph<weighted::edge> g(8);

    const auto edges = []()
    {
        std::vector<std::shared_ptr<weighted::edge>> e;
        e.reserve(16);
        e.push_back(std::make_shared<weighted::edge>(4, 5, 0.35));
        e.push_back(std::make_shared<weighted::edge>(4, 7, 0.37));
        e.push_back(std::make_shared<weighted::edge>(5, 7, 0.28));
        e.push_back(std::make_shared<weighted::edge>(0, 7, 0.16));
        e.push_back(std::make_shared<weighted::edge>(1, 5, 0.32));
        e.push_back(std::make_shared<weighted::edge>(0, 4, 0.38));
        e.push_back(std::make_shared<weighted::edge>(2, 3, 0.17));
        e.push_back(std::make_shared<weighted::edge>(1, 7, 0.19));
        e.push_back(std::make_shared<weighted::edge>(0, 2, 0.26));
        e.push_back(std::make_shared<weighted::edge>(1, 2, 0.36));
        e.push_back(std::make_shared<weighted::edge>(1, 3, 0.29));
        e.push_back(std::make_shared<weighted::edge>(2, 7, 0.34));
        e.push_back(std::make_shared<weighted::edge>(6, 2, 0.40));
        e.push_back(std::make_shared<weighted::edge>(3, 6, 0.52));
        e.push_back(std::make_shared<weighted::edge>(6, 0, 0.58));
        e.push_back(std::make_shared<weighted::edge>(6, 4, 0.93));
        return e;
    }();

    for (auto e : edges)
    {
        g.add_edge(e);
    }

    prim_mst<graph<weighted::edge>, weighted::edge> mst(g);
    CHECK(doctest::Approx(mst.weight()) == 1.81);

    const auto mst_edges = mst.edges();
    REQUIRE(mst_edges.size() == 7);

    assert_edge_appears_once_in_mst(edges[0], mst_edges);
    assert_edge_appears_once_in_mst(edges[2], mst_edges);
    assert_edge_appears_once_in_mst(edges[3], mst_edges);
    assert_edge_appears_once_in_mst(edges[6], mst_edges);
    assert_edge_appears_once_in_mst(edges[7], mst_edges);
    assert_edge_appears_once_in_mst(edges[8], mst_edges);
    assert_edge_appears_once_in_mst(edges[12], mst_edges);
}

} // namespace graph
