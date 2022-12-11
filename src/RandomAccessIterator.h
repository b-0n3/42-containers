//
// Created by Abdelouahad Ait hamd on 12/2/22.
//

#ifndef FT_CONTAINERS_RANDOMACCESSITERATOR_H
#define FT_CONTAINERS_RANDOMACCESSITERATOR_H
#include "Iterator.hpp"
#include <iterator>
namespace ft {

    template<class T>
    class RandomAccessIterator :
            public ft::Iterator<RandomAccessIterator<T>,
                    T>{
    private:
        T *_ptr;
    public:
        typedef typename ft::Iterator<RandomAccessIterator<T>, T>::iterator_category iterator_category;
        typedef typename ft::Iterator<RandomAccessIterator<T>, T>::value_type value_type;
        typedef typename ft::Iterator<RandomAccessIterator<T>, T>::difference_type difference_type;
        typedef typename ft::Iterator<RandomAccessIterator<T>, T>::pointer pointer;
        typedef typename ft::Iterator<RandomAccessIterator<T>, T>::reference reference;
    public:
        RandomAccessIterator() : _ptr(nullptr) {}
        template<class iter>
        RandomAccessIterator(iter  const &other) {
            *this = other;
        }

        RandomAccessIterator(T *ptr) : _ptr(ptr) {}



        RandomAccessIterator &operator=( RandomAccessIterator const  &other) {
            if (this != &other) {
                _ptr = other._ptr;
            }
            return *this;
        }
        template < class iter>
        RandomAccessIterator &operator=( iter const  &other) {
            if (this != &other) {
                _ptr = other._ptr;
            }
            return *this;
        }

        RandomAccessIterator &operator=(T *ptr) {
            _ptr = ptr;
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

        RandomAccessIterator& operator++() {
            _ptr++;
            return *this;
        }
        RandomAccessIterator operator++(int) const {

            return RandomAccessIterato(_ptr++);
        }
        RandomAccessIterator& operator--() {
            _ptr--;
            return *this;
        }
        RandomAccessIterator operator--(int)   {
            return RandomAccessIterator(_ptr--);
        }
        RandomAccessIterator operator+(difference_type n) const {
            return RandomAccessIterator(_ptr + n);
        }
        RandomAccessIterator operator-(difference_type n) const {
            return RandomAccessIterator(_ptr - n);
        }

        difference_type  operator-(const RandomAccessIterator &other) const {
            return _ptr - (other._ptr);
        }
        difference_type  operator+(const RandomAccessIterator &other) const {
            return _ptr + (other._ptr);
        }
        bool operator>(const RandomAccessIterator &other) const {
            return _ptr > other._ptr;
        }
        bool operator<(const RandomAccessIterator &other) const {
            return _ptr > other._ptr;
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
            return _ptr + n;
        }




    };
    template<class T>
    RandomAccessIterator<T> operator+(typename RandomAccessIterator<T>::difference_type n, RandomAccessIterator<T> const &other) {
        return other + n;
    }
    template<class T>
    RandomAccessIterator<T> operator-(typename RandomAccessIterator<T>::difference_type n, RandomAccessIterator<T> const &other) {
        return other - n;
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
#endif //FT_CONTAINERS_RANDOMACCESSITERATOR_H
