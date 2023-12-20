// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>
#include <vector>

namespace segtree
{

// TODO: implement minimum segtree and sum segtree

// The max segment tree stores values from a given std::vector. It allows updating the value at a
// given index and finding the maximum element in a given interval [a, b]. Performance is
// logarithmic.
// TODO: implement range checks for methods that accept indices
template <typename T> class add_max_segtree
{
  public:
    // Build a max segment tree representing the contents of a vector.
    add_max_segtree(const std::vector<T> &values) : add_max_segtree(values, values.size())
    {
    }

    // Add a value to the whole range.
    void add(T val)
    {
        constexpr size_t lo = 0;
        const auto hi = m_n - 1;
        add(1, lo, hi, lo, hi, val);
    }

    // Add a value to the value at a given position.
    void add(size_t pos, T new_val)
    {
        add(1, 0, m_n - 1, pos, pos, new_val);
    }

    // Add a value to a given interval [lo, hi].
    void add(size_t lo, size_t hi, T new_val)
    {
        add(1, 0, m_n - 1, lo, hi, new_val);
    }

    // Retrieve the value at a given position.
    T get(size_t pos)
    {
        return get(1, 0, m_n - 1, pos);
    }

    // Find the maximum element.
    T get_max()
    {
        constexpr size_t lo = 0;
        const auto hi = m_n - 1;
        return get_max(1, lo, hi, lo, hi);
    }

    // Find the maximum element in a given interval [lo, hi].
    T get_max(size_t lo, size_t hi)
    {
        return get_max(1, 0, m_n - 1, lo, hi);
    }

    size_t size()
    {
        return m_n;
    }

  private:
    // The segment tree is a full binary tree, therefore it contains at most nmax = 2^(hmax + 1) - 1
    // nodes, where hmax is the maximum height, which will be floor(log2(n)), where n is the number
    // of elements in the array the tree represents. Therefore, the maximum number of nodes will be
    // less than 4*n, so we allocate this amount of memory.
    // NOTE: this could be a waste of memory in some cases.
    // TODO: optimise
    add_max_segtree(const std::vector<T> &values, size_t n) : m_tree(4 * n), m_lazy(4 * n), m_n{n}
    {
        build(values, 1, 0, m_n - 1);
    }

    void build(const std::vector<T> &values, size_t v, size_t lo, size_t hi)
    {
        if (lo == hi)
        {
            m_tree[v] = values[lo];
            return;
        }

        const auto mid = (hi + lo) / 2;
        const auto left = 2 * v;
        const auto right = left + 1;

        build(values, left, lo, mid);
        build(values, right, mid + 1, hi);

        m_tree[v] = std::max(m_tree[left], m_tree[right]);
    }

    void push(size_t v)
    {
        const auto left = 2 * v;
        const auto right = left + 1;

        m_tree[left] += m_lazy[v];
        m_lazy[left] += m_lazy[v];

        m_tree[right] += m_lazy[v];
        m_lazy[right] += m_lazy[v];

        m_lazy[v] = 0;
    }

    void add(size_t v, size_t lo, size_t hi, size_t query_lo, size_t query_hi, T val)
    {
        if (query_lo > query_hi)
        {
            return;
        }

        if (lo == query_lo && hi == query_hi)
        {
            m_tree[v] += val;
            m_lazy[v] += val;
            return;
        }

        const auto mid = (hi + lo) / 2;
        const auto left = 2 * v;
        const auto right = left + 1;

        push(v);

        add(left, lo, mid, query_lo, std::min(mid, query_hi), val);
        add(right, mid + 1, hi, std::max(mid + 1, query_lo), query_hi, val);

        m_tree[v] = std::max(m_tree[left], m_tree[right]);
    }

    T get(size_t v, size_t lo, size_t hi, size_t pos)
    {
        if (lo == hi)
        {
            return m_tree[v];
        }

        const auto mid = (hi + lo) / 2;
        const auto left = 2 * v;
        const auto right = left + 1;

        push(v);

        if (pos <= mid)
        {
            return get(left, lo, mid, pos);
        }

        return get(right, mid + 1, hi, pos);
    }

    T get_max(size_t v, size_t lo, size_t hi, size_t query_lo, size_t query_hi)
    {
        if (query_lo > query_hi)
        {
            return std::numeric_limits<T>::min();
        }

        if (lo == query_lo && hi == query_hi)
        {
            return m_tree[v];
        }

        const auto mid = (hi + lo) / 2;
        const auto left = 2 * v;
        const auto right = left + 1;

        push(v);

        return std::max(get_max(left, lo, mid, query_lo, std::min(query_hi, mid)),
                        get_max(right, mid + 1, hi, std::max(query_lo, mid + 1), query_hi));
    }

    std::vector<T> m_tree;
    std::vector<T> m_lazy;
    size_t m_n;
};

} // namespace segtree
