#include "ReducibleGraphTy.hpp"
#include "DominanceTreeTy.hpp"
#include "DJGraphTy.hpp"

#include <iostream>
#include <exception>

int main() {
    try {
        size_t GraphSize;
        std::cin >> GraphSize;

        std::cout << "Redusible graph generation..." << std::endl;
        graph::ReducibleGraphTy ReducibleGraph{GraphSize};
        std::cout << "Redusible graph generation: done" << std::endl;

        std::cout << "Dominance tree generation..." << std::endl;
        graph::DominanceTreeTy DominanceTree{ReducibleGraph};
        std::cout << "Dominance tree generation: done" << std::endl;

        std::cout << "DJ-graph generation..." << std::endl;
        graph::DJGraphTy DJGraph{ReducibleGraph, DominanceTree};
        std::cout << "DJ-graph generation: done" << std::endl;

        #ifdef DUMP
        std::cout << "Graphs printing..." << std::endl; 
        ReducibleGraph.print();
        DominanceTree.print();
        DJGraph.print();
        system("dot -Tpng ReducibleGraph.dot -o Graph.png");
        system("dot -Tpng DomTree.dot -o DomTree.png");
        system("dot -Tpng DJGraph.dot -o DJGraph.png");
        std::cout << "Graphs printing: done" << std::endl;
        #endif
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
