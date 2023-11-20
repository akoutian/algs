// SPDX-License-Identifier: GPL-3.0-or-later

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

namespace tst
{

template <typename T> struct Node
{
    char c;
    std::shared_ptr<Node<T>> left, mid, right;
    std::optional<T> value;
};

// generic ternary search trie
template <typename T> class TST
{
  public:
    size_t size()
    {
        return m_size;
    }

    bool contains(std::string key)
    {
        return get(key).has_value();
    }

    std::optional<T> get(std::string key)
    {
        if (key.length() == 0)
        {
            throw std::invalid_argument("key length must be >= 1");
        }

        std::shared_ptr<Node<T>> x = get(m_root, key, 0);

        if (x == nullptr)
        {
            return std::nullopt;
        }

        return x->value;
    }

    void put(std::string key, T val)
    {
        if (!contains(key))
        {
            ++m_size;
        }

        m_root = put(m_root, key, val, 0);
    }

    std::vector<std::string> keys()
    {
        std::vector<std::string> result;

        std::string prefix;
        collect(m_root, prefix, result);

        return result;
    }

    std::vector<std::string> keys_with_prefix(std::string prefix)
    {
        std::vector<std::string> result;

        std::shared_ptr<Node<T>> x = get(m_root, prefix, 0);

        if (x == nullptr)
        {
            return result;
        }

        if (x->value)
        {
            result.push_back(prefix);
        }

        std::string p(prefix);
        collect(x->mid, p, result);

        return result;
    }

    // Returns all keys in the symbol table that match a given pattern, where
    // the character '.' is treated as a wildcard.
    std::vector<std::string> keys_that_match(std::string pattern)
    {
        std::vector<std::string> result;

        std::string prefix;
        collect(m_root, prefix, 0, pattern, result);

        return result;
    }

    std::string longest_prefix_of(std::string query)
    {
        if (query.empty())
        {
            return {};
        }

        size_t length{}, ii{};
        std::shared_ptr<Node<T>> x = m_root;
        while (x != nullptr && ii < query.length())
        {
            char c = query[ii];

            if (c < x->c)
            {
                x = x->left;
            }
            else if (c > x->c)
            {
                x = x->right;
            }
            else
            {
                ++ii;
                if (x->value)
                {
                    length = ii;
                }
                x = x->mid;
            }
        }

        return query.substr(0, length);
    }

  private:
    std::shared_ptr<Node<T>> get(std::shared_ptr<Node<T>> x, std::string key, size_t d)
    {
        if (x == nullptr)
        {
            return nullptr;
        }

        if (key.length() == 0)
        {
            throw std::invalid_argument("key length must be >= 1");
        }

        char c = key[d];

        if (c < x->c)
        {
            return get(x->left, key, d);
        }
        else if (c > x->c)
        {
            return get(x->right, key, d);
        }
        else if (d < key.length() - 1)
        {
            return get(x->mid, key, d + 1);
        }
        else
        {
            return x;
        }
    }

    std::shared_ptr<Node<T>> put(std::shared_ptr<Node<T>> x, std::string key, T val, size_t d)
    {
        char c = key[d];

        if (x == nullptr)
        {
            x = std::make_shared<Node<T>>();
            x->c = c;
        }

        if (c < x->c)
        {
            x->left = put(x->left, key, val, d);
        }
        else if (c > x->c)
        {
            x->right = put(x->right, key, val, d);
        }
        else if (d < key.length() - 1)
        {
            x->mid = put(x->mid, key, val, d + 1);
        }
        else
        {
            x->value = val;
        }

        return x;
    }

    void collect(std::shared_ptr<Node<T>> x, std::string &prefix, std::vector<std::string> &result)
    {
        if (x == nullptr)
        {
            return;
        }

        collect(x->left, prefix, result);

        if (x->value)
        {
            result.push_back(prefix + x->c);
        }

        prefix.push_back(x->c);
        collect(x->mid, prefix, result);
        prefix.pop_back();
        collect(x->right, prefix, result);
    }

    void collect(std::shared_ptr<Node<T>> x, std::string &prefix, size_t d,
                 const std::string &pattern, std::vector<std::string> &result)
    {
        if (x == nullptr)
        {
            return;
        }

        char c = pattern[d];

        if (c == '.' || c < x->c)
        {
            collect(x->left, prefix, d, pattern, result);
        }

        if (c == '.' || c == x->c)
        {
            size_t n = pattern.length() - 1;
            if (d == n && x->value)
            {
                result.push_back(prefix + x->c);
            }
            if (d < n)
            {
                prefix.push_back(x->c);
                collect(x->mid, prefix, d + 1, pattern, result);
                prefix.pop_back();
            }
        }

        if (c == '.' || c > x->c)
        {
            collect(x->right, prefix, d, pattern, result);
        }
    }

    size_t m_size;
    std::shared_ptr<Node<T>> m_root;
};

} // namespace tst
