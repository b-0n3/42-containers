//
// Created by Abdelouahad Ait hamd on 11/29/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <stdexcept>
#include <iostream>
#include "../iterators/RandomAccessIterator.h"
#include "../iterators/IteratorTraits.h"
#include "../iterators/reverse_iterator.h"
#include "../utility/Forward.hpp"
#include "../exceptions/OutOfBoundExecption.h"

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
        typedef RandomAccessIterator<value_type> iterator;
        typedef RandomAccessIterator<const  value_type> const_iterator;
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
               const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
                : _data(nullptr), _size(0), _capacity(0), _alloc(alloc) {
            assign(first, last);
        }


        Vector(const Vector &other) {
            *this = other;
        }

        Vector &operator=(const Vector &other) {
            if (this != &other) {
                _size = other.size();
                _capacity = other.capacity();
                _data = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_data + i, other[i]);
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
        void assign (InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
            {
                clear();
                difference_type  n = std::distance(first, last);
                reserve(n);
                for (difference_type i = 0; i < n; i++) {
                   _alloc.construct(_data + i, *first);
                   _size++;
                    first++;
                }
           }
        }

        void assign(size_type n, const value_type &val) {
            clear();
            insert(begin(), n , val);
        }
        void push_back(const value_type &val) {
            if (_size == _capacity) {
                if (_capacity == 0) {
                    reserve(1);
                } else {
                    reserve(_capacity * 2);
                }
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
        void resize (size_type n, value_type val = value_type())
        {
            if (n > max_size())
                return ;
            if (n < _size)
            {
                for (size_type i = n; i < _size; i++)
                    _alloc.destroy(_data + i);
                _size  = n;
            }
            else if (n > _size)
            {
                if (n > _capacity)
                    reserve(n);

                for (size_type i = _size; i < n; i++)
                    _alloc.construct(_data + i, val);
                _size = n;
            }
        }
        iterator insert(iterator position, const value_type &val) {


            size_type index = position - begin();
            if (index > _size) {
                index = _size;
            }
            if (_size == _capacity || _size + 1 == _capacity)
                reserve(_capacity ==  0 ? 1: _capacity * 2);
            else
                reserve(_size + 1);
            for (size_type i = _size; i > index; i--) {
                _alloc.construct(_data + i, _data[i - 1]);
                _alloc.destroy(_data + i - 1);
            }
            _alloc.construct(_data + index, val);
            _size++;
            return begin() + index;
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
             size_type index = position - begin();
//             size_type n_copy = n;
             if (index > _size)
                  index = _size;
                if (size() + n <= size() * 2)
                    reserve(size() * 2);
                else
                    reserve(size() + n );

             if (index < _size) {
                 for (size_type i = 0; i < _size - index; i++) {
                     _alloc.construct(_data + index + n + i, _data[index + i]);
                     _alloc.destroy(_data + index + i);
                 }
             }
             for (size_type i = 0; i < n; i++)
                 _alloc.construct(_data + i + index, val);

             _size += n;
        }
        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
        {
            size_type index = position - begin();
            if (index > _size)
                index = _size;
            size_type n = std::distance(first, last);

            if (size() + n <= size() * 2)
                reserve(size() * 2);
            else
                reserve(size() + n );

            if (index < _size) {
                for (size_type i = 0; i < _size - index; i++) {
                    _alloc.construct(_data + index + n + i, _data[index + i]);
                    _alloc.destroy(_data + index + i);
                }
            }
            for (size_type i = 0; i < n; i++) {
                _alloc.construct(_data + i + index, *first);
                first++;
            }
            _size += n;
        }

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
            if (first < begin() || first >= end() || last <= begin() || last > end()) {
                return end();
            }
            size_type index = std::distance(begin(), first);
            size_type size = std::distance(first, last);
            for (size_type i =0 ; i < size; i++)
                _alloc.destroy(_data + index + i);
            for ( size_type i = 0; i < _size - index - size; i++)
            {
                _alloc.construct(_data  + index + i, _data[index + size + i]);
                _alloc.destroy(_data + index + size  + i);
            }
            _size -= size;
            return begin() + index;
        }
        void swap (Vector& x)
        {
            size_type xSize = x.size();
            size_type xCapacity = x.capacity();
            pointer xData = (pointer) x.data();
            x._data = _data;
            x._size = _size;
            x._capacity = _capacity;
            _data = xData;
            _size = xSize;
            _capacity = xCapacity;
        }
        void clear() {
            if (_data != nullptr) {
                for (size_type i = 0; i < _size; i++) {
                    _alloc.destroy(_data + i);
                }
                _size = 0;
            }
        }

        ///  element Access
        reference operator[](size_type n) {
            return _data[n];
        }
        const_reference operator[](size_type n) const {
            return _data[n];
        }
        reference at(size_type n) {
            if (n >= _size)
                throw std::out_of_range("out of range");
            return _data[n];
        }
        const_reference at(size_type n) const {
            if (n >= _size)
                throw std::out_of_range("vector::at -> const_reference");
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

        void reserve(size_type  n)
        {
//            if (n > max_size())
//                return ;

            if ( _capacity < n)
            {
                pointer tmp = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++)
                {
                    _alloc.construct(tmp + i, _data[i]);
                    _alloc.destroy(_data + i);
                }
                _alloc.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = n;
            }
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
        iterator begin()  {
            return iterator(_data);
        }
        const_iterator begin() const {
            return const_iterator(_data);
        }
        const_iterator cbegin() const {
            return const_iterator(_data);
        }
        iterator end()  {
            return iterator(_data + (_size )  );
        }
        const_iterator end() const {
            return const_iterator(_data + (_size )  );
        }

        const_iterator cend() const {
            return const_iterator(_data + (_size) );
        }
        reverse_iterator rbegin()  {
            return reverse_iterator(_data + _size  ) ;
        }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_data + _size  ) ;
        }

        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(_data + _size );
        }
         reverse_iterator rend() {
            return reverse_iterator(_data );
        }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(_data );
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(_data );
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
        return lhs < rhs || lhs == rhs;
    }
    template <class T, class Alloc>
    bool operator> (const Vector<T, Alloc> & lhs, const Vector<T, Alloc> &rhs)
    {
        return !(lhs <= rhs);
    }
    template<class T, class Alloc>
    bool operator>= (const Vector<T, Alloc> & lhs, const Vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
    {
        x.swap(y);
    }
};
#endif //FT_CONTAINERS_VECTOR_HPP
