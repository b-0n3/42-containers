//
// Created by Abdelouahad Ait hamd on 11/29/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <stdexcept>
#include <iostream>
#include "RandomAccessIterator.h"
#include "IteratorTraits.h"
#include "reverse_iterator.h"
#include "Forward.hpp"
#include "exceptions/OutOfBoundExecption.h"

namespace  ft {
    template<class T, class Alloc = std::allocator <T> >
    class Vector {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RandomAccessIterator<T> iterator;
        typedef RandomAccessIterator<const T> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef typename IteratorTraits<iterator>::difference_type difference_type;
        typedef size_t size_type;
    private:
        pointer _data;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;
    public:
        Vector(const allocator_type &alloc = allocator_type())
                : _data(nullptr), _size(0), _capacity(0), _alloc(alloc) {}

        Vector(size_type n,
               const value_type &val = value_type(),
               const allocator_type &alloc = allocator_type()) :
                _data(nullptr), _size(0), _capacity(0), _alloc(alloc) {
            // @Todo : insert values;
            assign(n, val);
        }

        template<class InputIterator>
        Vector(InputIterator first, InputIterator last,
               const allocator_type &alloc = allocator_type())
                : _data(nullptr), _size(0), _capacity(0), _alloc(alloc) {
            // @ todo: f(first, last, alloc, InputIterator::iterator_category())
            // @Todo : check for the iterator category
            assign(first, last);
        }


        Vector(const Vector &other) {
            *this = other;
        }

        Vector &operator=(const Vector &other) {
            if (this != &other) {
                _size = other._size;
                _capacity = other._capacity;
                _size = other._size;
                _data = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++) {
                    _alloc.construct(_data + i, other._data[i]);
                }
            }
            return *this;
        }

        ~Vector() {
            if (_data != nullptr) {
                for (size_type i = 0; i < _size; i++) {
                    _alloc.destroy(_data + i);
                }
                _alloc.deallocate(_data, _capacity);
            }
        }

        /* *****  modifiers ****/

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last)
        {

           switch(first.iterator_category) {
               case std::input_iterator_tag():
               case std::output_iterator_tag():
               case std::forward_iterator_tag():
               case std::bidirectional_iterator_tag():
                   assign_bidirectionalIterator(first, last);
                   break;
               default:
                   assign_randomAccessIterator(first, last);
                   break;
           }
        }
    private:
       template<class InputIterator>
       void assign_bidirectionalIterator(InputIterator first, InputIterator last)
       {
          clear();
            while (first != last)
            {
                 push_back(*first);
                 first++;
            }
       }
       template<class InputIterator>
       void assign_randomAccessIterator(InputIterator first, InputIterator last)
       {
           clear();
           size_type n = last - first;
           if (n > _capacity)
           {
               _capacity = n;
               _data = _alloc.allocate(_capacity);
           }
           for (size_type i = 0; i < n; i++)
           {
               _alloc.construct(_data + i, first[i]);
           }
           _size = n;
       }
    public:
        void assign(size_type n, const value_type &val) {
            clear();
            reserve(n);
            insert(begin(), n , val);
        }
        void push_back(const value_type &val) {
            if (_size == _capacity) {
                reserve(_capacity + 1);
            }
            _alloc.construct(_data + _size, val);
            _size++;
        }
        void pop_back(){
            if (_size > 0) {
                _alloc.destroy(_data + _size - 1);
                _size--;
            }
        }
        iterator insert(iterator position, const value_type &val) {
            if (_size == _capacity)
                reserve(_size + 1);
            iterator first = begin();
            difference_type index = position - first;
            if (index == _size) {
                _alloc.construct(_data + _size, val);
                _size++;
            } else {
                for (size_type i = _size; i > index; i--) {
                    _alloc.construct(_data + i, _data[i - 1]);
                    _alloc.destroy(_data + i - 1);
                }
                _alloc.construct(_data + index, val);
                _size++;
            }
            _size++;
            return position;
        }



        void insert(iterator position, size_type n, const value_type &val)
        {
            if (_size + n > _capacity)
                reserve(_size + n);

            difference_type index = position - begin();

            if (index == _size) {
                for (size_type i = 0; i < n; i++) {
                    _alloc.construct(_data + _size + i, val);
                }
            } else {
                for (size_type i = _size; i > index; i--) {
                    _alloc.construct(_data + i + n - 1, _data[i - 1]);
                    _alloc.destroy(_data + i - 1);
                }
                for (size_type i = 0; i < n; i++) {
                    _alloc.construct(_data + index + i, val);
                }
            }
            _size += n;
        }
        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            switch (first.itertor_category) {
                case std::input_iterator_tag():
                case std::output_iterator_tag():
                case std::forward_iterator_tag():
                case std::bidirectional_iterator_tag():
                    insert_bidirectionalIterator(position, first, last);
                    break;
                default:
                    insert_randomAccessIterator(position, first, last);
                    break;
            }
        }
    private:
        template <class InputIterator>
        void insert_bidirectionalIterator(iterator position, InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                position = insert(position, *first);
                first++;
                position++;
            }
        }

        template <class InputIterator>
        void insert_randomAccessIterator(iterator position, InputIterator first, InputIterator last)
        {
            size_type n = last - first;
            if (_size + n > _capacity)
                reserve(_size + n);

            difference_type index = position - begin();

            if (index == _size) {
                for (size_type i = 0; i < n; i++) {
                    _alloc.construct(_data + _size + i, first[i]);
                }
            } else {
                for (size_type i = _size; i > index; i--) {
                    _alloc.construct(_data + i + n - 1, _data[i - 1]);
                    _alloc.destroy(_data + i - 1);
                }
                for (size_type i = 0; i < n; i++) {
                    _alloc.construct(_data + index + i, first[i]);
                }
            }
            _size += n;
        }
    public:


        iterator erase (iterator position) {
            if (position < begin() || position >= end()) {
                return end();
            }
            difference_type index = position - begin();
            _alloc.destroy(_data + index);
            for (size_type i = index; i < _size - 1; i++)
            {
                _alloc.construct(_data + i, _data[i + 1]);
                _alloc.destroy(_data + i + 1);
            }
            _size--;
            return begin() + index;
        }

        iterator erase (iterator first, iterator last)
        {
            if (first < begin() || first >= end() || last < begin() || last >= end()) {
                return end();
            }
            difference_type index = first - begin();
            difference_type size = last - first;
            for (size_type i = index; i <_size ; i++)
                _alloc.destroy(_data + i);
            for (size_type i = index; i < _size - size; i++)
            {
                _alloc.construct(_data + i, _data[i + size]);
                _alloc.destroy(_data + i + size);
            }
            return begin() + index;
        }
        void swap (Vector& x)
        {
            Vector tmp = *this;
            *this = x;
            x = tmp;
        }
        void clear() {
            if (_data != nullptr) {
                for (size_type i = 0; i < _size; i++) {
                    _alloc.destroy(_data + i);
                }
                _size = 0;
            }
        }
//        template <class... Args>
//        iterator emplace (const_iterator position, Args&&... args)
//        {
//            value_type  elements[] = {args...};
//            difference_type  size = sizeof...(args);
//            difference_type index = position - begin();
//            reserve(_size + size);
//            if (index == _size) {
//                for (size_type i = 0; i < size; i++)
//                    push_back(elements[i]);
//            } else {
//                for (size_type i = index; i <_size ;i++)
//                {
//                    _alloc.construct(_data + i + size, _data[i]);
//                    _alloc.destroy(_data + i);
//                }
//                for (size_type i = 0; i < size; i++)
//                    _alloc.construct(_data + index + i, elements[i]);
//                _size += size;
//            }
//            return begin() + index;
//        }
//        template <class... Args>
//        void emplace_back (Args&&... args)
//        {
//            value_type elements[] = {args...};
//            difference_type size = sizeof...(args);
//            reserve(_size + size);
//            for (size_type i = 0; i < size; i++)
//                push_back(elements[i]);
//        }

        ///  element Access
        reference operator[](size_type n) {
            return _data[n];
        }
        const_reference operator[](size_type n) const {
            return _data[n];
        }
        reference at(size_type n) {
            if (n >= _size)
                throw ft::OutOfBoundExecption("vector::at");
            return _data[n];
        }
        const_reference at(size_type n) const {
            if (n >= _size)
                throw ft::OutOfBoundExecption("vector::at -> const_reference");
            return _data[n];
        }
        reference front() {
             return _data[0];
        }
        const_reference front() const {
                return _data[0];
        }
        reference back() {
                return _data[_size - 1];
        }
        const_reference back() const {
                return _data[_size - 1];
        }
        pointer data() {
            return _data;
        }
       const_pointer data() const {
            return  _data;
        }
        // Capacity
        size_type size() const {
            return _size;
        }
        size_type max_size() const {
            return _alloc.max_size();
        }

        void reserve(size_type n)
        {
            if (_capacity > n + _size)
                return ;
            size_type  old_capacity = _capacity;
            if ((_capacity * GOLDEN_RATIO) < (n + size() + 1) )
                _capacity = n + size()  + 1;
            else
                _capacity = _capacity * GOLDEN_RATIO;
            pointer tmp = _alloc.allocate(_capacity);
          if (_data != nullptr) {
              for (size_type i = 0; i < _size; i++) {
                  _alloc.construct(tmp + i, _data[i]);
                  _alloc.destroy(_data + i);
              }
              _alloc.deallocate(_data, old_capacity);
          }
          _data = tmp;
        }
        size_type capacity() const {
            return _capacity;
        }
        bool empty() const {
            return _size == 0;
        }
        void shrink_to_fit() {
            if (_capacity > _size) {
                pointer tmp = _alloc.allocate(_size);
                for (size_type i = 0; i < _size; i++) {
                    _alloc.construct(tmp + i, _data[i]);
                    _alloc.destroy(_data + i);
                }
                _alloc.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = _size;
            }
        }


   // iterators:
        iterator begin() const {
            return iterator(_data);
        }
        const_iterator cbegin() const {
            return const_iterator(_data);
        }
        iterator end()  const{
            return iterator(_data + _size);
        }
        const_iterator cend() const {
            return const_iterator(_data + _size);
        }
        reverse_iterator rbegin() const {
            return reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend() const{
            return reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }
        allocator_type get_allocator() const
        {
            return _alloc;
        }
    };

    template <class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }
    template <class T, class Alloc>
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
    bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        size_t i = 0;
        while (i < lhs.size() && i < rhs.size())
        {
            if (lhs[i] < rhs[i])
                return true;
            else if (lhs[i] > rhs[i])
                return false;
            i++;
        }
        if (i == lhs.size() && i != rhs.size())
            return true;
        return false;
    }
    template <class T, class Alloc>
    bool operator <= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return  !(lhs > rhs);
    }
    template <class T, class Alloc>
    bool operator> (const Vector<T, Alloc> & lhs, const Vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }
    template<class T, class Alloc>
    bool operator>= (const Vector<T, Alloc> & lhs, const Vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
    {
        Vector<T, Alloc> tmp = x;
        x.swap(y);
        y.swap(tmp);
    }
};
#endif //FT_CONTAINERS_VECTOR_HPP
