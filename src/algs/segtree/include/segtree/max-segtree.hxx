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
template <typename T> class max_segtree
{
    using node = std::pair<T, size_t>;

  public:
    // Build a max segment tree from the contents of a vector.
    max_segtree(const std::vector<T> &values) : max_segtree(values, values.size())
    {
    }

    // Update the value at a given position to a new value.
    void update(size_t pos, T new_val)
    {
        update(1, 0, m_n - 1, pos, new_val);
    }

    // Retrieve the value at a specific position.
    T get(size_t pos)
    {
        return get(1, 0, m_n - 1, pos);
    }

    // Find the maximum element and the number of its occurences in the whole range.
    node get_max()
    {
        return get_max(1, 0, m_n - 1, 0, m_n - 1);
    }

    // Find the maximum element and the number of its occurences in a given interval [lo, hi].
    node get_max(size_t lo, size_t hi)
    {
        return get_max(1, 0, m_n - 1, lo, hi);
    }

  private:
    // The segment tree is a full binary tree, therefore it contains at most nmax = 2^(hmax + 1) - 1
    // nodes, where hmax is the maximum height, which will be floor(log2(n)), where n is the number
    // of elements in the array the tree represents. Therefore, the maximum number of nodes will be
    // less than 4*n, so we allocate this amount of memory.
    // NOTE: this could be a waste of memory in some cases.
    // TODO: optimise
    max_segtree(const std::vector<T> &values, size_t n) : m_tree(4 * n), m_n{n}
    {
        build(values, 1, 0, m_n - 1);
    }

    void build(const std::vector<T> &values, size_t v, size_t lo, size_t hi)
    {
        if (lo == hi)
        {
            m_tree[v] = std::make_pair(values[lo], 1);
        }
        else
        {
            const auto mid = (hi + lo) / 2;
            const auto left = 2 * v;
            const auto right = left + 1;

            build(values, left, lo, mid);
            build(values, right, mid + 1, hi);

            m_tree[v] = merge(m_tree[left], m_tree[right]);
        }
    }

    // Create a parent node from two children.
    node merge(const node &left, const node &right)
    {
        if (left.first > right.first)
        {
            return left;
        }
        else if (left.first < right.first)
        {
            return right;
        }

        return std::make_pair(left.first, left.second + right.second);
    }

    void update(size_t v, size_t lo, size_t hi, size_t pos, T new_val)
    {
        if (lo == hi)
        {
            m_tree[v] = std::make_pair(new_val, 1);
        }
        else
        {
            const auto mid = (lo + hi) / 2;
            const auto left = 2 * v;
            const auto right = left + 1;

            if (pos <= mid)
            {
                update(left, lo, mid, pos, new_val);
            }
            else
            {
                update(right, mid + 1, hi, pos, new_val);
            }

            m_tree[v] = merge(m_tree[left], m_tree[right]);
        }
    }

    T get(size_t v, size_t lo, size_t hi, size_t pos)
    {
        if (lo == pos && hi == pos)
        {
            return m_tree[v].first;
        }

        const auto mid = (lo + hi) / 2;
        const auto left = 2 * v;
        const auto right = left + 1;

        if (pos <= mid)
        {
            return get(left, lo, mid, pos);
        }

        return get(right, mid + 1, hi, pos);
    }

    node get_max(size_t v, size_t lo, size_t hi, size_t query_lo, size_t query_hi)
    {
        if (query_lo > query_hi)
        {
            return std::make_pair(std::numeric_limits<T>::min(), 0);
        }

        if (lo == query_lo && hi == query_hi)
        {
            return m_tree[v];
        }

        const auto mid = (lo + hi) / 2;
        const auto left = 2 * v;
        const auto right = left + 1;

        return merge(get_max(left, lo, mid, query_lo, std::min(query_hi, mid)),
                     get_max(right, mid + 1, hi, std::max(query_lo, mid + 1), query_hi));
    }

    std::vector<node> m_tree;
    size_t m_n;
};

} // namespace segtree
