//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma  once

#include <iostream>
#include <iomanip>
#include "color.hpp"
#include "NodeType.hpp"
#include "../utility/Forward.hpp"
namespace ft {
    template<class T>
    class Node {
    public:
        typedef T value_type;
        typedef ft::Node<T> node_t;
        typedef ft::Node<T> *node_pointer;
        typedef ft::Node<T>& node_reference;
        Node() :
                value(null),
                parent(null),
                left(null),
                right(null),
                color(BLACK) {
        }
        virtual  node_type  getType() = 0;
        virtual ~Node(){}
        Node(ft::Node<T> const &rhs):
        value(rhs.value),
        parent(rhs.parent),
        left(rhs.left),
        right(rhs.right),
        color(rhs.color)
        {}
        virtual size_t  getHeight() = 0;
        ft::Node<T> &operator=(ft::Node<T> const &rhs)
        {
            if (this == &rhs)
                return *this;
            value = rhs.value;
            parent = rhs.parent;
            left= rhs.parent;
            right = rhs.right;
            color = rhs.color;
                return *this;
        }
        node_pointer getUncle(bool isLeft)
        {
            ft::Node<T> *grandParent = getGrandParent();
           return isLeft ? grandParent->getLeft() : grandParent->getRight();
        }
        node_pointer getGrandParent()
        {
            return this->getParent()->getParent();
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
        virtual void  print() = 0;
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
         void print(){
              std::cout  << "LEAF";
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

        void print()
        {
            size_t h = this->getHeight();

             std::cout << " " << std::setw(h * 4)  << (this->getColor() == RED ? " RED": "BLACK") << std::endl;
            this->getLeft()->print();  std::cout << "  /  "  ;
            std::cout << "  \\  " ;  this->getRight()->print();


        }
        size_t  getHeight() {

            return 1 +  std::max(this->getRight()->getHeight(), this->getLeft()->getHeight());
        }
    };
//    template<class T>
//    std::ostream &operator<<(std::ostream &os, ft::ValueNode<T> &rhs)
//    {
//        size_t h = rhs.getHeight();
//        os<< std::setw((int) h * 4);
//         os << rhs.getValue() << (rhs.getColor() == RED ? _RED : _WHITE );
//         os << std::endl;
//         os << std::setw(((int ) (h * 4)) - 6 ) << "/" << "     \\" << std::endl;
//         return os;
//    }
//
//    template<class T>
//    std::ostream  &operator<<(std::ostream &os, ft::LeafNode<T> &rhs)
//    {
//        if (rhs.getType() == LEAF)
//            os << "LEAF" <<  std::endl;
//        return os;
//    }
//    template<class T>
//    std::ostream  &operator<<(std::ostream &os, ft::Node<T> &rhs)
//    {
//        if (rhs.getType() == LEAF)
//            os << ((ft::LeafNode<T> *) &rhs);
//        else if (rhs.getType() == REGULAR)
//            os << ((ft::ValueNode<T> *) &rhs);
//        return os;
//    }
}