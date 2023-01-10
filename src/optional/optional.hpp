//
// Created by Abdelouahad Ait hamd on 1/8/23.
//
#pragma once
#include "../utility/Forward.hpp"
#include <exception>
namespace  ft {
    template<class T>
    class Optional{
        private:
          T data;
          Optional(): data(null){}
          Optional(T   data): data(data){}

        public :
        Optional(const Optional<T> &other) {this->data = other.data;}
            bool isPresent() const{
                return data != null;
            }
            /*
             *
             *  @README: do not use this function if you have nullable values
             *    if  you pass in a null value  expect a segmentation fault
             *     use ofNullable
             */
            static  Optional<T> of(T const &item)
            {
                return Optional<T>(item);
            }

            static Optional<T> empty()
            {
                  return Optional<T>();
            }
            /*
             *   @Param : item
             */
            static Optional<T> ofNullable(T item)
            {
               return item == null ? empty(): of (item);
            }
            T get() const
            {
              return data;
            }
             T get()
             {
                 return data;
             }
            template< class V>
            Optional<V> ifPresentReturn(V other)
            {
                return isPresent() ? Optional<V>::ofNullable(other) : Optional<V>::empty();
            }
            Optional<T> orElse(T other)
            {
              return isPresent() ? *this : Optional<T>::ofNullable(other);
            }
             T &orElseThrow(std::exception const &e)
            {
                if (isPresent())
                    return data;
                throw  e;
            }
    };
}