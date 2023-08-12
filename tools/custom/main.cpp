#include "ReducibleGraphTy.hpp"
#include "DominanceTreeTy.hpp"
#include "DJGraphTy.hpp"
#include "DominanceFrontierTy.hpp"

#include <sstream>
#include <utility>
#include <iostream>
#include <exception>

namespace {

    std::pair<size_t, std::vector<graph::EdgeTy>> getEdges() {
        std::string Line;
        std::getline(std::cin, Line);
        std::stringstream SS(Line);
        
        size_t NNodes;
        if (!(SS >> NNodes))
            throw std::runtime_error("incorrect input");
        
        std::vector<graph::EdgeTy> Edges;
    
        while (std::getline(std::cin, Line)) {
            std::stringstream SS(Line);
            graph::EdgeTy Edge;
            std::string Arrow;
            if (SS.eof())
                break;
            else if (SS >> Edge.first >> Arrow >> Edge.second)
                Edges.emplace_back(Edge);
            else 
                throw std::runtime_error("incorrect input");
        }

        return {NNodes, Edges};
    }

} // namespace

int main() {
    try {
        auto [NNodes, Edges] = getEdges();

        std::cout << "Redusible graph generation..." << std::endl;
        graph::ReducibleGraphTy ReducibleGraph{NNodes, Edges};
        std::cout << "Redusible graph generation: done" << std::endl;

        std::cout << "Dominance tree generation..." << std::endl;
        graph::DominanceTreeTy DominanceTree{ReducibleGraph};
        std::cout << "Dominance tree generation: done" << std::endl;

        std::cout << "DJ-graph generation..." << std::endl;
        graph::DJGraphTy DJGraph{ReducibleGraph, DominanceTree};
        std::cout << "DJ-graph generation: done" << std::endl;

        std::cout << "DF generation..." << std::endl;
        graph::DominanceFrontierTy DominanceFrontier{DominanceTree, DJGraph};
        std::cout << "DF generation: done" << std::endl;

        #ifdef DUMP
        std::cout << "Graphs printing..." << std::endl; 
        ReducibleGraph.print();
        DominanceTree.print();
        DJGraph.print();
        DominanceFrontier.print();
        system("dot -Tpng ReducibleGraph.dot -o Graph.png");
        system("dot -Tpng DomTree.dot -o DomTree.png");
        system("dot -Tpng DJGraph.dot -o DJGraph.png");
        system("dot -Tpng DominanceFrontier.dot -o DominanceFrontier.png");
        std::cout << "Graphs printing: done" << std::endl;
        #endif
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }

}