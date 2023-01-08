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
            bool isPresent(){
                return data != null;
            }
            /*
             *
             *  @README: do not use this function if you have nullable values
             *    if  you pass in a null value  expect a segmentation fault
             *     use ofNullable
             */
            static  Optional<T> of(T item)
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
            Optional<T> orElseThrow(std::exception &e)
            {
                if (isPresent())
                    return *this;
                throw  e;
            }
    };
}