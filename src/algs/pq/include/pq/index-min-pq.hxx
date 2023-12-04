// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cassert>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <vector>

namespace pq
{

template <typename key> class index_min_pq
{
  public:
    // Initializes an empty indexed priority queue with indices between 0 and `size` - 1.
    index_min_pq(size_t capacity)
    {
        if (capacity < 0)
        {
            throw std::invalid_argument("Priority queue capacity cannot be negative.");
        }

        m_capacity = capacity;
        m_n = 0;
        // TODO: use unique pointers so we can actually free memory on deletion
        m_keys = std::vector<key>(capacity + 1);
        m_pq = std::vector<size_t>(capacity + 1);
        m_qp = std::vector<std::optional<size_t>>(capacity + 1);
    }

    bool is_empty() const
    {
        return m_n == 0;
    }

    // Is `i` an index in this priority queue?
    bool contains(size_t index) const
    {
        throw_on_invalid_index(index);

        return m_qp[index] != std::nullopt;
    }

    size_t size() const
    {
        return m_n;
    }

    // Associates key `k` with `index`.
    void insert(key k, size_t index)
    {
        throw_on_invalid_index(index);

        if (contains(index))
        {
            throw std::invalid_argument("Index is already in the priority queue.");
        }

        ++m_n;
        m_qp[index] = m_n;
        m_pq[m_n] = index;
        m_keys[index] = k;
        swim(m_n);
    }

    // Returns an index associated with a minimum key.
    size_t min_index() const
    {
        if (m_n == 0)
        {
            throw std::invalid_argument("Priority queue underflow.");
        }

        return m_pq[1];
    }

    key min_key() const
    {
        if (m_n == 0)
        {
            throw std::invalid_argument("Priority queue underflow.");
        }

        return m_keys[m_pq[1]];
    }

    // Removes a minimum key and returns its associated index.
    size_t remove_min()
    {
        if (m_n == 0)
        {
            throw std::invalid_argument("Priority queue underflow.");
        }

        size_t min = m_pq[1];
        exch(1, m_n--);
        sink(1);
        assert(min == m_pq[m_n + 1]);
        // this deletes the min
        m_qp[min] = std::nullopt;
        return min;
    }

    key key_of(size_t index) const
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        return m_keys[index];
    }

    // Changes the key associated with `index` to the given key `k`.
    void change_key(key k, size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        m_keys[index] = k;
        swim(*m_qp[index]);
        sink(*m_qp[index]);
    }

    // Decreases the key associated with `index` to the given key `k`.
    void decrease_key(key k, size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        if (m_keys[index] == k)
        {
            throw std::invalid_argument("Given key is equal to the key already present.");
        }

        if (m_keys[index] < k)
        {
            throw std::invalid_argument(
                "Given key is strictly greater than the key already present.");
        }

        m_keys[index] = k;
        swim(*m_qp[index]);
    }

    // Increases the key associated with `index` to the given key `k`.
    void increase_key(key k, size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        if (m_keys[index] == k)
        {
            throw std::invalid_argument("Given key is equal to the key already present.");
        }

        if (m_keys[index] > k)
        {
            throw std::invalid_argument("Given key is strictly less than the key already present.");
        }

        m_keys[index] = k;
        sink(*m_qp[index]);
    }

    // Removes the key associated with `index`.
    void remove(size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        auto i = *m_qp[index];
        exch(i, m_n--);
        swim(i);
        sink(i);
        m_qp[index] = std::nullopt;
    }

  private:
    void swim(size_t k)
    {
        while (k > 1 && greater(k / 2, k))
        {
            exch(k, k / 2);
            k /= 2;
        }
    }

    void sink(size_t k)
    {
        while (2 * k <= m_n)
        {
            auto j = 2 * k;

            if (j < m_n && greater(j, j + 1))
            {
                ++j;
            }

            if (!greater(k, j))
            {
                break;
            }

            exch(k, j);

            k = j;
        }
    }

    void exch(size_t i, size_t j)
    {
        std::swap(m_pq[i], m_pq[j]);
        m_qp[m_pq[i]] = i;
        m_qp[m_pq[j]] = j;
    }

    bool greater(size_t i, size_t j) const
    {
        return m_keys[m_pq[i]] > m_keys[m_pq[j]];
    }

    void throw_on_invalid_index(size_t index) const
    {
        if (index >= m_capacity)
        {
            throw std::invalid_argument("index >= capacity");
        }
    }

    size_t m_n;
    size_t m_capacity;
    std::vector<size_t> m_pq;
    std::vector<std::optional<size_t>> m_qp;
    std::vector<key> m_keys;
};

} // namespace pq
