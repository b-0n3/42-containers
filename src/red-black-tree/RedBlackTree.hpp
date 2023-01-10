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
#include "../iterators/bidirectional_iterator.hpp"

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
    enum insertCases {
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
        typedef ft::ValueNode<pointer, value_type> value_node_type;
        typedef ft::LeafNode<pointer, value_type> leaf_node_type;
        typedef ft::Node<pointer, value_type> node_type;
        typedef typename allocator_type::template rebind<leaf_node_type>::other leaf_node_alloc;
        typedef typename allocator_type::template rebind<value_node_type>::other value_node_alloc;
        typedef typename leaf_node_alloc::pointer leaf_node_pointer;
        typedef typename value_node_alloc::pointer value_node_pointer;
        typedef node_type *node_type_pointer;
        typedef ft::Optional<deleteCases> deleteCasesOptional;
        typedef ft::Optional<node_type_pointer> node_optional;
        typedef ft::BidirectionalIterator<node_type,  value_type> iterator;
        typedef ft::BidirectionalIterator< node_type, const value_type> const_iterator;
        typedef ft::pair<iterator, bool> creationPair;
        typedef ft::RedBlackTree<T, Compare , Alloc> ___self;
    private:
        allocator_type _alloc;
        value_node_alloc _value_node_alloc;
        leaf_node_alloc _leaf_node_alloc;
        node_type_pointer leafNode;
        node_type_pointer root;
        compare_type compare;
        node_type_pointer current;
        size_t _size;
        typedef std::out_of_range out_of_range_execption;
    public:
        explicit RedBlackTree(const allocator_type _alloc = allocator_type(),
                              const compare_type compare = compare_type(),
                              const value_node_alloc _value_node_alloc = value_node_alloc(),
                              const leaf_node_alloc _leaf_node_alloc = leaf_node_alloc()
        ) : _alloc(_alloc),
            _value_node_alloc(_value_node_alloc),
            _leaf_node_alloc(_leaf_node_alloc),
            leafNode(createLeafNode()),
            root(leafNode),
            compare(compare),
            _size(0) {
        }

        RedBlackTree(const_reference val,
                     const allocator_type _alloc = allocator_type(),
                     const compare_type compare = compare_type(),
                     const value_node_alloc _value_node_alloc = value_node_alloc(),
                     const leaf_node_alloc _leaf_node_alloc = leaf_node_alloc()) :
                _alloc(_alloc),
                _value_node_alloc(_value_node_alloc),
                _leaf_node_alloc(_leaf_node_alloc),
                leafNode(createLeafNode()),
                root(leafNode),
                compare(compare),
                _size(0) {

            insert(val);
        }
        RedBlackTree(___self const &x):
                _alloc(x._alloc),
                _value_node_alloc(x._value_node_alloc),
                _leaf_node_alloc(x._leaf_node_alloc),
                leafNode(x.leafNode),
                root(x.root),
                compare(x.compare),
                _size(x._size)
        {
        }
        RedBlackTree  &operator=(___self const &rhs)
        {
            if (*this != rhs)
            {
                _alloc = rhs._alloc;
                _value_node_alloc = rhs._value_node_alloc;
                _leaf_node_alloc = rhs._leaf_node_alloc;
                leafNode = rhs.leafNode;
                root =rhs. root;
                compare = rhs.compare;
                current = rhs.current;
                _size = rhs._size;
            }
            return *this;
        }
        ~RedBlackTree() {
            if (!root->isLeaf())
                clearAll(root);
            destroyNode(leafNode);
        }

    public:
        void logInorderTraversal(node_type_pointer p) {
            if (!p->isLeaf()) {
                logInorderTraversal(p->getLeft());
                std::cout << *p->getValue() << " ";
                logInorderTraversal(p->getRight());
            }
        }

        void log(std::string const &header, bool clear) {
            if (clear)
                system("clear ");
            std::cout << std::endl;
            std::cout << header << std::endl;

            this->root->print(null);
            std::cout << std::endl;;
            logInorderTraversal(root);
            std::cout << std::endl;
        }
        /*
         * @Return: an iterator pointing to the first element in the container
         * whose key is not considered to go before k (i.e., either it is equivalent or goes after).
         */
        node_type_pointer lower_bound(const_reference val) {
            node_type_pointer x = root;
            const_reference lesser = val;

            while(!x->isLeaf())
            {
                if (isEqual(x, val))
                 return x;
                if (isLess(x ,lesser))
                {
                    lesser = *x;
                    x = x->getRight();
                }else
                    x = x->getLeft();
            }
            return x;
        }
        /*
         * @Return: an iterator pointing to the first element in
         * the container whose key is considered to go after k.
         */
        node_type_pointer upper_bound(const_reference val)
        {
            node_type_pointer x = root;
            const_reference greater = val;

            while(!x->isLeaf())
            {
                if (!isLess(x ,greater))
                {
                    greater = *x;
                    x = x->getLeft();
                }else
                    x = x->getRight();
            }
            return x;
        }

        size_t size() {
            return _size;
        }

        bool isEmpty() {
            return _size == 0 || root->isLeaf();
        }

        iterator begin() {
            return iteratorAt(minimum(root));
        }

        iterator end() {
            return iteratorAt(leafNode);
        }

        const_iterator cbegin() const {
            return const_iteratorAt(minimum(root));
        }

        const_iterator cend() const {
            return const_iteratorAt(leafNode);
        }
        size_t maxSize()
        {
            return _alloc.max_size();
        }
        void clear() {
            clearAll(root);
        }


        size_t count(const_reference val)
        {
           return recursiveCount(root, 0 , val);
        }
        void swap(___self &x)
        {
            allocator_type _allocX = x._alloc;
            value_node_alloc _value_node_allocX = x._value_node_alloc;
            leaf_node_alloc _leaf_node_allocX = x._leaf_node_alloc;
            node_type_pointer leafNodeX = x.leafNode;
            node_type_pointer rootX = x.root;
            compare_type compareX = x.compare;
            node_type_pointer currentX = x.current;
            size_t _sizeX = x._size;
            x._alloc = _alloc;
            x._value_node_alloc = _value_node_alloc;
            x._leaf_node_alloc = _leaf_node_alloc;
            x.leafNode = leafNode;
            x.root = root;
            x.compare = compare;
            x.current = current;
            x._size = _size;

            _alloc = _allocX;
            _value_node_alloc = _value_node_allocX;
            _leaf_node_alloc = _leaf_node_allocX;
            leafNode = leafNodeX;
            root = rootX;
            compare = compareX;
            current = currentX;
            _size = _sizeX;


        }
        creationPair insert(const_reference val) {
            bool isNew = true;
            if (root->getType() != LEAF)
                insertValue(root, val, root, &isNew);
            else {
                root = createNode(val);
                root->makeMeBlack();
                current = root;
            }
            insertFixUp(current);
#ifdef RED_BLACK_TREE_DEBUG
            log("after inserting ", false);
#endif
            updateLeafPrevs(current);
            if (isNew)
                _size++;
            return ft::make_pair(iterator(current), isNew);
        }

        node_type_pointer search(const_reference val) {
            return this->search(root, val);
        }

        size_t erase(const_reference val) {
            size_t lastSize = _size;
            deleteNode(node_optional::ofNullable(root), val);
            leafNode->setParent(null);
            #ifdef RED_BLACK_TREE_DEBUG
             log("after deleting  ", false);
            #endif
             return lastSize - _size;
        }
        bool validateTree()
        {
            if (root== null || root->isLeaf())
                return true;
            if (root->isRed())
            {
                std::cout<< "root is not black" << std::endl;
                return false;
            }
            int blackCount =  0;
            return checkBlackNodeCount(root ,&blackCount, 0) && noRedRedParentChild(root, BLACK);
        }

        size_t getHeight() {
            return root->getHeight();
        }

    private:
        iterator iteratorAt(node_type_pointer n)
        {
            return iterator(n);
        }
        const_iterator const_iteratorAt(node_type_pointer n)
        {
            return const_iterator(n);
        }

        node_type_pointer search(node_type_pointer x, const_reference val) {
            if (x->isLeaf() || isEqual(x, val))
                return x;
            if (isLess(x, val))
                return search(x->getRight(), val);
            else
                return search(x->getLeft(), val);
        }

        node_type_pointer insertValue(node_type_pointer head,
                                      const_reference val,
                                      node_type_pointer parent,
                                      bool *isNew) {
            if (head->isLeaf()) {
                head = createNode(val, leafNode, leafNode, parent);
                current = head;
                return head;
            }
            if (compare(*head->getValue(), val)) {
                head->setRight(insertValue(head->getRight(), val, head, isNew));
            } else if (compare(val, *head->getValue())) {
                head->setLeft(insertValue(head->getLeft(), val, head, isNew));
            } else {
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
            while (!z->isParentBlack()) {
                if (z->getParent()->whoAmI()) {
                    node_type_pointer y = z->getGrandParent()->getRight();
                    if (y->isRed()) {
                        z->makeParentBlack();
                        y->makeMeBlack();
                        z->getParent()->makeParentRed();
                        z = z->getGrandParent();
                    } else {
                        if (!z->whoAmI()) {
                            z = z->getParent();
                            rotateLeft(z);
                        }
                        z->makeParentBlack();
                        z->getParent()->makeParentRed();
                        rotateRight(z->getGrandParent());
                    }
                } else {
                    node_type_pointer y = z->getGrandParent()->getLeft();
                    if (y->isRed()) {
                        z->makeParentBlack();
                        y->makeMeBlack();
                        z->getParent()->makeParentRed();
                        z = z->getGrandParent();
                    } else {
                        if (z->whoAmI()) {
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
            if (!x->isParentLeaf()) {
                if (x->whoAmI())
                    x->getParent()->setLeft(y);
                else
                    x->getParent()->setRight(y);
            } else
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

            node_type_pointer y = x->getLeft();
            x->setLeft(y->getRight());
            if (!y->isRightLeaf())
                y->getRight()->setParent(x);
            if (!y->isLeaf())
                y->setParent(x->getParent());
            if (!x->isParentLeaf()) {
                if (!x->whoAmI())
                    x->getParent()->setRight(y);
                else
                    x->getParent()->setLeft(y);
            } else
                root = y;
            y->setRight(x);
            if (!x->isLeaf())
                x->setParent(y);
        }

        void rotateLeftAndRecolor(node_type_pointer x, bool recolor) {
            node_type_pointer parent = x->getParent();
            x->setParent(parent->getParent());
            if (!parent->isParentLeaf()) {
                if (!parent->whoAmI())
                    parent->getParent()->setRight(x);
                else
                    parent->getParent()->setLeft(x);
            }
            node_type_pointer left = x->getLeft();
            x->setLeft(parent);
            parent->setParent(x);
            parent->setRight(left);
            if (!left->isLeaf()) {
                left->setParent(parent);
            }
            if (recolor) {
                x->makeMeBlack();
                parent->makeMeRed();
            }
        }

        void rotateRightAndRecolor(node_type_pointer x, bool recolor) {
            node_type_pointer parent = x->getParent();
            x->setParent(parent->getParent());
            if (!parent->isParentLeaf()) {
                if (!parent->whoAmI())
                    parent->getParent()->setRight(x);
                else
                    parent->getParent()->setLeft(x);
            }
            node_type_pointer right = x->getRight();
            x->setRight(parent);
            parent->setParent(x);
            parent->setLeft(right);
            if (!right->isLeaf()) {
                right->setParent(parent);
            }
            if (recolor) {
                x->makeMeBlack();
                parent->makeMeRed();
            }
        }


        void deleteNode(node_optional head, const_reference val) {
            if (!head.isPresent() || head.get()->isLeaf())
                return;
            if (isEqual(head.get(), val)) {
                node_optional left = head.get()->getLeftOptional();
                node_optional right = head.get()->getRightOptional();
                if ((left.isPresent() && left.get()->isLeaf())
                    || (right.isPresent() && right.get()->isLeaf())) {
                    deleteOneChild(head.get());
                    _size--;
                } else {
                    node_type_pointer inorderSuccesor = minimum(head.get()->getRight());

                    exchange(head.get(), inorderSuccesor);
                    // @FIXME :: update leaf Node pointer to less and greate values
                    deleteNode(head, *inorderSuccesor->getValue());
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

        void deleteOneChild(node_type_pointer x) {
            // note that we didnt delete x in this function

            node_type_pointer child = null;
            Color  xColor = x->getColor();
            node_optional left = x->getLeftOptional();
            node_optional right = x->getRightOptional();
            if (left.isPresent() && !left.get()->isLeaf())
                child = left.get();
            else if (right.isPresent())
                child = right.get();
            child = replaceChildWithParent(x, child);
            if (xColor == BLACK) {
                if (!child->isLeaf() && child->isRed())
                    child->makeMeBlack();
                else {
                    executeDoubleBlackCase(CASE_1, child);
                }
            }

        }
        node_type_pointer replaceChildWithParent(node_type_pointer  x, node_type_pointer child)
        {
                  child->setParent(x->getParent());
                  if (x->isParentLeaf())
                  {
                          root = child;
                  }else
                  {
                      if (x->whoAmI())
                          x->getParent()->setLeft(child);
                      else
                          x->getParent()->setRight(child);
                  }
                  destroyNode(x);
                  return child;
        }
        void executeDoubleBlackCase(deleteCases c,
                                    node_type_pointer x) {
            switch (c) {
                case CASE_0:
                    root->makeMeBlack();
                    break;
                case CASE_1:
                    deleteCase1(x);
                    break;
                case CASE_2:
                    deleteCase2(x);
                    break;
                case CASE_3:
                    deleteCase3(x);
                    break;
                case CASE_4:
                    deleteCase4(x);
                    break;
                case CASE_5:
                    deleteCase5(x);
                    break;
                case CASE_6:
                    deleteCase6(x);
                    break;
            }
        }

        void deleteCase1(node_type_pointer x) {
            if (x->isParentLeaf() || x->getParent() == null) {
                root = x;
                return executeDoubleBlackCase(CASE_0, x);
            }
            return  executeDoubleBlackCase(CASE_2, x);
        }

        void deleteCase2(node_type_pointer x) {
            node_optional sibling = x->getSiblingOptional();
            if (sibling.isPresent() && sibling.get()->isRed()) {
                if (sibling.get()->whoAmI())
                    rotateRightAndRecolor(sibling.get(), true);
                else
                    rotateLeftAndRecolor(sibling.get(), true);
                if (sibling.get()->isParentLeaf())
                    root = sibling.get();
            }
            return  executeDoubleBlackCase(CASE_3, x);

        }

        void deleteCase3(node_type_pointer x) {
            node_optional sibling = x->getSiblingOptional();
            if (sibling.isPresent()) {
                if (x->isParentBlack() &&
                    !sibling.get()->isRed() &&
                    sibling.get()->isBothChildsBlack()) {
                    sibling.get()->makeMeRed();
                    return  executeDoubleBlackCase(CASE_1, x->getParent());
                } else
                    return  executeDoubleBlackCase(CASE_4, x);
            } else
                return  executeDoubleBlackCase(CASE_4, x);
        }

        void deleteCase4(node_type_pointer x) {
            node_optional sibling = x->getSiblingOptional();
            if (sibling.isPresent()
                && !x->isParentBlack()
                && !sibling.get()->isRed()
                && sibling.get()->isBothChildsBlack()) {
                sibling.get()->makeMeRed();
                x->makeParentBlack();
                return executeDoubleBlackCase(CASE_0, x);
            } else
                executeDoubleBlackCase(CASE_5, x);
        }

        void deleteCase5(node_type_pointer x) {
            node_optional sibling = x->getSiblingOptional();
            if (sibling.isPresent()) {
                if (!sibling.get()->isRed()) {
                    node_optional sRight = sibling.get()->getRightOptional();
                    node_optional sLeft = sibling.get()->getLeftOptional();
                    if (x->whoAmI() && sRight.isPresent()
                        && !sRight.get()->isRed() && sLeft.isPresent() && sLeft.get()->isRed())
                        rotateRightAndRecolor(sLeft.get(), true);
                    else if (!x->whoAmI() && sRight.isPresent()
                             && sRight.get()->isRed() && sLeft.isPresent() && !sLeft.get()->isRed())
                        rotateLeftAndRecolor(sRight.get(), true);
                }
            }
            executeDoubleBlackCase(CASE_6, x);
        }

        void deleteCase6(node_type_pointer x) {
            node_optional sibling = x->getSiblingOptional();
            if (sibling.isPresent()) {
                sibling.get()->setColor(sibling.get()->getParent()->getColor());
                sibling.get()->makeParentBlack();
                if (x->whoAmI()) {
                    sibling.get()->getRight()->makeMeBlack();
                    rotateLeftAndRecolor(sibling.get(), false);
                } else {
                    sibling.get()->getLeft()->makeMeBlack();
                    rotateRightAndRecolor(sibling.get(), false);
                }
                if (sibling.get()->isParentLeaf()) {
                    root = sibling.get();
                }
            }
            executeDoubleBlackCase(CASE_0, x);
        }

        node_type_pointer minimum(node_type_pointer n) {
           return n->minimum()
           .orElseThrow(out_of_range_execption("minimum out of range"));
        }
        node_type_pointer maximum(node_type_pointer n)
        {
           return n->maximum()
           .orElseThrow(out_of_range_execption("maximum out of range"));
        }

        node_type_pointer successor(node_type_pointer x) {
           return x->successor().orElseThrow(out_of_range_execption("out of range"));
        }
        node_type_pointer  predecessor(node_type_pointer x)
        {
           return x->predecessor().orElseThrow(out_of_range_execption("out of range"));
        }
        size_t recursiveCount(node_type_pointer r, size_t count , const_reference val)
        {
            size_t c = 0;
            if (r->isLeaf())
                return count;
            if (isEqual(r, val))
                c = 1;
            if (isLess(r, val))
                return recursiveCount(r->getRight(), count + c, val);
            else
                return recursiveCount(r->getLeft(), count + c, val);
        }
        bool checkBlackNodeCount(node_type_pointer r , int *blackCount, int count)
        {
                if (!r->isLeaf() && !r->isRed())
                    count++;
                if (r->isLeftLeaf() && r->isRightLeaf())
                {
                    if (*blackCount == 0)
                    {
                        *blackCount = count;
                        return true;
                    }else
                        return count == *blackCount;
                }
                return checkBlackNodeCount(r->getLeft(), blackCount, count)&&
                        checkBlackNodeCount(r->getRight(), blackCount, count);
        }
        bool noRedRedParentChild(node_type_pointer  r, Color c)
        {
            if (r == null || r->isLeaf())
                return true;
            if (r->isRed() && c == RED)
                return false;
            return noRedRedParentChild(r->getLeft(), r->getColor())
            && noRedRedParentChild(r->getRight(), r->getColor());
        }
        bool isEqual(const_reference a, const_reference b) {
            return isLess(a, b) == isLess(b, a);
        }

        bool isEqual(node_type_pointer a, const_reference b) {
            if (a->isLeaf())
                return false;

            return isLess(*a->getValue(), b) == isLess(b, *a->getValue());
        }

        bool isEqual(node_type_pointer x, node_type_pointer y) {
            if (y->isLeaf() || x->isLeaf())
                return false;
            isEqual(*x->getValue(), *y->getValue());
        }

        bool isLess(node_type_pointer a, node_type_pointer b) {
            if (a->isLeaf() || b->isLeaf())
                return false;
            return isLess(*a->getValue(), *b->getValue());
        }

        bool isLess(node_type_pointer a, const_reference b) {
            if (a->isLeaf())
                return false;
            return isLess(*a->getValue(), b);
        }

        bool isLess(const_reference a, const_reference b) {
            return compare(a, b);
        }

        /*
         *   case 1 : lhs is parent of rhs
         *             P
         *            / \
         *           X  lhs
         *              / \
         *             l   rhs
            case 2: lhs is the root
                     LEAF
                       |
                      lhs
                      / \
                     X  rhs
                        / \

             case 3 : no direct link between lhs and rhs
                       P
                     /  \
                    X    lhs
                           \
                            Y
                           /
                         rhs
         */
        void exchange(node_type_pointer lhs, node_type_pointer rhs) {
            // copy the value of rhs to lhs
            destroyData(lhs->getValue());
            lhs->setValue(value2Pointer(*rhs->getValue()));
            if (lhs->isMyLeftChild(rhs))
            {
                swapLeftChild(lhs, rhs);
            }else if (lhs->isMyRightChild(rhs))
            {
                swapRightChild(lhs, rhs);
            }else
            {
                swapNodes(lhs, rhs);
            }
           Color rhsColor = rhs->getColor();
            rhs->setColor(lhs->getColor());
            lhs->setColor(rhsColor);

        }
        void swapNodes(node_type_pointer u, node_type_pointer v)
        {
            node_optional uParent = u->getParentOptional();
            node_optional  vParent = v->getParentOptional();
            node_optional uL = u->getLeftOptional();
            node_optional uR = u->getRightOptional();
            bool isULeft = u->whoAmI();
            node_optional vL = v->getLeftOptional();
            node_optional vR = v->getRightOptional();
            bool isVLeft = v->whoAmI();
            // swap Parents
            v->setParent(uParent.get());
            u->setParent(vParent.get());
            if (vParent.isPresent() && !vParent.get()->isLeaf())
            {
                if (isVLeft)
                    vParent.get()->setLeft(u);
                else
                    vParent.get()->setRight(u);
            }
            if (uParent.isPresent() && !uParent.get()->isLeaf())
            {
                if (isULeft)
                    uParent.get()->setLeft(v);
                else
                    uParent.get()->setRight(v);
            }
            // swapChilds
                v->setLeft(uL.get());
                v->setRight(uR.get());
                u->setLeft(vL.get());
                u->setRight(vR.get());
                u->makeMeTheParentOfMyChilds();
                v->makeMeTheParentOfMyChilds();
                //v->setColor(u->getColor());
        }
        void swapLeftChild(node_type_pointer x, node_type_pointer child)
        {
            node_optional parent = x->getParentOptional();
            bool iAm = x->whoAmI();
            node_optional right = x->getRightOptional();
            node_optional childLeftChild = child->getLeftOptional();
            if (parent.isPresent() && !parent.get()->isLeaf())
            {
                if(iAm)
                    parent.get()->setLeft(child);
                else
                    parent.get()->setRight(child);
            }
            child->setParent(parent.get());
            x->setRight(child->getRight());
            child->setLeft(x);
            child->setRight(right.get());
            x->setLeft(childLeftChild.get());
            child->makeMeTheParentOfMyChilds();
            x->makeMeTheParentOfMyChilds();
            //child->setColor(x->getColor());

        }
        void swapRightChild(node_type_pointer x, node_type_pointer child)
        {
            node_optional parent = x->getParentOptional();
            bool iAm = x->whoAmI();
            node_optional left = x->getLeftOptional();
            node_optional childRightChild = child->getRightOptional();
            if (parent.isPresent() && !parent.get()->isLeaf())
            {
                if(iAm)
                    parent.get()->setLeft(child);
                else
                    parent.get()->setRight(child);
            }
            child->setParent(parent.get());
            x->setLeft(child->getLeft());
            child->setRight(x);
            child->setLeft(left.get());
            x->setRight(childRightChild.get());
            child->makeMeTheParentOfMyChilds();
            x->makeMeTheParentOfMyChilds();
        }

        pointer value2Pointer(const_reference val) {
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

        void updateLeafPrevs(node_type_pointer  c)
        {
            node_optional cOptional = node_optional ::ofNullable(c);
            node_optional l = leafNode->getLastLessVisited();
            node_optional g = leafNode->getLastGreatVisted();
            if (l.isPresent() && isLess(c, l.get()))
                leafNode->setLastLessVisted(cOptional);
            else if (g.isPresent() && isLess(g.get(), c))
                leafNode->setLastGreatVisted(cOptional);
            else{
                if (isLess(root, c))
                {
                    leafNode->setLastGreatVisted(cOptional);
                }else
                    leafNode->setLastLessVisted(cOptional);
            }
        }

        node_optional cloneNodeAndReplaceData(node_type_pointer x,
                                              const_reference v) {
            if (!x->isLeaf()) {
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
                if (p.isPresent() && !p.get()->isLeaf()) {
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

        void cloneData(node_type_pointer c, const_pointer val) {
            destroyData(c->getValue());
            c->setValue(value2Pointer(val));
        }
        void clearAll(node_type_pointer r)
        {
            if (r->isLeaf())
                return;
            clearAll(r->getLeft());
            clearAll(r->getRight());
            destroyNode(r);
        }
        void destroyData(pointer data) {
            _alloc.destroy(data);
            _alloc.deallocate(data, 1);
        }

        void destroyNode(node_type_pointer node) {
            if (!node->isLeaf()) {
                destroyData(node->getValue());
                _value_node_alloc.destroy((value_node_pointer) node);
                _value_node_alloc.deallocate((value_node_pointer) node, 1);
            } else {
                _leaf_node_alloc.destroy((leaf_node_pointer) node);
                _leaf_node_alloc.deallocate((leaf_node_pointer) node, 1);
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