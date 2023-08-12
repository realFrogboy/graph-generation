#include "Utils.hpp"
#include "DominanceTreeTy.hpp"

#include <fstream>
#include <numeric>

namespace graph {

std::set<NodeTy*> DominanceTreeTy::DominatorSearcher::Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs) {
    if (Lhs.empty())
        return Rhs;

    if (Rhs.empty()) 
        return Lhs;

    std::set<NodeTy*> Intersection;
    std::set_intersection(Lhs.begin(), Lhs.end(), Rhs.begin(), Rhs.end(), std::inserter(Intersection, Intersection.begin()));

    return Intersection;
}

void DominanceTreeTy::DominatorSearcher::search() {
    RPO->run();

    // Dom(entry) = entry
    DominatorSets.front().insert(Graph.getRoot());

    bool Changed = 1;
    while (Changed) {
        Changed = 0;
        for (auto &Node : RPO->getOrder()) {
            std::set<NodeTy*> Intersec;
            for (auto Parent : Node->getParents())
                Intersec = Intersection(Intersec, DominatorSets[Parent->getID()]);
            
            if (Intersec.empty())
                continue;

            Intersec.insert(Node);

            if (DominatorSets[Node->getID()] == Intersec)
                continue;

            DominatorSets[Node->getID()] = std::move(Intersec);
            Changed = 1;
        }
    }
}

DominanceTreeTy::DominatorSearcher::DominatorSearcher(const GraphTy &Graph) : Graph{Graph}, RPO{std::make_unique<utils::RPOTy>(Graph)}, DominatorSets(Graph.getNNodes()) {
    search();
}

size_t DominanceTreeTy::DominatorSearcher::getIDominator(const size_t NodeID) const {    
    size_t IDom = 0;
    size_t RPOPos = 0;

    for (auto Dominator : DominatorSets[NodeID]) {
        size_t DomID = Dominator->getID();
        if (DomID == NodeID)
            continue;
        
        unsigned Pos = RPO->getPosition(DomID);
        if (Pos > RPOPos) {
            RPOPos = Pos;
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
