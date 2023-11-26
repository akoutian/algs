// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cassert>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <vector>

namespace pq
{

template <typename Key> class index_max_pq
{
  public:
    // Initializes an empty indexed priority queue with indices between 0 and `size` - 1.
    index_max_pq(size_t capacity)
    {
        if (capacity < 0)
        {
            throw std::invalid_argument("Priority queue capacity cannot be negative.");
        }

        m_capacity = capacity;
        m_n = 0;
        // TODO: use unique pointers so we can actually free memory on deletion
        m_keys = std::vector<Key>(capacity + 1);
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

    // Associates `key` with `index`.
    void insert(Key key, size_t index)
    {
        throw_on_invalid_index(index);

        if (contains(index))
        {
            throw std::invalid_argument("Index is already in the priority queue.");
        }

        ++m_n;
        m_qp[index] = m_n;
        m_pq[m_n] = index;
        m_keys[index] = key;
        swim(m_n);
    }

    // Returns an index associated with a maximum key.
    size_t max_index() const
    {
        if (m_n == 0)
        {
            throw std::invalid_argument("Priority queue underflow.");
        }

        return m_pq[1];
    }

    Key max_key() const
    {
        if (m_n == 0)
        {
            throw std::invalid_argument("Priority queue underflow.");
        }

        return m_keys[m_pq[1]];
    }

    // Removes a maximum key and returns its associated index.
    size_t remove_max()
    {
        if (m_n == 0)
        {
            throw std::invalid_argument("Priority queue underflow.");
        }

        size_t max = m_pq[1];
        exch(1, m_n--);
        sink(1);
        assert(max == m_pq[m_n + 1]);
        // this deletes the max
        m_qp[max] = std::nullopt;
        return max;
    }

    Key key_of(size_t index) const
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        return m_keys[index];
    }

    // Changes the Key associated with `index` to the given `key`.
    void change_key(Key key, size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        m_keys[index] = key;
        swim(*m_qp[index]);
        sink(*m_qp[index]);
    }

    // Decreases the Key associated with `index` to the given `key`.
    void decrease_key(Key key, size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        if (m_keys[index] == key)
        {
            throw std::invalid_argument("Given key is equal to the key already present.");
        }

        if (m_keys[index] < key)
        {
            throw std::invalid_argument(
                "Given key is strictly greater than the key already present.");
        }

        m_keys[index] = key;
        sink(*m_qp[index]);
    }

    // Increases the Key associated with `index` to the given `key`.
    void increase_key(Key key, size_t index)
    {
        throw_on_invalid_index(index);

        if (!contains(index))
        {
            throw std::invalid_argument("Index is not in the priority queue.");
        }

        if (m_keys[index] == key)
        {
            throw std::invalid_argument("Given key is equal to the key already present.");
        }

        if (m_keys[index] > key)
        {
            throw std::invalid_argument("Given key is strictly less than the key already present.");
        }

        m_keys[index] = key;
        swim(*m_qp[index]);
    }

    // Removes the Key associated with `index`.
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
        while (k > 1 && less(k / 2, k))
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

            if (j < m_n && less(j, j + 1))
            {
                ++j;
            }

            if (!less(k, j))
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

    bool less(size_t i, size_t j) const
    {
        return m_keys[m_pq[i]] < m_keys[m_pq[j]];
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
    std::vector<Key> m_keys;
};

} // namespace pq
