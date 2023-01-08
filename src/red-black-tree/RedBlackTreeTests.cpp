//
// Created by Abdelouahad Ait hamd on 1/1/23.
//
#include "RedBlackTree.hpp"
void printHeader()
{
    std::cout << "e to exit ,  (i to insert,  d to delete, followed by a  number)" << std::endl;
}
int main()
{
//     int size = 9;
//    int keys[] = {
//           1,
//           2,
//           3,
//
//    };
    ft::RedBlackTree<int, ft::_less<int> > rbl;
    for (int i = 0 ; i< 2; i++)
    {
        for (int j = 0; (i == 1 && j > -10) || (i == 0 && j < 10);(i==0 ? j++ : j--)) {
            rbl.insert(j);
            usleep(500);
        }
    }

    printHeader();
    std::string v;
    std::string input;
    std::cin >> input;

    while(1) {

        if (input == "e")
            break;
        if (input == "i")
        {
            std::cin >> v;

            rbl.insert(std::atoi(v.c_str()));
        }
        if (input == "d")
        {
            std::cin >> v;
            rbl.erase(std::atoi(v.c_str()));
        }
        printHeader();
        std::cin >> input;
    }
//    std::cout << "insertion" << std::endl;
//    for (int i =0; i< size ;i ++ )
//    {
//        rbl.insert(keys[i]);
//        std::cout << "INSERT " << keys[i];
//    }
//    std::cout << "Debug " << __LINE__ << " " << __PRETTY_FUNCTION__  << " " << __FILE__ << std::endl;
//    ft::Node<int *> *va = null;
//    int founds = 0;
//    for (int i =0; i< size ;i ++ ) {
//       va  = rbl.search(keys[i]);
//        if (va != null && va->getType() != LEAF)
//
//            std::cout << std::endl << "found    " << ++founds << *va->getValue() << std::endl;
//        else
//            std::cout << std::endl << "not found" << va << std::endl;
//    }
//
//    std::cout << "found " << founds << "out of " << size<< std::endl;
   // std::cout << rbl.getHeight() << std::endl;
}
