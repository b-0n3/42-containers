//
// Created by Abdelouahad Ait hamd on 1/9/23.
//

//
// Created by Abdelouahad Ait hamd on 12/2/22.
//

#pragma  once
#include "Iterator.hpp"
#include <iterator>
namespace ft {

    template<class T, typename  V, typename constValue>
    class BidirectionalIterator :
            public ft::Iterator<std::bidirectional_iterator_tag,
                    V>{

    public:
        typedef typename ft::Iterator<std::bidirectional_iterator_tag, V>::iterator_category  iterator_category;
        typedef typename ft::Iterator<std::bidirectional_iterator_tag, V>::value_type  value_type;
        typedef typename ft::Iterator<std::bidirectional_iterator_tag, V>::difference_type difference_type;
        typedef  constValue * pointer;
        typedef  constValue &reference;
        typedef   T * node_pointer;
    private:
        node_pointer _ptr;
    public:

        BidirectionalIterator() : _ptr(nullptr) {}
        BidirectionalIterator(const node_pointer   ptr) : _ptr(ptr) {}

        BidirectionalIterator(BidirectionalIterator  const   &rhs) {
            _ptr = rhs._ptr;
        }
        operator BidirectionalIterator< T,  V, const V> ()  const {
            return BidirectionalIterator<T,  V, const V> (_ptr);
        }
//        operator BidirectionalIterator<T , const V> () {
//            return BidirectionalIterator<T, const V>(_ptr);
//        }

        BidirectionalIterator &operator=( BidirectionalIterator const   &rhs)
        {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        ~BidirectionalIterator() {}

        bool operator==(const BidirectionalIterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const BidirectionalIterator &other) const {
            return _ptr != other._ptr;
        }

        pointer operator->() const {
            return _ptr->operator->();
        }
        reference operator*() const {
            return **_ptr;
        }

        BidirectionalIterator &operator++()   {
            _ptr = &((*_ptr)++);
            return *this;
        }
        const BidirectionalIterator operator++(int)      {
            node_pointer tmp = _ptr;
            _ptr = &((*_ptr)++);
            return BidirectionalIterator(tmp);
        }
        BidirectionalIterator &operator--() {
            _ptr = &((*_ptr)--);
            return *this;
        }
        const BidirectionalIterator operator--(int)     {
            node_pointer tmp = _ptr;
            _ptr = &((*_ptr)--);
            return BidirectionalIterator(tmp);
        }

    };

    template<class T, typename V,typename constValue>
    bool operator==(const T *ptr, const BidirectionalIterator<T, V,constValue> &other) {
        return ptr == other._ptr;
    }
    template<class T, typename V,typename constValue>
    bool operator!=(const T *ptr, const BidirectionalIterator<T, V,constValue> &other) {
        return ptr != other._ptr;
    }
};
