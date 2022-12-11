cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(${PROJECT_NAME} main.cpp
        src/IteratorTraits.h
        src/vector.hpp
        src/reverse_iterator.h
        src/RandomAccessIterator.h
        src/Iterator.hpp
        src/Forward.hpp src/exceptions/OutOfBoundExecption.cpp src/exceptions/OutOfBoundExecption.h src/Enable_if.hpp src/IsIntegral.hpp)
