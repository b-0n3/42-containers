//
// Created by Abdelouahad Ait hamd on 12/9/22.
//
#pragma once
namespace ft {
    template<bool B, class T = void>
    struct enable_if {
    };
    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };
}