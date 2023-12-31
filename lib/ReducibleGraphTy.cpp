#include "Utils.hpp"
#include "ReducibleGraphTy.hpp"

#include <random>
#include <fstream>

namespace graph {

ReducibleGraphTy::ReducibleGraphTy(const size_t Size) : GraphTy{}, Dump{GraphDumpTy{}} {
    Nodes.emplace_back(std::make_unique<NodeTy>(0));
    generate(Size); 
}

ReducibleGraphTy::ReducibleGraphTy(const size_t Size, const std::vector<EdgeTy> &Edges) : GraphTy{Size}, Dump{GraphDumpTy{}} {
    std::iota(Nodes.begin(), Nodes.end(), utils::MakeUnique<NodeTy>(0));

    for (auto Edge : Edges) {
        Nodes[Edge.first]->addNewChild(Nodes[Edge.second].get());
        Nodes[Edge.second]->addNewParent(Nodes[Edge.first].get());
    }

    Nodes.erase(std::remove_if(Nodes.begin(), Nodes.end(), [](auto &Node){ return !(Node->hasChildren() || Node->hasParents()); }), Nodes.end());
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

void ReducibleGraphTy::generate(const size_t Size) {
    while (Nodes.size() < Size) {
        reverseT2();
        reverseT2();
        reverseT1();
        reverseT2();
        reverseT2();
        reverseT2();
    }

    for (auto &Node : Nodes) {
        Node->removeDublicates();
        Node->T1();
    }
}

void ReducibleGraphTy::reverseT1() const {
    NodeTy *Node = getRandomNode();
    while (Node == Nodes.front().get())
        Node = getRandomNode();
    Node->reverseT1();
}

void ReducibleGraphTy::reverseT2() {
    NodeTy *GraphNode = getRandomNode();
    NodeTy *NewNode = addNewNode();
    
    GraphNode->reverseT2(NewNode);
}

} // namespace graph
