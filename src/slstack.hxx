// SPDX-License-Identifier: GPL-3.0-or-later

#include <memory>
#include <stdexcept>

#pragma once

namespace sls
{

template <typename T> class SLStack
{
  public:
    SLStack() : m_size{} {};

    bool empty()
    {
        return !m_top;
    }

    void push(const T &s)
    {
        auto first = std::make_shared<Node>();
        first->s = s;
        first->next = m_top;
        m_top = first;
        ++m_size;
    }

    T pop()
    {
        if (empty())
        {
            throw std::runtime_error("Empty stack.");
        }

        const auto result = m_top->s;
        m_top = m_top->next;
        --m_size;

        return result;
    }

    size_t size()
    {
        return m_size;
    }

    const T &top()
    {
        if (empty())
        {
            throw std::runtime_error("Empty stack.");
        }

        return m_top->s;
    }

  private:
    struct Node;
    std::shared_ptr<Node> m_top;
    size_t m_size;
};

template <typename T> struct SLStack<T>::Node
{
    T s;
    std::shared_ptr<Node> next;
};

} // namespace sls
