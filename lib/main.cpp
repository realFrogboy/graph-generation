#include "ReducibleGraphTy.hpp"

#include <iostream>
#include <exception>

int main() {
    try {
        size_t GraphSize;
        std::cin >> GraphSize;
        graph::ReducibleGraphTy ReducibleGraph{GraphSize};
        ReducibleGraph.print();
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
