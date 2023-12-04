// SPDX-License-Identifier: GPL-3.0-or-later

#include <memory>
#include <vector>

namespace graph
{

enum class direction
{
    undirected,
    directed
};

template <class edge> class graph
{
  public:
    // Initialises an empty graph with `v` vertices and 0 edges.
    graph(size_t v, direction d = direction::undirected) : m_v{v}, m_e{}, m_direction{d}, m_adj(v)
    {
    }

    size_t v() const
    {
        return m_v;
    }

    size_t e() const
    {
        return m_e;
    }

    bool is_directed() const
    {
        return m_direction == direction::directed;
    }

    void add_edge(std::shared_ptr<edge> e)
    {
        auto v = e->either();
        auto w = e->other(v);

        m_adj.at(v).push_back(e);

        if (m_direction == direction::undirected)
        {
            m_adj.at(w).push_back(e);
        }

        ++m_e;
    }

    std::vector<std::shared_ptr<edge>> adj(size_t v) const
    {
        return m_adj.at(v);
    }

    size_t degree(size_t v) const
    {
        return m_adj.at(v).size();
    }

    std::vector<std::shared_ptr<edge>> edges() const
    {
        std::vector<std::shared_ptr<edge>> result;
        result.reserve(m_e);

        for (size_t vv{}; vv < m_v; ++vv)
        {
            size_t self_loops{};

            for (auto e : adj(vv))
            {
                if (e->other(vv) > vv)
                {
                    result.push_back(e);
                }
                else if (e->other(vv) == vv)
                {
                    if (self_loops % 2 == 0)
                    {
                        result.push_back(e);
                        ++self_loops;
                    }
                }
            }
        }

        return result;
    }

  private:
    size_t m_v;
    size_t m_e;
    direction m_direction;
    std::vector<std::vector<std::shared_ptr<edge>>> m_adj;
};

} // namespace graph
