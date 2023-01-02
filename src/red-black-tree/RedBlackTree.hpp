//
// Created by Abdelouahad Ait hamd on 12/19/22.
//

#pragma once


#include <algorithm>
#include <memory>
#include "../node/node.hpp"
#include "../utility/pair.hpp"
#include "../utility/Forward.hpp"

namespace ft {
    template< class T>
    struct _less{
        bool operator()(T o, T other)
        {
            return o < other;
        }
    };
    template<class T,
            class Compare = std::less<T >,
            class Alloc = std::allocator<T>
    >
    class RedBlackTree {
    public:
        typedef T value_type;
        typedef Compare compare_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::const_reference const_pointer;
        typedef ft::ValueNode<pointer> value_node_type;
        typedef ft::LeafNode<pointer> leaf_node_type;
        typedef ft::Node<pointer> node_type;
        typedef typename allocator_type::template rebind<leaf_node_type>::other leaf_node_alloc;
        typedef typename allocator_type::template rebind<value_node_type>::other value_node_alloc;
        typedef typename leaf_node_alloc::pointer leaf_node_pointer;
        typedef typename value_node_alloc::pointer value_node_pointer;
        typedef node_type *node_type_pointer;

    private:
        allocator_type _alloc;
        value_node_alloc _value_node_alloc;
        leaf_node_alloc _leaf_node_alloc;
        node_type_pointer leafNode;
        node_type_pointer root;
        compare_type compare;
//        ft::Node<value_type> *current;
    public:
        explicit RedBlackTree(const allocator_type _alloc = allocator_type(),
                              const value_node_alloc _value_node_alloc = value_node_alloc(),
                              const leaf_node_alloc _leaf_node_alloc = leaf_node_alloc(),
                              const compare_type compare = compare_type()
        ) : _alloc(_alloc),
            _value_node_alloc(_value_node_alloc),
            _leaf_node_alloc(_leaf_node_alloc),
            leafNode(createLeafNode()),
            root(leafNode),
            compare(compare) {
        }

        RedBlackTree(const_reference val,
                     const allocator_type _alloc = allocator_type(),
                     const value_node_alloc _value_node_alloc = value_node_alloc(),
                     const leaf_node_alloc _leaf_node_alloc = leaf_node_alloc(),
                     const compare_type compare = compare_type()) :
                _alloc(_alloc),
                _value_node_alloc(_value_node_alloc),
                _leaf_node_alloc(_leaf_node_alloc),
                leafNode(createLeafNode()),
                root(leafNode),
                compare(compare) {
            insert(val);
        }

    public:
        node_type_pointer insert(const_reference val) {
            return insert(createNode(val));
        }
        node_type_pointer search(const_reference val)
        {
           return this->search(root, val);
        }
        size_t getHeight()
        {
            return root->getHeight();
        }
    private:

        node_type_pointer search(node_type_pointer current, const_reference  val)
        {
                if (current == null || current->getType() == LEAF ||
                    (compare(*current->getValue(), val) == compare(val, *current->getValue())))
                        return current;
                if (compare(*current->getValue(), val))
                    return search(current->getRight(), val);
                else
                    return search(current->getLeft(), val);
        }

        node_type_pointer insert(node_type_pointer z) {
            node_type_pointer x = root;
            node_type_pointer y = leafNode;
            while (x != leafNode) {
                y = x;
                if (compare(*z->getValue(), *x->getValue()))
                    x = x->getLeft();
                else
                    x = x->getRight();
            }
            z->setParent(y);
            if (y->getType() == LEAF)
                root = z;
            else if (compare(*z->getValue(), *y->getValue()))
                y->setLeft(z);
            else
                y->setRight(z);
            z->setLeft(leafNode);
            z->setRight(leafNode);
            z->setColor(RED);

            z =  insertFixUp(z);
#ifndef DEBUG_RED_BLACK_TREE
            system("clear;");
//            std::cout <<std::endl<<  "operation insert" << std::endl;
            this->root->print();
//            system("sleep 1");
//            std::cout << this->root->print(std::cout.rdbuf()) << std::endl;
#endif
return z;
        }

        node_type_pointer insertFixUp(node_type_pointer z) {
            node_type_pointer zCopy = z;
            while (z->getParent()->getColor() == RED) {

                if (z->getParent() == z->getGrandParent()->getLeft()) {
                    node_type_pointer y = z->getUncle(false);
                    if (y != null && y->getColor() == RED) {
                        z->getParent()->setColor(BLACK);
                        y->setColor(BLACK);
                        z->getGrandParent()->setColor(RED);
                        z = z->getGrandParent();
                    } else {
                        if (z == z->getParent()->getRight()) {
                            z = z->getParent();
                            rotateLeft(z);
                        }
                        z->getParent()->setColor(BLACK);
                        z->getGrandParent()->setColor(RED);;
                        rotateRight(z->getGrandParent());
                    }
                } else {
                    node_type_pointer y = z->getUncle(true);
                    if (y != null && y->getColor() == RED) {
                        z->getParent()->setColor(BLACK);
                        y->setColor(BLACK);
                        z->getGrandParent()->setColor(RED);
                        z = z->getGrandParent();
                    } else {
                        if (z == z->getParent()->getLeft()) {
                            z = z->getParent();
                            rotateRight(z);
                        }
                        z->getParent()->setColor(BLACK);
                        z->getGrandParent()->setColor(RED);
                        rotateLeft(z->getGrandParent());
                    }
                }
            }
            root->setColor(BLACK);
            return zCopy;
        }

        void rotateLeft(node_type_pointer current) {
            node_type_pointer right = current->getRight(); // get the x right child
            current->setRight(right->getLeft()); // switch childs
            if (right->getLeft()->getType() != LEAF)
                right->getLeft()->setParent(current);
            right->setParent(current->getParent());
            if (current->getParent()->getType() == LEAF)
                root = right;
            else if (current == current->getParent()->getLeft())
                current->getParent()->setLeft(right);
            else
                current->getParent()->setRight(right);
            right->setLeft(current);
            current->setParent(right);
        }

        void rotateRight(node_type_pointer current) {
            node_type_pointer left = current->getLeft();
            current->setLeft(left->getRight());
            if (left->getRight()->getType() != LEAF)
                left->getRight()->setParent(current);
            left->setParent(current->getParent());
            if (current->getParent()->getType() == LEAF)
                root = left;
            else if (current == current->getParent()->getRight())
                current->getParent()->setRight(left);
            else
                current->getParent()->setLeft(left);
            left->setLeft(current);
            current->setParent(left);
        }

        node_type_pointer createNode(const_reference val,
                                     node_type_pointer left = null,
                                     node_type_pointer right = null,
                                     node_type_pointer parent = null) {
            if (left == null)
                left = leafNode;
            if (right == null)
                right = leafNode;
            if (parent == null)
                parent = leafNode;
            value_node_pointer current = _value_node_alloc.allocate(1);
            pointer value = _alloc.allocate(1);
            _alloc.construct(value, val);
            _value_node_alloc.construct(current, value_node_type(value, left, right, parent));
            return current;
        }

        node_type_pointer createLeafNode() {
            leaf_node_pointer leaf = _leaf_node_alloc.allocate(1);
            _leaf_node_alloc.construct(leaf);
            return leaf;
        }
    };


}