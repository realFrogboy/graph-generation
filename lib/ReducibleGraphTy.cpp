#include "ReducibleGraphTy.hpp"

#include <random>

namespace {

template<class T>
struct movable_il {
  mutable T t;
  operator T() const&& { return std::move(t); }
  movable_il( T&& in ): t(std::move(in)) {}
};

template<class T, class A=std::allocator<T>>
std::vector<T,A> vector_from_il( std::initializer_list< movable_il<T> > il ) {
  std::vector<T,A> r( std::make_move_iterator(il.begin()), std::make_move_iterator(il.end()) );
  return r;
}

}

namespace graph {

ReducibleGraphTy::ReducibleGraphTy(const size_t Size) {
    Nodes.emplace_back(std::make_unique<NodeTy>(0));
    Root = Nodes.front().get();
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
    NodeTy *Node = addNewNode();

    NodeTy *GraphNode = getRandomNode();
    while (Node == GraphNode) 
        GraphNode = getRandomNode();
    
    GraphNode->reverseT2(Node);
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
