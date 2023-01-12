//
// Created by Abdelouahad Ait hamd on 1/11/23.
//

#pragma once
//
// Created by Abdelouahad Ait hamd on 12/19/22.
//
#pragma  once
#include "../red-black-tree/RedBlackTree.hpp"
#include <algorithm>
#include <memory>
#include "../utility/pair.hpp"
#include "../algo/equal.hpp"
#include "../iterators/reverse_iterator.h"
#include "../algo/lexicographical_compare.hpp"
namespace ft {
    template < class T,
            class Compare = std::less<T>,
            class Alloc = std::allocator<T>
             > class set {
    public:
        typedef  T key_type;
        typedef  T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef  Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef size_t  size_type;
    private:
        typedef ft::RedBlackTree< value_type, key_compare ,Alloc> _rb_tree_type;
        typedef ft::set<T, Compare, Alloc> ___self;
    public:
        typedef typename  _rb_tree_type::const_iterator iterator;
        typedef typename  _rb_tree_type::const_iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename ft::IteratorTraits<iterator>::difference_type difference_type;
    private:
        _rb_tree_type redBlackTree;
    public:
        explicit  set(const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
                : redBlackTree(_rb_tree_type(alloc, comp))
        {

        }
        template <class InputIterator>
        set(InputIterator first,
            InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()):
                redBlackTree(_rb_tree_type(alloc, comp))
        {
            insert(first, last);
        }
        set(const ___self & x) : redBlackTree(x.redBlackTree){}

        set& operator= (const ___self & x)
        {
            if (this != &x)
            {
                redBlackTree = x.redBlackTree;
            }
            return *this;
        }
        ~set(){}

        ft::pair<iterator, bool> insert(const value_type& val)
        {
            return redBlackTree.insert(val);
        }
        iterator insert (iterator position, const value_type& val)
        {

            position =  redBlackTree.insert(val).first;
            return position;
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                redBlackTree.insert(*first);
                first++;
            }
        }
        void erase (iterator position)
        {
            redBlackTree.erase(*position);
        }
        size_type erase (const key_type& k)
        {
            return redBlackTree.erase(k);
        }
        void erase (iterator first, iterator last)
        {
            while (first != last)
                first = redBlackTree.erase(first);
        }
        void swap (___self & x)
        {
            return redBlackTree.swap(x.redBlackTree);
        }
        void clear()
        {
            redBlackTree.clear();
        }
        key_compare key_comp() const
        {
            return key_compare();
        }
        value_compare value_comp() const
        {
            return value_compare();
        }
        iterator find (const key_type& k) const
        {
            return iterator(redBlackTree.search(k));
        }

        size_type count (const key_type& k) const
        {
            return redBlackTree.count(k);
        }
        iterator lower_bound (const key_type& k) const
        {
            return iterator(redBlackTree.lower_bound(k));
        }

        iterator upper_bound (const key_type& k) const
        {
            return  iterator(redBlackTree.upper_bound(k));
        }
        ft::pair<iterator, iterator>   equal_range(const key_type& k) const
        {
            return  ft::make_pair(lower_bound(k), upper_bound(k));
        }

        allocator_type get_allocator() const
        {
            return allocator_type();
        }

        bool empty() const
        {
            return redBlackTree.isEmpty();
        }
        size_type max_size() const
        {
            return  redBlackTree.maxSize();
        }
        size_type size() const
        {
            return redBlackTree.size();
        }



        iterator begin()
        {
            return redBlackTree.begin();
        }
        const_iterator begin() const
        {
            return redBlackTree.cbegin();
        }
        iterator end()
        {
            return redBlackTree.end();
        }
        const_iterator end() const
        {
            return redBlackTree.cend();
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }
    };
    template <class T, class Compare, class Alloc>
    void swap (ft::set<T,Compare,Alloc>& x, ft::set<T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
    template < class T, class Compare, class Alloc>
    bool operator== ( const set<T,Compare,Alloc>& lhs,
                      const set<T,Compare,Alloc>& rhs )
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template < class T, class Compare, class Alloc>
    bool operator!= ( const set<T,Compare,Alloc>& lhs,
                      const set<T,Compare,Alloc>& rhs ){
        return !(lhs == rhs);
    }

    template <class T, class Compare, class Alloc>
    bool operator<  ( const set<T,Compare,Alloc>& lhs,
                      const set<T,Compare,Alloc>& rhs )
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                           rhs.begin(), rhs.end());
    }

    template < class T, class Compare, class Alloc>
    bool operator<= ( const set<T,Compare,Alloc>& lhs,
                      const set<T,Compare,Alloc>& rhs )
    {
        return !(lhs > rhs);
    }

    template < class T, class Compare, class Alloc>
    bool operator>  ( const set<T,Compare,Alloc>& lhs,
                      const set<T,Compare,Alloc>& rhs )
    {
        return !(lhs < rhs);
    }

    template <class T, class Compare, class Alloc>
    bool operator>= ( const set<T,Compare,Alloc>& lhs,
                      const set<T,Compare,Alloc>& rhs )
    {
        return !(lhs < rhs);
    }

}

