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
#include "deleteCases.hpp"

namespace ft {
    template<class T>
    struct _less {
        bool operator()(T o, T other) {
            return o < other;
        }
    };

    /*
     *  @TODO: create documentation of insertCases
     */
    enum insertCases{
        LL,
        LR,
        RL,
        RR
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
        typedef ft::Optional<deleteCases> deleteCasesOptional;
        typedef ft::Optional<node_type_pointer> node_optional;
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
        void logInorderTraversal(node_type_pointer p)
        {
            if (!p->isLeaf())
            {
                logInorderTraversal(p->getLeft());
                std::cout << *p->getValue() << " ";
                logInorderTraversal(p->getRight());
            }
        }

        void log(std::string const &header , bool clear) {
            if (clear)
             system("clear ");
            std::cout << std::endl;
            std::cout << header << std::endl;

//            ft::Vector<std::string> list(this->root->getHeight(), " ");
            this->root->print(null);
            std::cout <<std::endl;;
            logInorderTraversal(root);
            std::cout <<std::endl;;
//            prettiFyOutput(list);
//            for (size_t i = 0; i < list.size(); i++)
//                std::cout << list[i] << std::endl;
//           std::getchar();
        }

        node_type_pointer insert(const_reference val) {
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
            log("before deleting  ", true);
            deleteNode( node_optional::ofNullable(root) , val);
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

        /*
         * @Param: x new node
         *  @Description: maintain RED-Black tree balance after inserting x
         */
        node_type_pointer insertFixUp(node_type_pointer z) {
                 while (!z->isParentBlack())
                 {
                     if (z->getParent()->whoAmI())
                     {
                         node_type_pointer  y = z->getGrandParent()->getRight();
                         if (y->isRed())
                         {
                             z->makeParentBlack();
                             y->makeMeBlack();
                             z->getParent()->makeParentRed();
                             z = z->getGrandParent();
                         }
                         else {
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
                     else
                     {
                         node_type_pointer  y = z->getGrandParent()->getLeft();
                         if (y->isRed())
                         {
                             z->makeParentBlack();
                             y->makeMeBlack();
                             z->getParent()->makeParentRed();
                             z = z->getGrandParent();
                         }
                         else{
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

        /*
         *   @Param : x
         *   @Description: rotate x to left
         *        x's right child takes its place in the tree ,
         *        and x becom the left child of that node;
         *               P
         *             /   \
         *            x     U
         *          /   \
         *         L      y
         *        / \    / \
         *       C   D  E   F
         *
         *           result
         *            | |
         *            \/
         *               P
         *              /  \
         *             y    U
         *            /  \
         *           x    F
         *          / \
         *         L   E
         *        / \
         *       C   D
         */

        void rotateLeft(node_type_pointer x) {
            node_type_pointer y = x->getRight();
            x->setRight(y->getLeft());
            if (!y->isLeftLeaf())
                y->getLeft()->setParent(x);
            if (!y->isLeaf())
                y->setParent(x->getParent());
            if (!x->isParentLeaf())
            {
                if (x->whoAmI())
                    x->getParent()->setLeft(y);
                else
                    x->getParent()->setRight(y);
            }
            else
                root = y;
            y->setLeft(x);
            if (!x->isLeaf())
                x->setParent(y);
        }
        /*
        *   @Param : x
        *   @Description: rotate x to right
        *        x's left child takes its place in the tree ,
        *        and x becom the right child of that node;
        *               P
        *             /   \
        *            x     U
        *          /   \
        *         y      R
        *        / \    / \
        *       C   D  E   F
                   result
                    | |
                    \/
                    P
                 /     \
                y       U
              /    \
             C      x
                  /  \
                 D    R
                     / \
                    E  F
        */
        void rotateRight(node_type_pointer x) {

            node_type_pointer   y  = x->getLeft();
            x->setLeft(y->getRight());
            if (!y->isRightLeaf())
                y->getRight()->setParent(x);
            if (!y->isLeaf())
                y->setParent(x->getParent());
            if (!x->isParentLeaf())
            {
                if (!x->whoAmI())
                    x->getParent()->setRight(y);
                else
                    x->getParent()->setLeft(y);
            }else
                root = y;
            y->setRight(x);
            if (!x->isLeaf())
                x->setParent(y);
        }

        void rotateLeftReplacment(node_type_pointer x, bool recolor)
        {
            node_type_pointer  parent = x->getParent();
            x->setParent(parent->getParent());
            if (!parent->isParentLeaf())
            {
                if (!parent->whoAmI())
                    parent->getParent()->setRight(x);
                else
                    parent->getParent()->setLeft(x);
            }
            node_type_pointer left = x->getLeft();
            x->setLeft(parent);
            parent->setParent(x);
            parent->setRight(left);
            if (!left->isLeaf())
            {
                left->setParent(parent);
            }
            if (recolor)
            {
                x->makeMeBlack();
                parent->makeMeRed();
            }
        }
        void rotateRightReplacement(node_type_pointer x, bool recolor)
        {
            node_type_pointer  parent = x->getParent();
            x->setParent(parent->getParent());
            if (!parent->isParentLeaf())
            {
                if (!parent->whoAmI())
                    parent->getParent()->setRight(x);
                else
                    parent->getParent()->setLeft(x);
            }
            node_type_pointer right = x->getRight();
            x->setRight(parent);
            parent->setParent(x);
            parent->setLeft(right);
            if (!right->isLeaf())
            {
                right->setParent(parent);
            }
            if (recolor)
            {
                x->makeMeBlack();
                parent->makeMeRed();
            }
        }
        /*
       *       @Param : u deleted node
       *       @Param : v replacement of U
         *           PU              PV
         *          / \             /  \
         *         u   pUR         v    pUR
         *        / \             / \
         *      uL  uR           vL  vR
                       | |
                       \/
                       PU              PU
                     /  \              |
                   v    pUR    and     u
                  / \                /  \
                vL   vR             uL   uR
                if u want to link u child also you need to do it on you own
       */
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
        void deleteNode(node_optional head, const_reference val)
        {
                if (!head.isPresent() || head.get()->isLeaf())
                    return;
                if (isEqual(head.get() ,val))
                {
                       node_optional left = head.get()->getLeftOptional();
                       node_optional right = head.get()->getRightOptional();
                       if ((left.isPresent() && left.get()->isLeaf())
                       || (right.isPresent() && right.get()->isLeaf()))
                       {
                           fixDoubleBlackNode(head.get());
                       }
                       else{
                           node_type_pointer inorderSuccesor = minimum(head.get()->getRight());
                           // create other object invalidate any itertor pointing to head
                            deleteNode(head.get()->getRightOptional() ,*inorderSuccesor->getValue());
                            cloneNodeAndReplaceData(head.get(), *inorderSuccesor->getValue());
                       }
                }
                // fiha ni9ach
                else if (isLess(head.get(), val))
                    deleteNode(head.get()->getRightOptional(), val);
                else
                    deleteNode(head.get()->getLeftOptional(), val);
        }
        /*               P
         *            /   \
         *          X      R
         *         / \    / \
         *        N   V
         *        we must replace x with one of the childs
         *        and then check the delete Cases
         *
         */

        void fixDoubleBlackNode(node_type_pointer x)
        {
            // note that we didnt delete x in this function
            if (!x->isRed())
            {
                node_type_pointer  child = null;
                node_optional left = x->getLeftOptional();
                node_optional right = x->getRightOptional();
                if (left.isPresent() && !left.get()->isLeaf())
                    child = left.get();
                else if (right.isPresent())
                    child = right.get();
                if (!child->isLeaf() && child->isRed())
                    child->makeMeBlack();
                else
                {
                    executeDoubleBlackCase(CASE_1, child, x);
                }
            }

        }

        void executeDoubleBlackCase(deleteCases c,
                                    node_type_pointer x,
                                    node_type_pointer parent)
        {
            switch (c) {
                case CASE_0:
                    root->makeMeBlack();
                    break;
                case CASE_1:
                    deleteCase1(x, parent);
                    break;
                case CASE_2:
                    deleteCase2(x, parent);
                    break;
                case CASE_3:
                    deleteCase3(x, parent);
                    break;
                case CASE_4:
                    deleteCase4(x, parent);
                    break;
                case CASE_5:
                    deleteCase5(x, parent);
                    break;
                case CASE_6:
                    deleteCase6(x, parent);
                    break;
            }
        }
        void deleteCase1(node_type_pointer x, node_type_pointer parent)
        {
           if (parent->isParentLeaf()) {
               root = x;
             return  executeDoubleBlackCase(CASE_0, x, parent);
           }
            executeDoubleBlackCase(CASE_2, x, parent);
        }

        void deleteCase2(node_type_pointer x, node_type_pointer parent)
        {
            node_optional sibling = parent->getSiblingOptional();
            if (sibling.isPresent() && sibling.get()->isRed())
            {
                if (sibling.get()->whoAmI())
                    rotateRightReplacement(sibling.get(), true);
                else
                    rotateRightReplacement(sibling.get(), true);
            }
            executeDoubleBlackCase(CASE_3, x, parent->getParent());

        }
        void deleteCase3(node_type_pointer x, node_type_pointer parent)
        {
            node_optional sibling = parent->getSiblingOptional();
            if (sibling.isPresent())
            {
                if(parent->isParentBlack() &&
                !sibling.get()->isRed() &&
                sibling.get()->isBothChildsBlack()) {
                    sibling.get()->makeMeRed();
                    executeDoubleBlackCase(CASE_1, parent->getParent(), parent->getParent());
                }
                else
                    executeDoubleBlackCase(CASE_4, x, parent);
            }
            else
                executeDoubleBlackCase(CASE_0, x, parent);
        }
        void deleteCase4(node_type_pointer x, node_type_pointer parent)
        {
            node_optional sibling = parent->getSiblingOptional();
            if (sibling.isPresent()
            && !sibling.get()->isRed()
            && sibling.get()->isBothChildsBlack())
            {
                sibling.get()->makeMeRed();
                parent->makeParentBlack();
                return executeDoubleBlackCase(CASE_0, x, parent);
            }
            else
                executeDoubleBlackCase(CASE_5, x, parent);
        }
        void deleteCase5(node_type_pointer x, node_type_pointer parent)
        {
            node_optional sibling = parent->getSiblingOptional();
            if (sibling.isPresent())
            {
                if (!sibling.get()->isRed() && !parent->isParentBlack())
                {
                    node_optional sRight = sibling.get()->getRightOptional();
                    node_optional sLeft = sibling.get()->getLeftOptional();
                    if (parent->whoAmI() && sRight.isPresent()
                    && !sRight.get()->isRed() && sLeft.isPresent() && sLeft.get()->isRed())
                        rotateRightReplacement(sLeft.get(), true);
                    else if (!parent->whoAmI() && sRight.isPresent()
                            && sRight.get()->isRed() && sLeft.isPresent() && !sLeft.get()->isRed())
                        rotateLeftReplacment(sRight.get(), true);
                }
            }
            executeDoubleBlackCase(CASE_6, x, parent);
        }
        void deleteCase6(node_type_pointer x, node_type_pointer parent)
        {
            node_optional sibling = parent->getSiblingOptional();
            x = null;
            if (sibling.isPresent())
            {
                sibling.get()->setColor(sibling.get()->getParent()->getColor());
                sibling.get()->makeParentBlack();
                if (parent->whoAmI())
                {
                    sibling.get()->getRight()->makeMeBlack();
                    rotateLeftReplacment(sibling.get(), false);
                }else
                {
                    sibling.get()->getLeft()->makeMeBlack();
                    rotateRightReplacement(sibling.get(), false);
                }
                if (sibling.get()->isParentLeaf())
                {
                    root = sibling.get();
                }
            }
            executeDoubleBlackCase(CASE_0, x, parent);
        }
        node_type_pointer minimum(node_type_pointer n)
        {
            if (n->isLeftLeaf())
                return n;
            return minimum(n->getLeft());
        }
        node_type_pointer successor(node_type_pointer x)
        {
            if (!x->isRightLeaf())
                return minimum(x->getRight());
            else {
                node_type_pointer y = x->getParent();
                while (!y->isLeaf() &&  isEqual(x , y->getRight()))
                {
                        x = y;
                        y = y->getParent();
                }
                return y;
            }
        }
        bool isEqual(const_reference a, const_reference b)
        {
            return isLess(a, b) == isLess(b, a);
        }
        bool isEqual(node_type_pointer a, const_reference b)
        {
            if (a->isLeaf())
                return false;

            return isLess(*a->getValue(), b) == isLess(b, *a->getValue());
        }

        bool isEqual(node_type_pointer x, node_type_pointer y)
        {
            if (y->isLeaf() || x->isLeaf())
                return false;
            isEqual(*x->getValue(), *y->getValue());
        }
        bool isLess(node_type_pointer a, node_type_pointer b)
        {
            if (a->isLeaf() || b->isLeaf())
                return false;
            return isLess(*a->getValue(), *b->getValue());
        }

        bool isLess(node_type_pointer a, const_reference b)
        {
            if (a->isLeaf())
                return false;
            return isLess(*a->getValue(), b);
        }
        bool isLess(const_reference a, const_reference b)
        {
            return compare(a, b);
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
        node_optional cloneNodeAndReplaceData(node_type_pointer x,
                        const_reference  v)
        {
            if (!x->isLeaf())
            {
                node_type_pointer newNode = createNode(v,
                                                       x->getLeft(),
                                                       x->getRight(),
                                                       x->getParent());
                node_optional left = newNode->getLeftOptional();
                node_optional right = newNode->getRightOptional();
                // make the new node the parent of x childs
                if (left.isPresent())
                    left.get()->setParent(newNode);
                if (right.isPresent())
                    right.get()->setParent(newNode);
                node_optional p = x->getParentOptional();
                if (p.isPresent() && !p.get()->isLeaf())
                {
                    if (x->whoAmI())
                        p.get()->setLeft(newNode);
                    else
                        p.get()->setRight(newNode);
                }
                destroyNode(x);
                return node_optional::of(newNode);
            }
            return node_optional::empty();
        }
        void cloneData(node_type_pointer c, const_pointer val)
        {
            destroyData(c->getValue());
            c->setValue(value2Pointer(val));
        }
        void destroyData(pointer data)
        {

                _alloc.destroy(data);
                _alloc.deallocate(data , 1);
        }
        void destroyNode(node_type_pointer node)
        {
            if (!node->isLeaf()) {
                destroyData(node->getValue());
                _value_node_alloc.destroy((value_node_pointer)node);
                _value_node_alloc.deallocate((value_node_pointer)node, 1);
            }
            else
            {
                _leaf_node_alloc.destroy((leaf_node_pointer )node);
                _leaf_node_alloc.deallocate((leaf_node_pointer)node, 1);
            }
        }

        node_type_pointer createLeafNode() {
            leaf_node_pointer leaf = _leaf_node_alloc.allocate(1);
            _leaf_node_alloc.construct(leaf);
            leaf->setParent(null);
            leaf->setRight(leaf);
            leaf->setLeft(leaf);
            return leaf;
        }
    };


}