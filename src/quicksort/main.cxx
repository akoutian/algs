// SPDX-License-Identifier: GPL-3.0-or-later

#include "quicksort.hxx"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void print(const std::vector<std::string> &u)
{
    std::for_each(u.begin(), u.end(), [&](const auto &s) { std::cout << s; });
    std::cout << std::endl;
}

int main(void)
{
    std::vector<std::string> v;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty())
    {
        v.push_back(line);
    }

    print(v);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

    print(v);

    qs::sort(v);

    print(v);

    std::cout << "done" << std::endl;

    return EXIT_SUCCESS;
}
