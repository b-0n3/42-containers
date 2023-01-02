//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma once
#include "../algo/swap.h"

namespace ft {
    template<class T1, class T2>
    class pair {
    public:
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;

        pair() {
            first = first_type();
            second = second_type();
        };

        template<class U, class V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {
        };

        pair(const first_type &a, const second_type &b) {
            first = a;
            second = b;
        };

        pair &operator=(const pair &pr) {
            first = pr.first;
            second = pr.second;
            return *this;
        };

        void swap (ft::pair<T1, T2> & pr)
        {
            ft::swap(first, pr.first);
            ft::swap(second, pr.second);
        }
    };
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first < rhs.first; }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }
    template <class T1, class T2>
    std::ostream &operator<<(std::ostream &os, ft::pair<T1, T2> &rhs)
    {
        os << "first" << rhs.first << "  second" << rhs.second ;
        return os;
    }
    template <class T1, class T2>
    void swap (pair<T1,T2>& x, pair<T1,T2>& y)
    {
        x.swap(y);
    }
    template<class T1, class T2>
    ft::pair<T1,  T2> make_pair(T1 first, T2 second)
    {
        return pair<T1, T2>(first, second);
    }

}