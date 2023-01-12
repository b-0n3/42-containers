//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma  once

#include <iostream>
//#include <iomanip>
#include <sstream>
#include "color.hpp"
#include "NodeType.hpp"
#include "../utility/Forward.hpp"

#include "../optional/optional.hpp"

namespace ft {
    struct Trunk {
        Trunk *prev;
        Trunk *next;
        std::string str;
        Trunk( Trunk *prev, std::string str ) {
            this->prev = prev;
            this->str = str;
            next = null;
            if (prev!= null)
                prev->next = this;
        }
    };
    void showTrunks(Trunk *p) {
        if (p == nullptr) {
            std::cout << std::endl;
            return ;
        }

        showTrunks(p->prev);
        std::cout << p->str;
    }
    template<class T, typename ref>
    class Node {
    public:
        typedef T value_type;
        typedef ft::Node<T, ref> node_t;
        typedef ft::Node<T, ref> *node_pointer;
        typedef const ft::Node<T, ref> *const_node_pointer;
        typedef ft::Node<T, ref> &node_reference;
        typedef ft::Optional<node_pointer> node_optional;
        typedef ft::Optional<const_node_pointer> const_node_optional;
        typedef ft::Optional<bool *> bool_optional;
    protected:
        Node(value_type const value,node_pointer left, node_pointer right, node_pointer parent):
                value(value),
                parent(parent),
                left(left),
                right(right),
                color(RED),
                lastGVisited(node_optional::empty()),
                lastLessVisted(node_optional::empty())
        {}
//        Node(value_type const value,node_pointer left, node_pointer right, node_pointer parent,
//             Color c,
//             node_optional lastGVisited, node_optional lastLessVisted):
//                value(value),
//                parent(parent),
//                left(left),
//                right(right),
//                color(c),
//                lastGVisited(lastGVisited),
//                lastLessVisted(lastLessVisted)
//        {}
        value_type value;
        node_pointer parent;
        node_pointer left;
        node_pointer right;
        Color color;
        node_optional lastGVisited;
        node_optional lastLessVisted;



    public:
        Node() :
                value(null),
                parent(null),
                left(null),
                right(null),
                color(BLACK),
                lastGVisited(node_optional::empty()),
                lastLessVisted(node_optional::empty()){
        }

        virtual node_type getType() const = 0 ;

        virtual ~Node() {}

//        operator Node< T, const ref>() const{
//            return Node< T, const ref>
//                    (value, left , right, parent,  color, lastGVisited, lastLessVisted);
//        }
        Node(ft::Node<T, ref> const &rhs) :
                value(rhs.value),
                parent(rhs.parent),
                left(rhs.left),
                right(rhs.right),
                color(rhs.color) ,
                lastGVisited(rhs.lastGVisited),
                lastLessVisted(rhs.lastLessVisted){}

        virtual size_t getHeight() = 0;

        ft::Node<T, ref> &operator=(ft::Node<T, ref> const &rhs) {
            if (this == &rhs)
                return *this;
            value = rhs.value;
            parent = rhs.parent;
            left = rhs.parent;
            right = rhs.right;
            color = rhs.color;
            lastGVisited = rhs.lastGVisited;
            lastLessVisted = rhs.lastLessVisted;
            return *this;
        }

        void clearLastVistedNodesPointer()
        {
            this->lastGVisited = node_optional::empty();
            this->lastLessVisted = node_optional::empty();
        }


        void setLastLessVisted(node_optional lastL)
        {
            this->lastLessVisted = lastL;
        }
        node_optional getLastLessVisited() const{
           return lastLessVisted;
        }


        void setLastGreatVisted(node_optional lastG)
        {
            this->lastGVisited = lastG;
        }

        node_optional getLastGreatVisted()  const
        {
            return lastGVisited;
        }

        ref &operator*() const {
            return *this->getValue();
        }

        value_type operator->() const{
            return this->getValue();
        }

        node_t &operator++()
        {
            node_optional x = successor();
            if (x.isPresent())
            {
                this->clearLastVistedNodesPointer();
                x.get()->setLastLessVisted(node_optional::of(this));
                return *x.get();
            }
            throw std::out_of_range("out of range");
        }

        node_t &operator--()
        {
            node_optional x = predecessor();
            if (x.isPresent())
            {
                this->clearLastVistedNodesPointer();
                x.get()->setLastGreatVisted(node_optional::of(this));
                return *x.get();
            }
            throw std::out_of_range("out of range");
        }
        Node &operator++(int)
        {
            node_optional x = successor();
            if (x.isPresent())
            {
                this->clearLastVistedNodesPointer();
                x.get()->setLastLessVisted(node_optional::of(this));
                return *x.get();
            }
            throw std::out_of_range("out of range");
        }

        node_t &operator--(int)
        {
            node_optional x = predecessor();
            if (x.isPresent())
            {
                x.get()->clearLastVistedNodesPointer();
                x.get()->setLastGreatVisted(node_optional::of(this));
                return *x.get();
            }
            throw std::out_of_range("out of range");
        }
        // min and max
        node_optional minimum() {
            if (isLeftLeaf())
                return node_optional::of(this);
            node_pointer n = getLeft();
            while (!n->isLeftLeaf())
              n  = n->getLeft();
            return node_optional::ofNullable(n);
        }

        node_optional maximum()
        {
            if (isRightLeaf())
                return  node_optional::of(this);
            node_pointer n = getRight();
            while (!n->isRightLeaf())
                n = n->getRight();
            return node_optional::ofNullable(n);
        }

        node_optional successor()
        {
            if (isLeaf())
                return getLastLessVisited();
            if(!isRightLeaf())
                return getRight()->minimum();
             node_pointer  y = getParent();
              node_pointer   x = this;
            while (!y->isLeaf() && x == y->getRight())
            {
                x = y;
                y = y->getParent();
            }
            return node_optional::ofNullable(y);
        }


        node_optional  predecessor()
        {
            if (isLeaf())
                return getLastGreatVisted();
            if (!isLeftLeaf())
                return getLeft()->maximum();
            node_pointer y = getParent();
            node_pointer x = this;
            while (!y->isLeaf() && x == y->getLeft())
            {
                x = y;
                y = y->getParent();
            }
            return node_optional::ofNullable(y);
        }

        node_optional getSiblingOptional() const
        {
//            if (getType() == LEAF)
//                return node_optional::empty();
            node_optional p = getParentOptional();
            if (p.isPresent())
            {
                if (whoAmI())
                    return p.get()->getRightOptional();
                return p.get()->getLeftOptional();
            }
            return node_optional::empty();
        }


        node_optional  getParentOptional() const
        {
             return node_optional::ofNullable(parent);
        }

        node_optional getLeftOptional() const
        {
            if (getType() == LEAF)
                return node_optional::empty();
            return Optional<node_pointer>::ofNullable(left);
        }

        node_optional getRightOptional() const
        {
            if (getType() == LEAF)
                return node_optional::empty();
            return node_optional::ofNullable(right);
        }
        bool isMyRightChild(node_pointer other)const
        {
            if (other == null)
                return false;
            node_optional  r = getRightOptional();
            return r.isPresent() && r.get() == other;
        }
        bool isMyLeftChild(node_pointer other) const
        {
            if (other == null)
                return false;
            node_optional  l = getLeftOptional();
            return l.isPresent() && l.get() == other;
        }
        bool isBothChildsBlack()const
        {
            node_optional l = getLeftOptional();
            node_optional r = getRightOptional();
            return l.isPresent() && !l.get()->isRed()&&
                            r.isPresent() && !r.get()->isRed();
        }


        bool isParentBlack()const
        {
            return !getParent()->isRed();
        }
        bool isRed()const{
            return color == RED;
        }
        void makeMeBlack()
        {
            setColor(BLACK);
        }
        void makeMeRed()
        {
            setColor(RED);
        }
        void makeParentBlack()
        {
            getParent()->makeMeBlack();
        }
        void makeParentRed()
        {
            getParent()->makeMeRed();
        }
        void makeMeTheParentOfMyChilds()
        {
             if (!isLeftLeaf())
                 left->setParent(this);
             if (!isRightLeaf())
                 right->setParent(this);
        }

        node_pointer getGrandParent()const
        {
            return this->getParent()->getParent();
        }
        bool isLeaf()const
        {
            return getType() == LEAF;
        }
        bool  isLeftLeaf() const
        {
            if (getType() == LEAF)
                return true;
            return getLeftOptional().isPresent()
            && left->isLeaf();
        }
        bool isRightLeaf() const
        {
            if (getType() == LEAF)
                return true;
            return getRightOptional().isPresent()
            &&
            right->isLeaf();
        }


        bool isParentLeaf()const
        {
            return getParent() == null || getParent()->isLeaf();
        }
        void setValue(value_type v)
        {
            value = v;
        }
        value_type getValue()const{
            return value;
        }
        node_pointer getLeft() const{
            return left;
        }
        node_pointer getRight() const {
            return right;
        }
        node_pointer getParent() const {
            return parent;
        }
        void setLeft(node_pointer n){
            left = n;
        }
        void setRight(node_pointer n){
            right = n;
        }
        void setParent(node_pointer n){
            parent = n;
        }
        void setColor(Color c)
        {
            color = c;
        }
        Color getColor() const {
            return color;
        }
        bool whoAmI() const
        {
           node_optional p = getParentOptional();
            if (p.isPresent())
            {
                node_optional l = p.get()->getLeftOptional();
                return l.isPresent()  && l.get() == this;
            }
            return false;
        }

//        virtual void  print(logArray &list, size_t level, int maxWidth) = 0;
        virtual  void  print(Trunk *prev) = 0;





    };

    template<class T, typename  ref>
    class LeafNode : public ft::Node<T , ref> {
    public:
         node_type getType() const {return LEAF;}

         ~LeafNode(){}
         LeafNode(): Node<T, ref>(){}

        void print(Trunk *prev)
        {
            std::string prev_str = "    ";
            Trunk *trunk = new Trunk(prev, prev_str);
            if (!prev) { trunk->str = "——— "; }
            else if (this->whoAmI()) { trunk->str = " .——— "; prev_str = "   |"; }
            else {
                trunk->str = " `——— ";
                prev->str = prev_str;
            }
            showTrunks(trunk);
            std::cout <<"(LEAF)" << std::endl;
            delete trunk;
        }
         size_t  getHeight() {return 1;}
    };

    template<class T, typename ref>
    class ValueNode : public ft::Node<T, ref> {
    public:
        typedef  typename ft::Node<T, ref>::value_type value_type;
        typedef typename ft::Node<T, ref>::node_pointer  node_pointer;
        node_type getType() const { return REGULAR;}
        ~ValueNode(){}

//        explicit ValueNode(value_type const &value):
//        ValueNode(value, nullptr, nullptr){};
//        ValueNode(value_type const &value, node_pointer left,node_pointer right):
//                            ValueNode(value, left, right, nullptr){}
       explicit ValueNode(value_type const   &value, node_pointer left,
                  node_pointer right, node_pointer parent)
        :
        Node<T, ref>(value, left, right, parent)
        {}
        ValueNode(ft::ValueNode<T, ref> const &rhs):
          ft::Node<T, ref>(rhs)
        {
        }

//        void print(logArray &list, size_t level, int maxWidth){
//        {
//
//        }
            void print( Trunk *prev) {

//            std::cout << indent;
//       if (!this->whoAmI()) {
//         std::cout << "R----  ";
//         indent += "   ";
//       } else {
//         std::cout << "L----  ";
//         indent += "|  ";
//       }
//
//            bool isRed = this->getColor() == RED;
//              std::string sColor = (isRed ? "R": "B");
//              std::cout <<(isRed? _RED : "" )<< *this->getValue() <<" (" << sColor <<  ")" << _WHITE << std::endl;
//              this->getLeft()->print(indent);
              //this->getRight()->print(indent);
              std::string prev_str = "    ";
              Trunk *trunk = new Trunk(prev, prev_str);
              this->getRight()->print(trunk);
              if (!prev) { trunk->str = "——— "; }
              else if (this->whoAmI()) { trunk->str = " .——— "; prev_str = "   |"; }
              else {
                  trunk->str = " `——— ";
                  prev->str = prev_str;
              }
              showTrunks(trunk);

              std::string sColor = (this->isRed() ? "R": "B");
              std::cout
              << (this->isRed() ? _RED : "")
              <<  *this->getValue()
              << " (" << sColor
              << " "
              << (this->whoAmI() ? "LEFT" : "RIGHT")
              <<  " ";
              if (!this->isParentLeaf())
                  std::cout <<   *this->getParent()->getValue();
              std::cout <<" )"
              << _WHITE << std::endl;
              if (prev) {
                  prev->str = prev_str;
              }
              trunk->str = "   |";
              this->getLeft()->print(trunk);
              delete trunk;
          }

        size_t  getHeight() {
            int value = 0;
             if (this->getColor() == BLACK)
                 value = 1;
              return value +  std::max(this->getRight()->getHeight(), this->getLeft()->getHeight());
        }
    };

}