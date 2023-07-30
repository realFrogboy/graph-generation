#include "ReducibleGraphTy.hpp"

#include <random>

namespace graph {

void DFSTy::run() { 
    std::vector<NodeTy*> Stack{Graph.getRoot()};
    while (!Stack.empty()) {
        NodeTy *Node = Stack.back();
        Stack.pop_back();

        Positions.try_emplace(Node->getID(), Positions.size());

        for (auto Child : Node->getChildren())
            if (!Positions.count(Child->getID()))
                Stack.push_back(Child);
    }
}

std::set<NodeTy*> DominanceTreeTy::Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs) {
    if (Lhs.empty())
        return Rhs;

    if (Rhs.empty()) 
        return Lhs;

    std::set<NodeTy*> Intersection;
    std::set_intersection(Lhs.begin(), Lhs.end(), Rhs.begin(), Rhs.end(), std::inserter(Intersection, Intersection.begin()));

    return Intersection;
}

DominanceTreeTy::DominanceTreeTy(const ReducibleGraphTy &Graph) : DominatorSets(Graph.getNNodes()) {
    Nodes.reserve(Graph.getNNodes());
    for (auto &Node : Graph.getNodes())
        Nodes.emplace_back(std::make_unique<NodeTy>(*(Node.get())));
    generate(Graph);
}

void DominanceTreeTy::initDominatorSets(const ReducibleGraphTy &Graph) {
    // Dom(entry) = entry
    DominatorSets.front().insert(Nodes.front().get());

    bool Changed = 1;
    while (Changed) {
        Changed = 0;
        for (auto &Node : Nodes) {
            std::set<NodeTy*> Intersec;
            for (auto Parent : Node->getParents())
                if (Parent != Node.get())
                    Intersec = Intersection(Intersec, DominatorSets[Parent->getID()]);
            
            if (Intersec.empty())
                continue;

            Intersec.insert(Node.get());

            if (DominatorSets[Node->getID()] == Intersec)
                continue;

            DominatorSets[Node->getID()] = std::move(Intersec);
            Changed = 1;
        }
    }
}

NodeTy *DominanceTreeTy::getIDominator(NodeTy *Node, const ReducibleGraphTy &Graph) const {
    NodeTy *IDom = Nodes.front().get();
    unsigned DFSPos = 0;

    for (auto Dominator : DominatorSets[Node->getID()]) {
        if (Dominator == Node)
            continue;
        
        unsigned Pos = Graph.getDFSPosition(Dominator->getID());
        if (Pos > DFSPos) {
            DFSPos = Pos;
            IDom = Dominator;
        }
    }
    return IDom;
}

void DominanceTreeTy::generate(const ReducibleGraphTy &Graph) {
    initDominatorSets(Graph);

    for (auto &Node : Nodes) {
        Node->clearChildren();
        Node->clearParents();
        Node->addNewParent(getIDominator(Node.get(), Graph));
    }
}

void DominanceTreeTy::print() const {
    std::ofstream File("DomTreeDump.dot");
    File << "digraph tree {\n";

    for (auto &Node : Nodes) {
        File << "\tnode" << Node->getID() << " [shape = \"record\", label = \"" << Node->getID() << "\"];\n";
    }

    for (auto &Node : Nodes) {
        for (auto Parent : Node->getParents())
            File << "node" << Parent->getID() << " -> node" << Node->getID() << ";\n";
    }

    File << "}";
    return;
}

ReducibleGraphTy::ReducibleGraphTy(const size_t Size) : DFS{std::make_unique<DFSTy>(*this)} {
    Nodes.emplace_back(std::make_unique<NodeTy>(0));
    generate(Size); 
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

void ReducibleGraphTy::print() const {
    std::ofstream File("Dump.dot");
    File << "digraph tree {\n";

    for (auto &Node : Nodes) {
        File << "\tnode" << Node->getID() << " [shape = \"record\", label = \"" << Node->getID() << " (" << 
        DFS->getPosition(Node->getID()) << ")\"];\n";
    }

    for (auto &Node : Nodes) {
        for (auto Child : Node->getChildren())
            File << "node" << Node->getID() << " -> node" << Child->getID() << ";\n";
    }

    File << "}";
    return;
} 

} // namespace graph
