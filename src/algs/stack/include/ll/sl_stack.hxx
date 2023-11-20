// SPDX-License-Identifier: GPL-3.0-or-later

#include <memory>
#include <stdexcept>

#pragma once

namespace ll
{

// stack implemented with a singly-linked list
template <typename T> class sl_stack
{
  public:
    sl_stack() : m_size{} {};

    bool empty()
    {
        return !m_top;
    }

    void push(const T &s)
    {
        auto first = std::make_shared<node>();
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
    struct node;
    std::shared_ptr<node> m_top;
    size_t m_size;
};

template <typename T> struct sl_stack<T>::node
{
    T s;
    std::shared_ptr<node> next;
};

} // namespace ll
