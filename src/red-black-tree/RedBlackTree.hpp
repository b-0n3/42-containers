//
// Created by Abdelouahad Ait hamd on 12/19/22.
//

#pragma once
#include "../node/node.hpp"
namespace ft {
    template<class T>
    class RedBlackTree {
    public:
        typedef T value_type;
        typedef value_type *pointer;
        typedef value_type &reference;
    private:
        ft::Node<value_type> *leafNode;
        ft::Node<value_type> *head;
        ft::Node<value_type> *current;
    public:
        RedBlackTree() :
                leafNode(new  ft::LeafNode<value_type>()),
                head(leafNode),
                current(leafNode) {}

        RedBlackTree(reference val) :
                leafNode(new  ft::LeafNode<value_type>()),
                head(new  ft::ValueNode<value_type>(value, leafNode, leafNode, leafNode)),
                current(head) {}
    private:
        ft::Node<value_type> *insert(value_type &valueType){
            return  new ft::ValueNode<value_type>(valueType);
        }
        bool insert()
        {

        }


    };
}