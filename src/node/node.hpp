//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma  once
#include "color.hpp"
#include "NodeType.hpp"
namespace ft {
    template<class T>
    class Node {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T &referance;
        Node() :
                value(nullptr),
                parent(nullptr),
                left(nullptr),
                right(nullptr),
                color(BLACK) {
        }
        virtual  node_type  getType() = 0;
    protected:
        Node(value_type &value, Node *left, Node *right, Node *parent):
        value(&value),
        parent(parent),
        left(left),
        right(right),
        color(RED)
        {}
        pointer value;
        Node *parent;
        Node *left;
        Node *right;
        Color color;
        virtual void printNode() = 0;
        referance getValue(){
            return *value;
        }
    };

    template<class T>
    class LeafNode : public Node<T> {
    public:
         node_type getType() {return LEAF;}
         LeafNode(): Node<T>(){}
    };

    template<class T>
    class ValueNode : public Node<T> {
    public:
        typedef  typename Node<T>::value_type value_type;
        node_type getType() { return REGULAR};
        ValueNode(value_type value):
        ValueNode(value, nullptr, nullptr){};
        ValueNode(value_type  value, Node<T> *left, Node<T> *right):
                            ValueNode(value, left, right, nullptr){}
        ValueNode(value_type  &value, Node<T> *left, Node<T> *right, Node<T> *parent)
        :
        Node<T>(value, left, right, parent)
        {}
    };
}