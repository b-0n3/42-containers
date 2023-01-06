//
// Created by Abdelouahad Ait hamd on 12/19/22.
//

#pragma once


#include <algorithm>
#include <memory>
#include <unistd.h>
#include <string>
#include "../node/node.hpp"
#include "../utility/pair.hpp"
#include "../utility/Forward.hpp"
#include <sys/ioctl.h>
#include <unistd.h>


namespace ft {
    template<class T>
    struct _less {
        bool operator()(T o, T other) {
            return o < other;
        }
    };

    template<class T,
            class Compare = std::less<T>,
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
        node_type_pointer current;
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


        void log(std::string const &header , bool clear) {
            if (clear)
             system("clear ");
            std::cout << std::endl;
            std::cout << header << std::endl;
//            ft::Vector<std::string> list(this->root->getHeight(), " ");
            this->root->print(null);
            std::cout <<std::endl;;
//            prettiFyOutput(list);
//            for (size_t i = 0; i < list.size(); i++)
//                std::cout << list[i] << std::endl;
//           std::getchar();
        }

        node_type_pointer insert(const_reference val) {
//#ifndef DEBUG_RED_BLACK_TREE

//#endif
                if (val == -9)
                    std::cout<< "the breaker" << std::endl;
            log("before inserting ", true);
            bool  isNew = true;
            if (root->getType() != LEAF)
                insertValue(root, val, root, &isNew);
            else
            {
                root = createNode(val);
                root->makeMeBlack();
                current = root;
            }
            insertFixUp(current);
            std::cout << "is New" << isNew << std::endl;
            log("after inserting ", false);
            return current;
        }

        node_type_pointer search(const_reference val) {
            return this->search(root, val);
        }
        void erase(const_reference val)
        {
            node_type_pointer toDelete = search(val);
            if (toDelete->isLeaf())
                return ;
            log("before deleting  ", true);
            erase(toDelete);
            log("after deleting  ", false);
        }
        // @TODO: add erase By Range
//        void erase(const_reference val)
//        {
//            erase(root, val);
//        }
        size_t getHeight() {
            return root->getHeight();
        }

    private:

        node_type_pointer search(node_type_pointer current, const_reference val) {
            if ( current->getType() == LEAF ||
                (compare(*current->getValue(), val) == compare(val, *current->getValue())))
                return current;
            if (compare(*current->getValue(), val))
                return search(current->getRight(), val);
            else
                return search(current->getLeft(), val);
        }

        node_type_pointer insertValue(node_type_pointer head,
                                      const_reference val,
                                      node_type_pointer parent,
                                      bool  *isNew) {
            if (head->getType() == LEAF)
            {
                head = createNode(val, leafNode , leafNode, parent);
                current = head;
                return head;
            }
            if (compare(*head->getValue(), val ))
            {
              head->setRight(insertValue(head->getRight(), val, head, isNew));
            }else if (compare(val, *head->getValue()))
            {
               head->setLeft(insertValue(head->getLeft(), val, head, isNew));
            }
            else {
                *isNew = false;
                head->setValue(value2Pointer(val));
            }

            return head;
        }


        node_type_pointer insertFixUp(node_type_pointer z) {
            while (!z->isParentBlack())
            {
                node_type_pointer  y;
                if (z->getParent()->whoAmI())
                {
                    y = z->getGrandParent()->getRight();
                    if (y->isRed())
                    {
                        z->makeParentBlack();
                        y->makeMeBlack();
                        y->getParent()->makeParentRed();
                        z = z->getGrandParent();
                    }
                    else
                    {
                        if (!z->whoAmI())
                        {
                            z = z->getParent();
                            rotateLeft(z);
                        }
                        z->makeParentBlack();
                        z->getParent()->makeParentRed();
                        rotateRight(z->getGrandParent());
                    }
                }
                else{
                    y = z->getGrandParent()->getLeft();
                    if (y->isRed())
                    {
                        z->makeParentBlack();
                        y->makeMeBlack();
                        z->getParent()->makeParentRed();
                        z = z->getGrandParent();
                    }
                    else
                    {
                        if (z->whoAmI())
                        {
                            z = z->getParent();
                            rotateRight(z);
                        }
                        z->makeParentBlack();
                        z->getParent()->makeParentRed();
                        rotateLeft(z->getGrandParent());
                    }
                }
            }
            root->makeMeBlack();
            return z;
        }

        void rotateLeft(node_type_pointer pivot) {
           node_type_pointer   y  = pivot->getRight();
           pivot->setRight(y->getLeft());
           if (!y->isLeftLeaf())
               y->getLeft()->setParent(pivot);
           y->setParent(pivot->getParent());
           if (y->isParentLeaf())
               root = y;
           else if (pivot->whoAmI())
               pivot->getParent()->setLeft(y);
           else
               pivot->getParent()->setRight(y);
           y->setLeft(pivot);
           pivot->setParent(y);
        }

        void rotateRight(node_type_pointer pivot) {
//            pivot = null;
            node_type_pointer   y  = pivot->getLeft();
            pivot->setLeft(y->getRight());
            if (!y->isRightLeaf())
                y->getRight()->setParent(pivot);
            y->setParent(pivot->getParent());
            if (y->isParentLeaf())
                root = y;
            else if (!pivot->whoAmI())
                pivot->getParent()->setRight(y);
            else
                pivot->getParent()->setLeft(y);
            y->setRight(pivot);
            pivot->setParent(y);
        }

        void erase(node_type_pointer  toDelete)
        {
            node_type_pointer y = toDelete, x;
            Color yOriginalColor = y->getColor();
            if (toDelete->isLeftLeaf())
            {
                x = toDelete->getRight();
                transplant(toDelete , toDelete->getRight());
            }else if (toDelete->isRightLeaf())
            {
                x = toDelete->getLeft();
                transplant(toDelete , toDelete->getLeft());
            }
            else {
                y =  minimum(toDelete->getRight());
                yOriginalColor = y->getColor();
                x = y->getRight();
                if (y != toDelete->getRight())
                {
                    transplant(y, y->getRight());
                    y->setRight(toDelete->getRight());
                    y->getRight()->setParent(y);
                }else
                    x->setParent(y);
                transplant(toDelete, y);
                y->setLeft(toDelete->getLeft());
                y->getLeft()->setParent(y);
                y->setColor(toDelete->getColor());
            }
            if (yOriginalColor == BLACK)
                deleteFIXUP(x);
        }
        void deleteFIXUP(node_type_pointer x)
        {
            node_type_pointer  w;
            while (x != root && !x->isRed())
            {
                if (x->whoAmI())
                {
                    w = x->getSibling(true);
                    if (w->isRed())
                    {
                        w->makeMeBlack();
                        x->makeParentRed();
                        rotateLeft(x->getParent());
                        w = x->getSibling(true);
                    }
                    if (!w->getLeft()->isRed() && !w->getRight()->isRed()) {
                        w->makeMeRed();
                        x = x->getParent();
                    }
                    else {
                        if (!w->getRight()->isRed())
                        {
                            w->getLeft()->makeMeBlack();
                            w->makeMeRed();
                            rotateRight(w);
                            w = x->getSibling(true);
                        }
                        w->setColor(x->getParent()->getColor());
                        x->makeParentBlack();
                        w->getRight()->makeMeBlack();
                        rotateLeft(x->getParent());
                        x = root;
                    }
                }else
                {
                    w = x->getSibling(false);
                    if (w->isRed())
                    {
                        w->makeMeBlack();
                        x->makeParentRed();
                        rotateRight(x->getParent());
                        w = x->getSibling(false);
                    }
                    if (!w->getRight()->isRed() && !w->getLeft()->isRed())
                    {
                        w->makeMeRed();
                        x = x->getParent();
                    }
                    else{
                        if (!w->getLeft()->isRed())
                        {
                            w->getRight()->makeMeBlack();
                            w->makeMeRed();
                            rotateLeft(w);
                            w = x->getSibling(false);
                        }
                        w->setColor(x->getParent()->getColor());
                        x->makeParentBlack();
                        w->getLeft()->makeMeBlack();
                        rotateRight(x->getParent());
                        x = root;
                    }
                }
            }
            x->makeMeBlack();
        }
        void transplant(node_type_pointer u , node_type_pointer v)
        {
            if (u->isParentLeaf())
                root = v;
            else if (u->whoAmI())
                u->getParent()->setLeft(v);
            else
                u->getParent()->setRight(v);
            v->setParent(u->getParent());
        }

        node_type_pointer minimum(node_type_pointer n)
        {
            if (n->isLeftLeaf())
                return n;
            return minimum(n->getLeft());
        }
        pointer value2Pointer(const_reference val)
        {
            pointer value = _alloc.allocate(1);
            _alloc.construct(value, val);
            return value;
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
            value_node_pointer c = _value_node_alloc.allocate(1);

            _value_node_alloc.construct(c, value_node_type(value2Pointer(val), left, right, parent));
            return c;
        }

        node_type_pointer createLeafNode() {
            leaf_node_pointer leaf = _leaf_node_alloc.allocate(1);
            _leaf_node_alloc.construct(leaf);
            leaf->setParent(leaf);
            leaf->setRight(leaf);
            leaf->setLeft(leaf);
            return leaf;
        }
    };


}