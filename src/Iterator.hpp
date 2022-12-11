//
// Created by Abdelouahad Ait hamd on 12/5/22.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP
#include "IteratorTraits.h"
#include <cstddef>
namespace ft{
    template<class Category, class T,
            class Distance = std::ptrdiff_t,
                    class Pointer = T*,
                            class Reference = T&>
    class Iterator{
    public:
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };
}
#endif //FT_CONTAINERS_ITERATOR_HPP
