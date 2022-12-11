//
// Created by Abdelouahad Ait hamd on 12/3/22.
//

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_H
#define FT_CONTAINERS_REVERSE_ITERATOR_H
#include "Iterator.hpp"
#include "RandomAccessIterator.h"
#include "IteratorTraits.h"
namespace  ft {
    template<class Iter>
class reverse_iterator :
public ft::Iterator<typename ft::IteratorTraits<Iter>::iterator_category,
        typename ft::IteratorTraits<Iter>::value_type>{

    public:
        typedef  typename  ft::Iterator<typename ft::IteratorTraits<Iter>::iterator_category,
                typename ft::IteratorTraits<Iter>::value_type>::difference_type difference_type;
        typedef typename   ft::Iterator<typename ft::IteratorTraits<Iter>::iterator_category,
                typename ft::IteratorTraits<Iter>::value_type>::value_type value_type;
        typedef typename   ft::Iterator<typename ft::IteratorTraits<Iter>::iterator_category,
                typename ft::IteratorTraits<Iter>::value_type>::pointer pointer;
        typedef typename   ft::Iterator<typename ft::IteratorTraits<Iter>::iterator_category,
                typename ft::IteratorTraits<Iter>::value_type>::reference reference;
        typedef typename   ft::Iterator<typename ft::IteratorTraits<Iter>::iterator_category,
                typename  ft::IteratorTraits<Iter>::value_type>::iterator_category iterator_category;
    private:
    pointer _ptr;
    public:
    reverse_iterator() : _ptr(nullptr) {}

    reverse_iterator( pointer const  ptr) : _ptr(ptr) {}

    reverse_iterator(const reverse_iterator<Iter> &other) {
            *this = other;
        }

    template<class iter>
    reverse_iterator(iter const  &other) {
            *this = other;
        }

        template <class iter>
        reverse_iterator &operator=(iter const  &other) {
            if (this != &other) {
                _ptr = other._ptr;
            }
            return *this;
        }

        iterator_category base() const {
            return reverse_iterator(_ptr--);
        }
        reverse_iterator &operator=(const reverse_iterator<Iter> &other) {
            if (this != &other) {
                _ptr = other._ptr;
            }
            return *this;
        }
        reference operator*() const {
            return *_ptr;
        }
        pointer operator->() const {
            return _ptr;
        }
        reverse_iterator &operator++() {
            _ptr--;
            return *this;
        }
        reverse_iterator operator++(int) const {

            return reverse_iterator(_ptr--);
        }
        reverse_iterator &operator--() {
            _ptr++;
            return *this;
        }
        reverse_iterator operator--(int) const {
            reverse_iterator tmp(*this);
            _ptr++;
            return tmp;
        }
        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(_ptr - n);
        }
        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(_ptr + n);
        }
        reverse_iterator &operator+=(difference_type n) {
            _ptr -= n;
            return *this;
        }
        reverse_iterator &operator-=(difference_type n) {
            _ptr += n;
            return *this;
        }
        reference operator[](difference_type n) const {
            return _ptr - n;
        }
    };

    template<class T>
    bool operator==(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() == rhs.base();
    }
    template<class T>
    bool operator!=(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() != rhs.base();
    }
    template<class T>
    bool operator<(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() > rhs.base();
    }
    template<class T>
    bool operator<=(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() >= rhs.base();
    }
    template<class T>
    bool operator>(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() < rhs.base();
    }
    template<class T>
    bool operator>=(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() <= rhs.base();
    }
    template<class T>
    reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &it) {
        return reverse_iterator<T>(it.base() - n);
    }
    template<class T>
    reverse_iterator<T> operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &it) {
        return reverse_iterator<T>(it.base() + n);
    }
    template<class T>
    typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() - rhs.base();
    }
    template<class T>
    typename reverse_iterator<T>::difference_type operator+(const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs) {
        return lhs.base() + rhs.base();
    }
}
#endif //FT_CONTAINERS_REVERSE_ITERATOR_H
