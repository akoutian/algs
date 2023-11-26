// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "pq/index-min-pq.hxx"

#include <limits>
#include <memory>
#include <vector>

namespace mst
{

template <class Graph, class Edge> class prim_mst
{
  public:
    prim_mst(const Graph &graph) : prim_mst(graph, graph.v())
    {
    }

    std::vector<std::shared_ptr<Edge>> edges()
    {
        std::vector<std::shared_ptr<Edge>> result;

        for (size_t vv{}; vv < m_edge_to.size(); ++vv)
        {
            auto e = m_edge_to[vv];

            if (e != nullptr)
            {
                result.push_back(e);
            }
        }

        return result;
    }

    double weight()
    {
        double result{};
        for (auto e : edges())
        {
            result += e->weight();
        }

        return result;
    }

  private:
    prim_mst(const Graph &graph, size_t n)
        : m_dist_to(n, std::numeric_limits<double>::max()), m_marked(n), m_edge_to(n), m_pq(n)
    {
        for (size_t vv{}; vv < n; ++vv)
        {
            if (!m_marked[vv])
            {
                prim(graph, vv);
            }
        }

        // TODO: assert(check(graph));
    }

    // run Prim's algorithms in `graph` starting from the `source` vertex
    void prim(const Graph &graph, size_t source)
    {
        m_dist_to[source] = 0.0;
        m_pq.insert(m_dist_to[source], source);

        while (!m_pq.is_empty())
        {
            scan(graph, m_pq.remove_min());
        }
    }

    // scan vertex `v`
    void scan(const Graph &graph, size_t v)
    {
        m_marked[v] = true;

        for (auto e : graph.adj(v))
        {
            auto w = e->other(v);

            if (m_marked[w])
            {
                continue;
            }

            if (e->weight() < m_dist_to[w])
            {
                m_dist_to[w] = e->weight();
                m_edge_to[w] = e;

                if (m_pq.contains(w))
                {
                    m_pq.decrease_key(m_dist_to[w], w);
                }
                else
                {
                    m_pq.insert(m_dist_to[w], w);
                }
            }
        }
    }

    std::vector<double> m_dist_to;
    std::vector<bool> m_marked;
    std::vector<std::shared_ptr<Edge>> m_edge_to;
    pq::index_min_pq<double> m_pq;
};

} // namespace mst
