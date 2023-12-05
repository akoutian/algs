// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

namespace graph
{

namespace dfs
{

template <class graph> class dfs
{
  public:
    // Computes a path between s and every other vertex in the `graph`
    dfs(const graph &g, size_t source) : dfs(g.v(), source)
    {
        search(g, source);
    }

    bool has_path_to(size_t v)
    {
        throw_on_invalid_vertex(v);
        return m_marked[v];
    }

    std::vector<size_t> path_to(size_t v)
    {
        throw_on_invalid_vertex(v);

        std::vector<size_t> result;

        if (!has_path_to(v))
        {
            return result;
        }

        for (size_t x = v; x != m_s; x = m_edge_to[x])
        {
            result.push_back(x);
        }
        result.push_back(m_s);

        return result;
    }

  private:
    dfs(size_t v, size_t s) : m_marked(v), m_edge_to(v), m_s{s}
    {
    }

    void search(const graph &g, size_t s)
    {
        m_marked[s] = true;

        for (auto e : g.adj(s))
        {
            const auto w = e->other(s);
            if (!m_marked[w])
            {
                m_marked[w] = true;
                m_edge_to[w] = s;
                search(g, w);
            }
        }
    }

    void throw_on_invalid_vertex(size_t v)
    {
        if (v > m_marked.size())
        {
            throw std::invalid_argument("Vertex " + std::to_string(v) + " is not between 0 and " +
                                        std::to_string(v - 1));
        }
    }

    std::vector<bool> m_marked;
    std::vector<size_t> m_edge_to;
    size_t m_s;
};

} // namespace dfs

} // namespace graph
