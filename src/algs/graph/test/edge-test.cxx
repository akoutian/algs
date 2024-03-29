// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "graph/edge.hxx"

#include <doctest/doctest.h>

#include <stdexcept>

namespace graph
{

TEST_CASE("Test method \"either\"")
{
    const size_t v = 0;
    const size_t w = 1;

    edge e{v, w};

    CHECK((e.either() == v || e.either() == w));
}

TEST_CASE("Test method \"other\" - 1: valid query")
{
    const size_t v = 0;
    const size_t w = 1;

    edge e{v, w};

    CHECK(e.other(v) == w);
    CHECK(e.other(w) == v);
}

TEST_CASE("Test method \"other\" - 2: invalid query")
{
    const size_t v = 0;
    const size_t w = 1;

    edge e{v, w};

    CHECK_THROWS_WITH_AS(e.other(2), "Illegal vertex.", const std::invalid_argument &);
}

TEST_CASE("Test operator==")
{
    const size_t u = 0;
    const size_t v = 1;
    const size_t w = 2;

    edge e{u, v};
    edge f{v, u};
    edge g{v, w};

    CHECK(e == f);
    CHECK(!(g == e));
}

} // namespace graph
