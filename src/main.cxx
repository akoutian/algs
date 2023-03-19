// SPDX-License-Identifier: GPL-3.0-or-later

#include "slstack.hxx"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
    const std::vector<std::string> v{"to", "be", "or", "not", "to", "be"};

    SLStack<std::string> stack;

    std::for_each(v.begin(), v.end(),
                  [&](const auto &s)
                  {
                      stack.push(s);
                      std::cout << stack.size() << " " << stack.top() << std::endl;
                  });

    while (!stack.empty())
    {
        std::cout << stack.size() << " " << stack.pop() << std::endl;
    }

    return EXIT_SUCCESS;
}
