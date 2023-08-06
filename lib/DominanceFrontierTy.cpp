#include "Utils.hpp"
#include "DominanceFrontierTy.hpp"

#include <fstream>
#include <numeric>

namespace graph {

DominanceFrontierTy::DominanceFrontierTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree) : GraphTy{Graph.getNNodes()}, Dump{GraphDumpTy{}} {
    std::iota(Nodes.begin(), Nodes.end(), utils::MakeUnique<NodeTy>(0));

    for (auto &Node : Graph.getNodes()) {
        for (auto Dominator : DominanceTree.getDominators(Node->getID())) 
            for (auto Child : Node->getChildren()) {
                std::set<NodeTy*> ChildDominators = DominanceTree.getDominators(Child->getID());
                auto DominatorIt = std::find_if(ChildDominators.begin(), ChildDominators.end(), [Dominator](NodeTy *ChildDominator){ return Dominator->getID() == ChildDominator->getID(); });
                if (DominatorIt == ChildDominators.end()) {
                    Nodes[Dominator->getID()]->addNewChild(Nodes[Child->getID()].get());
                    Nodes[Child->getID()]->addNewParent(Nodes[Dominator->getID()].get());
                }
            }
    }
    
    Nodes.erase(std::remove_if(Nodes.begin(), Nodes.end(), [](auto &Node){ return !(Node->hasChildren() || Node->hasParents()); }), Nodes.end());
}

} // namespace graph
