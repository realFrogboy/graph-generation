#include "Utils.hpp"
#include "DominanceTreeTy.hpp"

#include <fstream>
#include <numeric>

namespace graph {

void DominanceTreeTy::DominatorSearcher::DFSTy::run(const NodeTy *Root) { 
    std::vector<const NodeTy*> Stack{Root};
    while (!Stack.empty()) {
        const NodeTy *Node = Stack.back();
        Stack.pop_back();

        Positions.try_emplace(Node->getID(), Positions.size());

        for (auto Child : Node->getChildren())
            if (!Positions.count(Child->getID()))
                Stack.push_back(Child);
    }
}

std::set<NodeTy*> DominanceTreeTy::DominatorSearcher::Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs) {
    if (Lhs.empty())
        return Rhs;

    if (Rhs.empty()) 
        return Lhs;

    std::set<NodeTy*> Intersection;
    std::set_intersection(Lhs.begin(), Lhs.end(), Rhs.begin(), Rhs.end(), std::inserter(Intersection, Intersection.begin()));

    return Intersection;
}

void DominanceTreeTy::DominatorSearcher::search(const ReducibleGraphTy &Graph) {
    DFS->run(Graph.getRoot());

    // Dom(entry) = entry
    DominatorSets.front().insert(Graph.getRoot());

    bool Changed = 1;
    while (Changed) {
        Changed = 0;
        for (auto &Node : Graph.getNodes()) {
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

DominanceTreeTy::DominatorSearcher::DominatorSearcher(const ReducibleGraphTy &Graph) : DFS{std::make_unique<DFSTy>()}, DominatorSets(Graph.getNNodes()) {
    search(Graph);
}

size_t DominanceTreeTy::DominatorSearcher::getIDominator(const size_t NodeID) const {    
    size_t IDom = 0;
    size_t DFSPos = 0;

    for (auto Dominator : DominatorSets[NodeID]) {
        size_t DomID = Dominator->getID();
        if (DomID == NodeID)
            continue;
        
        unsigned Pos = DFS->getPosition(DomID);
        if (Pos > DFSPos) {
            DFSPos = Pos;
            IDom = DomID;
        }
    }
    return IDom;
}

DominanceTreeTy::DominanceTreeTy(const ReducibleGraphTy &Graph) : GraphTy{Graph.getNNodes()}, DS{std::make_unique<DominatorSearcher>(Graph)}, Dump{GraphDumpTy{}} {
    std::iota(Nodes.begin(), Nodes.end(), utils::MakeUnique<NodeTy>(0));
    generate();
}

void DominanceTreeTy::generate() {
    for (auto &Node : Nodes) {
        size_t ParentID = DS->getIDominator(Node->getID());
        NodeTy *Parent = getNode(ParentID);

        Node->addNewParent(Parent);
        Parent->addNewChild(Node.get());
    }
    Nodes.front()->T1();
}

} // namespace graph
