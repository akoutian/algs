#pragma once

#include <memory>
#include <stdexcept>

namespace st
{

// sequential search symbol table using singly-linked list
template <typename Key, typename Value> class SSTable
{
  public:
    class Iterator;

    Iterator begin()
    {
        return Iterator(m_top);
    }

    Iterator end()
    {
        auto x = m_top;

        while (x != nullptr)
        {
            x = x->next;
        }

        return x;
    }

    void put(Key key, Value value)
    {
        throw std::runtime_error("TODO: implement");
    }

    Iterator get(Key key)
    {
        auto x = m_top;

        while (x != nullptr)
        {
            if (x->key == key)
            {
                return x;
            }

            x = x->next;
        }

        return end();
    }

    void remove(Key)
    {
        throw std::runtime_error("TODO: implement");
    }

    bool contains(Key key)
    {
        return get(key) != nullptr;
    }

    bool empty()
    {
        return m_size == 0;
    }

    size_t size()
    {
        return m_size;
    }

  private:
    struct Node;
    std::shared_ptr<Node> m_top;
    size_t m_size;
};

template <typename Key, typename Value> struct SSTable<Key, Value>::Node
{
    Key key;
    Value val;
    std::shared_ptr<Node> next;
};

template <typename Key, typename Value> class SSTable<Key, Value>::Iterator
{
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Value;
    using pointer = std::shared_ptr<Node>;
    using reference = Value &;

  public:
    Iterator(pointer ptr) : m_ptr(ptr)
    {
    }

    reference operator*() const
    {
        return m_ptr->val;
    }

    pointer operator->()
    {
        return m_ptr;
    }

    // Prefix increment
    Iterator &operator++()
    {
        m_ptr = m_ptr->next;
        return this;
    }

    // Postfix increment
    Iterator operator++(Iterator)
    {
        Iterator tmp = this;
        ++this;
        return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b)
    {
        return a.m_ptr == b.m_ptr;
    };

    friend bool operator!=(const Iterator &a, const Iterator &b)
    {
        return a.m_ptr != b.m_ptr;
    };

  private:
    pointer m_ptr;
};

} // namespace st
