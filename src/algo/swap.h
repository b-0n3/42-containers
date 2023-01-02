//
// Created by Abdelouahad Ait hamd on 1/2/23.
//
#pragma  once
namespace ft {
    template<class T>
    void swap(T &a, T &b)
    {
        T c(a);
        a = b;
        b = c;
    }
}