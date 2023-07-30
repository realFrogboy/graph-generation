#include "ReducibleGraphTy.hpp"

#include <random>

namespace graph {

ReducibleGraphTy::ReducibleGraphTy(const size_t Size) {
    Nodes.emplace_back(std::make_unique<NodeTy>(0));
    Generate(Size); 
}

NodeTy *ReducibleGraphTy::getRandomNode() const {
    std::random_device Rd;
    std::seed_seq seed2{Rd(), Rd(), Rd(), Rd(), Rd(), Rd(), Rd(), Rd()};
    std::mt19937 Mt{seed2};
    std::uniform_int_distribution<unsigned> Dist(0, Nodes.size() - 1);
    return Nodes[Dist(Mt)].get();
}

NodeTy *ReducibleGraphTy::addNewNode() {
    Nodes.emplace_back(std::make_unique<NodeTy>(Nodes.size()));
    return Nodes.back().get();
}

void ReducibleGraphTy::Generate(const size_t Size) {
    while (Nodes.size() < Size) {
        reverseT2();
        reverseT2();
        reverseT1();
        reverseT2();
        reverseT2();
        reverseT2();
    }
}

void ReducibleGraphTy::reverseT1() const {
    getRandomNode()->reverseT1();
}

void ReducibleGraphTy::reverseT2() {
    NodeTy *GraphNode = getRandomNode();
    NodeTy *NewNode = addNewNode();
    
    GraphNode->reverseT2(NewNode);
}

void ReducibleGraphTy::print() const {
    std::ofstream File("Dump.dot");
    File << "digraph tree {\n";

    for (auto &Node : Nodes) {
        File << "\tnode" << Node->getID() << " [shape = \"record\", label = \"" << Node->getID() << "\"];\n";
    }

    for (auto &Node : Nodes) {
        for (auto Child : Node->getChildren())
            File << "node" << Node->getID() << " -> node" << Child->getID() << ";\n";
    }

    File << "}";
    return;
} 

} // namespace graph
