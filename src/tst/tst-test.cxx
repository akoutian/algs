// SPDX-License-Identifier: GPL-3.0-or-later

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "tst.hxx"

#include <doctest/doctest.h>

namespace tst
{

TEST_CASE("Test method \"size\"")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    CHECK(t.size() == 7);
}

TEST_CASE("Test method \"contains\" - I: valid query - hit")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto check = [&](const auto &s) { CHECK(t.contains(s)); };

    std::for_each(v.begin(), v.end(), check);
}

TEST_CASE("Test method \"contains\" - II: valid query - miss")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    CHECK(!t.contains("foobar"));
}

TEST_CASE("Test method \"contains\" - III: invalid query")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto will_throw = [&]() { [[maybe_unused]] const auto e = t.contains(""); };
    CHECK_THROWS_AS(will_throw(), const std::invalid_argument &);
}

TEST_CASE("Test method \"get\" - I: valid query - hit")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto check = [&](const auto &s) { CHECK(t.get(s)); };

    std::for_each(v.begin(), v.end(), check);
}

TEST_CASE("Test method \"get\" - II: valid query - miss")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    CHECK(!t.get("foobar"));
}

TEST_CASE("Test method \"get\" - III: invalid query")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto will_throw = [&]() { [[maybe_unused]] const auto e = t.get(""); };
    CHECK_THROWS_AS(will_throw(), const std::invalid_argument &);
}

TEST_CASE("Test method \"keys\"")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto result = t.keys();
    CHECK(result.size() == 7);

    const auto check = [&](const auto &s) { CHECK(std::find(v.begin(), v.end(), s) != v.end()); };

    std::for_each(result.begin(), result.end(), check);
}

TEST_CASE("Test method \"keys_with_prefix\" - I: valid query - hit")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto result = t.keys_with_prefix("sh");
    REQUIRE(result.size() == 2);
    CHECK(result[0] == "she");
    CHECK(result[1] == "shore");
}

TEST_CASE("Test method \"keys_with_prefix\" - II: valid query - miss")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto result = t.keys_with_prefix("foobar");
    CHECK(result.size() == 0);
}

TEST_CASE("Test method \"keys_with_prefix\" - III: invalid query")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto will_throw = [&]() { const auto e = t.keys_with_prefix(""); };

    CHECK_THROWS_AS(will_throw(), const std::invalid_argument &);
}

TEST_CASE("Test method \"longest_prefix_of\" - I: valid query - hit")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto result = t.longest_prefix_of("bystander");
    CHECK(result == "by");
}

TEST_CASE("Test method \"keys_with_prefix\" - II: valid query - miss")
{
    TST<size_t> t;

    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};
    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { t.put(s, ii++); });

    const auto result = t.longest_prefix_of("foobar");
    CHECK(result == "");
}

} // namespace tst
