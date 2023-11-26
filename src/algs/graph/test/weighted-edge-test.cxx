// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/edge.hxx"

#include <doctest/doctest.h>

namespace graph::weighted
{

TEST_CASE("Test method \"weight\"")
{
    edge e{0, 1, 3.3};

    CHECK(e.weight() == 3.3);
}

TEST_CASE("Test method \"either\"")
{
    const size_t v = 0;
    const size_t w = 1;

    edge e{v, w, 3.3};

    CHECK((e.either() == v || e.either() == w));
}

TEST_CASE("Test method \"other\" - 1: valid query")
{
    const size_t v = 0;
    const size_t w = 1;

    edge e{v, w, 3.3};

    CHECK(e.other(v) == w);
    CHECK(e.other(w) == v);
}

TEST_CASE("Test method \"other\" - 2: invalid query")
{
    const size_t v = 0;
    const size_t w = 1;

    edge e{v, w, 3.3};

    CHECK_THROWS_WITH_AS(e.other(2), "Illegal vertex.", const std::invalid_argument &);
}

TEST_CASE("Test operator<")
{
    const size_t u = 0;
    const size_t v = 1;
    const size_t w = 2;

    edge e{v, w, 3.3};
    edge f{v, u, 3.2};
    edge g{w, u, 3.3};

    CHECK(f < e);
    CHECK(!(g < e));
}

} // namespace graph::weighted
