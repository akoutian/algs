// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdexcept>
#include <vector>

namespace graph
{

namespace cc
{

template <class graph> class cc
{
  public:
    // Computes the connected components of an undirected graph
    cc(const graph &g) : cc(g, g.v())
    {
    }

    // Returns the component identifier of the connected component containing a vertex.
    size_t id(size_t v)
    {
        throw_on_invalid_index(v);
        return m_id[v];
    }

    // Returns the number of vertices in the connected component containint a vertex.
    size_t size(size_t v)
    {
        throw_on_invalid_index(v);
        return m_size[m_id[v]];
    }

    // Returns the number of connected components in the graph.
    size_t count()
    {
        return m_count;
    }

    // Returns `true` if two vertices are in the same connected component.
    bool connected(size_t v, size_t w)
    {
        throw_on_invalid_index(v);
        throw_on_invalid_index(w);
        return m_id[v] == m_id[w];
    }

  private:
    cc(const graph &g, size_t v) : m_marked(v), m_id(v), m_size(v), m_count{}
    {
        if (g.is_directed())
        {
            throw std::invalid_argument("This algorithm does not work on directed graphs.");
        }

        for (size_t vv{}; vv < v; ++vv)
        {
            if (!m_marked[vv])
            {
                dfs(g, vv);
                ++m_count;
            }
        }
    }

    void dfs(const graph &g, size_t source)
    {
        m_marked[source] = true;
        m_id[source] = m_count;
        ++m_size[m_count];

        for (const auto e : g.adj(source))
        {
            const auto w = e->other(source);

            if (!m_marked[w])
            {
                dfs(g, w);
            }
        }
    }

    void throw_on_invalid_index(size_t v)
    {
        const auto n = m_marked.size();
        if (v > m_marked.size())
        {
            throw std::invalid_argument("Vertex " + std::to_string(v) + " is not between 0 and " +
                                        std::to_string(n - 1));
        }
    }

    std::vector<bool> m_marked;
    std::vector<size_t> m_id;
    std::vector<size_t> m_size;
    size_t m_count;
};

} // namespace cc

} // namespace graph
