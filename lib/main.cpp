#include "ReducibleGraphTy.hpp"
#include "DominanceTreeTy.hpp"

#include <iostream>
#include <exception>

int main() {
    try {
        size_t GraphSize;
        std::cin >> GraphSize;

        std::cout << "Redusible graph generation..." << std::endl;
        graph::ReducibleGraphTy ReducibleGraph{GraphSize};
        ReducibleGraph.print();
        std::cout << "Redusible graph generation: done" << std::endl;

        std::cout << "Dominance tree generation..." << std::endl;
        graph::DominanceTreeTy DominanceTree{ReducibleGraph};
        DominanceTree.print();
        std::cout << "Dominance tree generation: done" << std::endl;

        #ifdef DUMP
        std::cout << "Graphs printing..." << std::endl; 
            system("dot -Tpng Dump.dot -o Graph.png");
            system("dot -Tpng DomTreeDump.dot -o DomTree.png");
        std::cout << "Graphs printing: done" << std::endl;
        #endif
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
