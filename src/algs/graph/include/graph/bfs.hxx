// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

namespace graph
{

namespace bfs
{

template <class graph> class bfs
{
  public:
    // Compute the shortest path between the `source` vertex and every
    // other vertex in the `graph`
    bfs(const graph &g, size_t source) : bfs(g.v(), source)
    {
        search(g, source);
        // TODO: assert(check(graph, source));
    }

    // Compute the shortest path between any of the `sources` and every other vertex in the `graph`
    bfs(const graph &g, const std::vector<size_t> &sources) : bfs(g.v(), sources)
    {
        search(g, sources);
        // TODO: assert(check(graph, source));
    }

    bool has_path_to(size_t v)
    {
        if (v > m_marked.size())
        {
            throw std::invalid_argument("Vertex " + std::to_string(v) + " is not between 0 and " +
                                        std::to_string(v - 1));
        }

        return m_marked[v];
    }

    size_t dist_to(size_t v)
    {
        if (v > m_marked.size())
        {
            throw std::invalid_argument("Vertex " + std::to_string(v) + " is not between 0 and " +
                                        std::to_string(v - 1));
        }

        return m_dist_to[v];
    }

    std::vector<size_t> path_to(size_t v)
    {
        if (v > m_marked.size())
        {
            throw std::invalid_argument("Vertex " + std::to_string(v) + " is not between 0 and " +
                                        std::to_string(v - 1));
        }

        if (!has_path_to(v))
        {
            return {};
        }

        std::vector<size_t> result;

        size_t x{v};
        while (m_dist_to[x] != 0)
        {
            result.push_back(x);
            x = m_edge_to[x];
        }
        result.push_back(x);

        return result;
    }

  private:
    bfs(size_t v, size_t source)
        : m_marked(v), m_edge_to(v), m_dist_to(v, std::numeric_limits<size_t>::max())
    {
        if (source > v)
        {
            throw std::invalid_argument("Vertex " + std::to_string(source) +
                                        " is not between 0 and " + std::to_string(v - 1));
        }
    }

    void search(const graph &g, size_t source)
    {
        std::queue<size_t> q;

        m_dist_to[source] = 0;
        m_marked[source] = true;
        q.push(source);

        search(g, q);
    }

    void search(const graph &g, const std::vector<size_t> &sources)
    {
        std::queue<size_t> q;

        for (auto s : sources)
        {
            m_dist_to[s] = 0;
            m_marked[s] = true;
            q.push(s);
        }

        search(g, q);
    }

    void search(const graph &g, std::queue<size_t> &q)
    {
        while (!q.empty())
        {
            const auto v = q.front();
            q.pop();

            for (auto e : g.adj(v))
            {
                const auto w = e->other(v);
                if (!m_marked[w])
                {
                    m_marked[w] = true;
                    m_edge_to[w] = v;
                    m_dist_to[w] = m_dist_to[v] + 1;
                    q.push(w);
                }
            }
        }
    }

    std::vector<bool> m_marked;
    std::vector<size_t> m_edge_to;
    std::vector<size_t> m_dist_to;
};

} // namespace bfs

} // namespace graph
