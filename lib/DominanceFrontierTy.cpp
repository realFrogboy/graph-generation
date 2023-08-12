#include "Utils.hpp"
#include "DominanceFrontierTy.hpp"

#include <fstream>
#include <numeric>

namespace graph {

DominanceFrontierTy::DominanceFrontierTy(const DominanceTreeTy &DominanceTree, const DJGraphTy &DJGraph) : GraphTy{DominanceTree.getNNodes()}, Dump{GraphDumpTy{}} {
    std::iota(Nodes.begin(), Nodes.end(), utils::MakeUnique<NodeTy>(0));

    for (auto Edge : DJGraph.getJoinEdges()) {
        NodeTy *Node = DominanceTree.getNode(Edge.first);
        std::set<size_t> DFNodeDominators = DominanceTree.getDominatorsIDs(Edge.second);

        while (!DFNodeDominators.count(Node->getID())) {
            if (!Nodes[Node->getID()]->hasChild(Edge.second)) {
                Nodes[Node->getID()]->addNewChild(Nodes[Edge.second].get());
                Nodes[Edge.second]->addNewParent(Nodes[Node->getID()].get());
            }
            // climb the dominator tree, Node has only 1 parent
            Node = Node->getParents().front();
        }
    }
    
    Nodes.erase(std::remove_if(Nodes.begin(), Nodes.end(), [](auto &Node){ return !(Node->hasChildren() || Node->hasParents()); }), Nodes.end());
}

} // namespace graph
