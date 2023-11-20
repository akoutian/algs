#pragma once

#include <cstddef>
#include <stdexcept>

namespace graph
{

namespace weighted
{

class edge
{
  public:
    edge(size_t v, size_t w, double weight) : m_v{v}, m_w{w}, m_weight{weight}
    {
    }

    double weight() const
    {
        return m_weight;
    }

    size_t either() const
    {
        return m_v;
    }

    size_t other(size_t vertex) const
    {
        if (vertex == m_v)
        {
            return m_w;
        }
        else if (vertex == m_w)
        {
            return m_v;
        }

        throw std::invalid_argument("Illegal vertex.");
    }

    friend bool operator<(const edge &lhs, const edge &rhs)
    {
        return lhs.m_weight < rhs.m_weight;
    }

    friend bool operator==(const edge &lhs, const edge &rhs)
    {
        auto a = (lhs.m_v == rhs.m_v && lhs.m_w == rhs.m_w);
        auto b = (lhs.m_v == rhs.m_w && lhs.m_w == rhs.m_v);

        return (a || b) && lhs.m_weight == rhs.m_weight;
    }

  private:
    size_t m_v;
    size_t m_w;
    double m_weight;
};

} // namespace weighted

} // namespace graph
