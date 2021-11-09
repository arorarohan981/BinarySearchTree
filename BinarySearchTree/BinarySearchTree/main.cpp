//
//  main.cpp
//  BinarySearchTree
//
//  Created by Rohan Arora on 09/11/21.
//

#include <iostream>
#include "BinarySearchTree.hpp"

int main(int argc, const char * argv[]) {
    
    mylib::BinarySearchTree<int> intTree;
    intTree.add(50);
    intTree.add(30);
    intTree.add(70);
    intTree.add(20);
    intTree.add(40);
    intTree.add(60);
    intTree.add(80);
//    intTree.add(12);
    intTree.inOrderPrintTree();
    std::cout<<std::boolalpha<<intTree.remove(20)<<std::endl;
    intTree.inOrderPrintTree();
    return 0;
    
}
