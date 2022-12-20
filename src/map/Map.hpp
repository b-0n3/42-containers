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
            class Alloc = std::allocator <ft::Pair<const Key, T>>
    >
    class map {
    public:
        typedef  Key key_type;
        typedef  T mapped_type;
        typedef  ft::Pair<key_type , mapped_type> value_type;
        typedef Compare key_compare;
       // @TODO add value_compaer

        // @END
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        // @Todo add ITERATOR

        // @END
        typedef size_t  size_type;

    private:
        ft::RedBlackTree<pointer> *_tree;


    public:

    };
}