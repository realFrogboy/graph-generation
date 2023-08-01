#include "DominanceTreeTy.hpp"

#include <fstream>

namespace graph {

void DFSTy::run(NodeTy *Root) { 
    std::vector<NodeTy*> Stack{Root};
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

DominanceTreeTy::DominanceTreeTy(const ReducibleGraphTy &Graph) : DominatorSets(Graph.getNNodes()), DFS{std::make_unique<DFSTy>()} {
    Nodes.reserve(Graph.getNNodes());
    for (auto &Node : Graph.getNodes())
        Nodes.emplace_back(std::make_unique<NodeTy>(*(Node.get())));
    runDFS();
    generate();
}

void DominanceTreeTy::initDominatorSets() {
    // Dom(entry) = entry
    DominatorSets.front().insert(Nodes.front().get());

    bool Changed = 1;
    while (Changed) {
        Changed = 0;
        for (auto &Node : Nodes) {
            std::set<NodeTy*> Intersec;
            for (auto Parent : Node->getParents())
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

NodeTy *DominanceTreeTy::getIDominator(NodeTy *Node) const {
    NodeTy *IDom = Nodes.front().get();
    unsigned DFSPos = 0;

    for (auto Dominator : DominatorSets[Node->getID()]) {
        if (Dominator == Node)
            continue;
        
        unsigned Pos = getDFSPosition(Dominator->getID());
        if (Pos > DFSPos) {
            DFSPos = Pos;
            IDom = Dominator;
        }
    }
    return IDom;
}

void DominanceTreeTy::generate() {
    initDominatorSets();

    for (auto &Node : Nodes) {
        Node->clearChildren();
        Node->clearParents();
    }

    for (auto &Node : Nodes) {
        NodeTy *Parent = getIDominator(Node.get());
        Node->addNewParent(Parent);
        Parent->addNewChild(Node.get());
    }

    Nodes.front()->T1();
}

void DominanceTreeTy::print() const {
    std::ofstream File("DomTree.dot");
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

} // namespace graph
