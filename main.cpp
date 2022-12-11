//
// Created by Abdelouahad Ait hamd on 12/8/22.
//

#include "./src/vector.hpp"
#include <iostream>

int main() {
     ft::vector<int> v;
     v.assign(10, 5);
     for ( int i = 0; i < v.size(); i++) {
         std::cout << v[i] << std::endl;
     }

    return 0;
}