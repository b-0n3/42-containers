//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma once


namespace ft {
    template<class T1, class T2>
    struct Pair {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;

        Pair() {
            first = first_type();
            second = second_type();
        };

        template<class U, class V>
        Pair(const Pair<U, V> &pr) {
            first = pr.first;
            second = pr.second;
        };

        Pair(const first_type &a, const second_type &b) {
            first = a;
            second = b;
        };

        Pair &operator=(const Pair &pr) {
            first = pr.first;
            second = pr.second;
            return *this;
        };

    };
}