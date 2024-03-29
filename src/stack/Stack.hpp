//
// Created by Abdelouahad Ait hamd on 12/18/22.
//

#pragma  once

#include "../vector/Vector.hpp"
namespace  ft {
    template<class T, class Container = ft::vector<T> >
    class stack {
    public:

        typedef T value_type;
        typedef Container container_type;
        typedef typename  Container::size_type size_type;
        container_type _container;

        explicit stack (const container_type& ctnr = container_type())
        {
            _container = ctnr;
        }
        bool empty() const{
            return _container.empty();
        }
        size_type size() const {
            return _container.size();
        }
        value_type& top()
        {
            return _container.back();
        }

        const value_type& top() const
        {
            return _container.back();
        }
        void push (const value_type& val)
        {
            _container.push_back(val);
        }

        void pop(){
            _container.pop_back();
        }
        void swap (stack& x){
            _container.swap(x._container);
        }
    };
    template <class T, class Container>
    void swap (stack<T,Container>& x, stack<T,Container>& y){
        x.swap(y);
    }
    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._container ==  rhs._container;
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._container  != rhs._container;
    }
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._container  < rhs._container;
    }
    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._container  <= rhs._container;
    }
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._container > rhs._container;
    }
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return lhs._container  >= rhs._container;
    }


}