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

    template<class T, typename  V>
    class BidirectionalIterator :
            public ft::Iterator<std::bidirectional_iterator_tag,
                    T>{
    private:
        T *_ptr;
    public:
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::value_type  value_type;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::pointer pointer;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::reference reference;
        typedef  V &value_type_reference;
        typedef  V *value_type_pointer;


        BidirectionalIterator() : _ptr(nullptr) {}
        BidirectionalIterator(const pointer   ptr) : _ptr(ptr) {}

        BidirectionalIterator(BidirectionalIterator  const   &rhs)  {
            _ptr = rhs._ptr;
        }

        operator BidirectionalIterator< T, const V> () const{
            return BidirectionalIterator< T, const  V>(_ptr);
        }

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

        value_type_pointer operator->() const {
            return *_ptr;
        }
        value_type_reference operator*() const {
            return **_ptr;
        }

        BidirectionalIterator &operator++()   {
            _ptr = &((*_ptr)++);
            return *this;
        }
        const BidirectionalIterator operator++(int)      {
            pointer tmp = _ptr;
            _ptr = &((*_ptr)++);
            return BidirectionalIterator(tmp);
        }
        BidirectionalIterator &operator--() {
            _ptr = &((*_ptr)--);
            return *this;
        }
        const BidirectionalIterator operator--(int)     {
            pointer tmp = _ptr;
            _ptr = &((*_ptr)--);
            return BidirectionalIterator(tmp);
        }

    };

    template<class T, typename V>
    bool operator==(const T *ptr, const BidirectionalIterator<T, V> &other) {
        return ptr == other._ptr;
    }
    template<class T, typename V>
    bool operator!=(const T *ptr, const BidirectionalIterator<T, V> &other) {
        return ptr != other._ptr;
    }
};
