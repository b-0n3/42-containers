//
// Created by Abdelouahad Ait hamd on 12/2/22.
//

#pragma  once
#include "Iterator.hpp"
#include <iterator>
namespace ft {

    template<class T>
    class RandomAccessIterator :
            public ft::Iterator<std::random_access_iterator_tag,
                    T>{
    private:
        T *_ptr;
    public:
        typedef typename ft::Iterator<std::random_access_iterator_tag, T> ::iterator_category  iterator_category;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::value_type  value_type;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::pointer pointer;
        typedef typename ft::Iterator<std::random_access_iterator_tag, T>::reference reference;


        RandomAccessIterator() : _ptr(nullptr) {}
        RandomAccessIterator(const pointer   ptr) : _ptr(ptr) {}

        RandomAccessIterator(RandomAccessIterator  const   &rhs)  {
           _ptr = rhs._ptr;
        }

       operator RandomAccessIterator<const T> () const{
            return RandomAccessIterator<const T>(_ptr);
        }

        RandomAccessIterator &operator=(RandomAccessIterator const   &rhs)
        {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        ~RandomAccessIterator() {}

        bool operator==(const RandomAccessIterator &other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const RandomAccessIterator &other) const {
            return _ptr != other._ptr;
        }

        pointer  operator->() const {
            return _ptr;
        }
        reference operator*() const {
            return *_ptr;
        }

        RandomAccessIterator &operator++()   {
            _ptr++;
            return *this;
        }
        RandomAccessIterator operator++(int)   {

            return RandomAccessIterator(this->_ptr++);
        }
        RandomAccessIterator &operator--() {
            _ptr--;
            return *this;
        }
        RandomAccessIterator operator--(int)     {
            return RandomAccessIterator(_ptr--);
        }
        RandomAccessIterator operator+(difference_type n) const {
            return RandomAccessIterator(_ptr + n);
        }
        RandomAccessIterator operator-(difference_type n) const {
            return RandomAccessIterator(_ptr - n);
        }

        difference_type  operator-(const RandomAccessIterator &other) const {
            return _ptr - other._ptr;
        }
        difference_type  operator+(const RandomAccessIterator &other) const {
            return _ptr + other._ptr;
        }
        bool operator>(const RandomAccessIterator &other) const {
            return _ptr > other._ptr;
        }
        bool operator<(const RandomAccessIterator &other) const {
            return _ptr < other._ptr;
        }
        bool operator>=(const RandomAccessIterator &other) const {
            return _ptr >= other._ptr;
        }
        bool operator<=(const RandomAccessIterator &other) const {
            return _ptr <= other._ptr;
        }

        RandomAccessIterator operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }
        RandomAccessIterator operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }
        reference operator[](difference_type n) const {
            return _ptr[n];
        }




    };

    template<class T>
    RandomAccessIterator<T> operator+(typename RandomAccessIterator<T>::difference_type n, RandomAccessIterator<T> const &other) {
        return n + &(*other);
    }
    template<class T>
    RandomAccessIterator<T> operator-(typename RandomAccessIterator<T>::difference_type n, RandomAccessIterator<T> const &other) {
        return n -  &(*other);
    }
    template<class T>
    bool operator==(const T *ptr, const RandomAccessIterator<T> &other) {
        return ptr == other._ptr;
    }
    template<class T>
    bool operator!=(const T *ptr, const RandomAccessIterator<T> &other) {
        return ptr != other._ptr;
    }
};
