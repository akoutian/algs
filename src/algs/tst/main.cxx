// SPDX-License-Identifier: GPL-3.0-or-later

#include "tst.hxx"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
    const std::vector<std::string> v{"she", "sells", "seashells", "by", "the", "sea", "shore"};

    tst::TST<size_t> tst;

    size_t ii{};
    std::for_each(v.begin(), v.end(), [&](const auto &s) { tst.put(s, ii++); });

    const auto f = tst.keys();
    std::for_each(f.begin(), f.end(), [&](const auto &s) { std::cout << s << std::endl; });

    std::cout << std::boolalpha;
    std::for_each(v.begin(), v.end(),
                  [&](const auto &s) { std::cout << tst.contains(s) << std::endl; });
    std::cout << tst.contains("foobar") << std::endl;

    const auto k = tst.keys_with_prefix("sh");
    std::for_each(k.begin(), k.end(), [&](const auto &s) { std::cout << s << std::endl; });

    std::cout << tst.longest_prefix_of("shells") << std::endl;
    std::cout << tst.longest_prefix_of("sea") << std::endl;

    const auto l = tst.keys_that_match("s..");
    std::for_each(l.begin(), l.end(), [&](const auto &s) { std::cout << s << std::endl; });

    return EXIT_SUCCESS;
}
