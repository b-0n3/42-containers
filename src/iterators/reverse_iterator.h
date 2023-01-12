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
        typename ft::IteratorTraits<Iter>::value_type> {

public:
    typedef typename ft::IteratorTraits<Iter>::difference_type difference_type;
    typedef typename ft::IteratorTraits<Iter>::value_type value_type;
    typedef typename ft::IteratorTraits<Iter>::pointer pointer;
    typedef typename ft::IteratorTraits<Iter>::reference reference;
    typedef typename ft::IteratorTraits<Iter>::iterator_category iterator_category;
private:
    Iter _current;
public:
    reverse_iterator() : _current() {}

    explicit reverse_iterator(Iter x) : _current(x) {}

    template <class _Iter>
    reverse_iterator (const reverse_iterator<_Iter>& rev_it)
    {
        _current = rev_it.base();
    }


    Iter base() const {
        return _current;
    }


    reference operator*() const {
        Iter _tmp = _current;
        --_tmp;
        return *_tmp;
    }

    pointer operator->() const {
        return &(operator*());
    }

    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(_current - n);
    }

    reverse_iterator &operator++() {
        --_current;
        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator tmp(*this);
        --_current;
        return tmp;
    }

    reverse_iterator &operator+=(difference_type n) {
        _current -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(_current + n);
    }

    reverse_iterator &operator--() {
        ++_current;
        return *this;
    }

    reverse_iterator operator--(int) {
        reverse_iterator tmp (*this);
        ++_current;
        return tmp;
    }

    reverse_iterator &operator-=(difference_type n) {
        _current += n;
        return *this;
    }


    reference operator[] (difference_type n) const
    {
        return *(_current - n - 1);
    }
};
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it
            )
    {
        return (rev_it + n);
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (&(*rhs.base()) - &(*lhs.base()));
    }
    template <class Iterator>
    bool operator== (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (lhs.base() == rhs.base());
    }
    template <class Iterator>
    bool operator!= (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (lhs.base() != rhs.base());
    }
    template <class Iterator>
    bool operator< (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (lhs.base() > rhs.base());
    }
    template <class Iterator>
    bool operator<= (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (lhs.base() >= rhs.base());
    }
    template <class Iterator>
    bool operator> (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (lhs.base() < rhs.base());
    }
    template <class Iterator>
    bool operator>= (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs
            )
    {
        return (lhs.base() <= rhs.base());
    }




}
#endif //FT_CONTAINERS_REVERSE_ITERATOR_H
