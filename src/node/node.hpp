//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma  once

#include <iostream>
#include <iomanip>
#include <sstream>
#include "color.hpp"
#include "NodeType.hpp"
#include "../utility/Forward.hpp"
#include "../vector/Vector.hpp"
#include "../optional/optional.hpp"

namespace ft {
    struct Trunk {
        Trunk *prev;
        std::string str;
        Trunk( Trunk *prev, std::string str ) { this->prev = prev; this->str = str; }
    };
    void showTrunks(Trunk *p) {
        if (p == nullptr) {
            std::cout << std::endl;
            return ;
        }

        showTrunks(p->prev);
        std::cout << p->str;
    }
    template<class T>
    class Node {
    public:
        typedef T value_type;
        typedef ft::Node<T> node_t;
        typedef ft::Node<T> *node_pointer;
        typedef ft::Node<T> &node_reference;
        typedef ft::Optional<node_pointer> node_optional;
        typedef ft::Optional<bool *> bool_optional;

        Node() :
                value(null),
                parent(null),
                left(null),
                right(null),
                color(BLACK) {
        }

        virtual node_type getType() = 0;

        virtual ~Node() {}

        Node(ft::Node<T> const &rhs) :
                value(rhs.value),
                parent(rhs.parent),
                left(rhs.left),
                right(rhs.right),
                color(rhs.color) {}

        virtual size_t getHeight() = 0;

        ft::Node<T> &operator=(ft::Node<T> const &rhs) {
            if (this == &rhs)
                return *this;
            value = rhs.value;
            parent = rhs.parent;
            left = rhs.parent;
            right = rhs.right;
            color = rhs.color;
            return *this;
        }
        node_optional getSiblingOptional()
        {
            if (getType() == LEAF)
                return node_optional::empty();
            node_optional p = getParentOptional();
            if (p.isPresent())
            {
                if (whoAmI())
                    return p.get()->getRightOptional();
                return p.get()->getLeftOptional();
            }
            return node_optional::empty();
        }

        node_optional  getParentOptional()
        {
             return node_optional::ofNullable(parent);
        }
        node_optional getLeftOptional()
        {
            if (getType() == LEAF)
                return node_optional::empty();
            return Optional<node_pointer>::ofNullable(left);
        }

        node_optional getRightOptional()
        {
            if (getType() == LEAF)
                return node_optional::empty();
            return node_optional::ofNullable(right);
        }
        bool isBothChildsBlack()
        {
            node_optional l = getLeftOptional();
            node_optional r = getRightOptional();
            return l.isPresent() && !l.get()->isRed()&&
                            r.isPresent() && !r.get()->isRed();
        }
        node_pointer getUncle()
        {
           if (whoAmI())
           {
               return getParent()->getRight();
           }
           return getParent()->getLeft();
        }

        node_pointer getSibling(bool r)
        {
            if (r)
                return getParent()->getRight();
            return getParent()->getLeft();
        }

        bool isUncleRed()
        {
            return getUncle()->isRed();
        }
        bool isParentBlack()
        {
            return !getParent()->isRed();
        }
        bool isRed(){
            return color == RED;
        }
        void makeMeBlack()
        {
            setColor(BLACK);
        }
        void makeMeRed()
        {
            if (!isLeaf())
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
        void makeUncleRed()
        {
            getUncle()->makeMeRed();
        }
        void makeUncleBlack()
        {
            getUncle()->makeMeBlack();
        }

        node_pointer getGrandParent()
        {
            return this->getParent()->getParent();
        }
        bool isLeaf()
        {
            return getType() == LEAF;
        }
        bool  isLeftLeaf()
        {
            return left->isLeaf();
        }
        bool isRightLeaf()
        {
            return right->isLeaf();
        }


        bool isParentLeaf()
        {
            return getParent() == null || getParent()->isLeaf();
        }
        void setValue(value_type v)
        {
            value = v;
        }
        value_type getValue(){
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
        bool whoAmI()
        {
            if (getType() == LEAF)
                return true;
            return this->getParent()->getLeft() == this;
        }
//        virtual void  print(logArray &list, size_t level, int maxWidth) = 0;
        virtual  void  print(Trunk *prev) = 0;

    protected:
        Node(value_type const value,node_pointer left, node_pointer right, node_pointer parent):
        value(value),
        parent(parent),
        left(left),
        right(right),
        color(RED)
        {}
        value_type value;
        node_pointer parent;
        node_pointer left;
        node_pointer right;
        Color color;




    };

    template<class T>
    class LeafNode : public ft::Node<T> {
    public:
         node_type getType() {return LEAF;}

         ~LeafNode(){}
         LeafNode(): Node<T>(){}
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
        }
         size_t  getHeight() {return 0;}
    };

    template<class T>
    class ValueNode : public ft::Node<T> {
    public:
        typedef  typename ft::Node<T>::value_type value_type;
        typedef typename ft::Node<T>::node_pointer  node_pointer;
        node_type getType() { return REGULAR;}
        ~ValueNode(){}

//        explicit ValueNode(value_type const &value):
//        ValueNode(value, nullptr, nullptr){};
//        ValueNode(value_type const &value, node_pointer left,node_pointer right):
//                            ValueNode(value, left, right, nullptr){}
       explicit ValueNode(value_type const   &value, node_pointer left,
                  node_pointer right, node_pointer parent)
        :
        Node<T>(value, left, right, parent)
        {}
        ValueNode(ft::ValueNode<T> const &rhs):
          ft::Node<T>(rhs)
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
          }

        size_t  getHeight() {
            return 1 +  std::max(this->getRight()->getHeight(), this->getLeft()->getHeight());
        }
    };

}