//
// Created by Abdelouahad Ait hamd on 12/19/22.
//
#pragma  once
#include "../red-black-tree/RedBlackTree.hpp"
#include <algorithm>
#include <memory>
#include "../utility/pair.hpp"
namespace ft {
    template<class Key,
            class T,
            class Compare = std::less<Key>,
            class Alloc = std::allocator <ft::pair<const Key, T> >
    >
    class Map {
    public:
        typedef  Key key_type;
        typedef  T mapped_type;
        typedef  ft::pair<const key_type , mapped_type> value_type;
        typedef Compare key_compare;

        typedef  Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef size_t  size_type;
        class value_compare
        {
            friend class Map;
        protected:
            Compare comp;
            value_compare (Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

    private:
        typedef ft::RedBlackTree<value_type, value_compare ,Alloc> _rb_tree_type;
        typedef ft::Map<Key, T, Compare, Alloc> ___self;
    public:
        typedef typename  _rb_tree_type::iterator iterator;
        typedef typename  _rb_tree_type::const_iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename ft::IteratorTraits<iterator>::difference_type difference_type;
    private:
        _rb_tree_type redBlackTree;
    public:
        Map(const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type())
                      : redBlackTree(_rb_tree_type(alloc, value_compare(comp)))
        {

        }
        template <class InputIterator>
        Map(InputIterator first,
              InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()):
        redBlackTree(_rb_tree_type(alloc, value_compare(comp)))
        {
            insert(first, last);
        }
        Map(const ___self & x) : redBlackTree(x.redBlackTree){}

        Map& operator= (const ___self & x)
        {
            if (this != &x)
            {
                redBlackTree = x.redBlackTree;
            }
        }
        ~Map(){}

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
           return redBlackTree.erase(make_pair(k ,mapped_type()));
        }
        void erase (iterator first, iterator last)
        {
            while (first != last)
            {
                redBlackTree.erase(*first);
                first++;
            }
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
        iterator find (const key_type& k)
        {
            return iterator(redBlackTree.search(make_pair(k ,mapped_type())));
        }
        const_iterator find(const key_type& k) const
        {
            return const_iterator(redBlackTree.search(make_pair(k ,mapped_type())));
        }
        size_type count (const key_type& k) const
        {
            return redBlackTree.count(make_pair(k, mapped_type()));
        }
        iterator lower_bound (const key_type& k)
        {
            return iterator(redBlackTree.lower_bound(ft::make_pair(k, mapped_type())));
        }
        const_iterator lower_bound (const key_type& k) const
        {
           return  const_iterator(redBlackTree.lower_bound(ft::make_pair(k, mapped_type())));
        }
        iterator upper_bound (const key_type& k)
        {
            return  iterator(redBlackTree.upper_bound(ft::make_pair(k, mapped_type())));
        }
        const_iterator upper_bound (const key_type& k) const
        {
            return  const_iterator(redBlackTree.upper_bound(ft::make_pair(k, mapped_type())));
        }

        ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
        {
            ft::pair<const_iterator, const_iterator> p;
            p.first= lower_bound(k);
            p.second = upper_bound(*p.first);
            return p;
        }
        ft::pair<iterator, iterator>   equal_range (const key_type& k)
        {
            ft::pair<iterator, iterator> p;
            p.first= lower_bound(k);
            p.second = upper_bound(*p.first);
            return p;
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
        size_type size()
        {
            return redBlackTree.size();
        }
        mapped_type &operator[](const key_type &k)
        {
            return insert(make_pair(k, mapped_type()))
            .first
            .first;
        }



        // @TODO: add more itertor  functions
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
}