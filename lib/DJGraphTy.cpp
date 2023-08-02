#include "DJGraphTy.hpp"

#include <fstream>

namespace graph {

DJGraphTy::DJGraphTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree) : Dump{GraphDumpTy{}} {
    for (unsigned i = 0; i < Graph.getNNodes(); ++i)
        Nodes.emplace_back(std::make_unique<NodeTy>(i));

    for (auto &Node : Nodes) {
        const NodeTy *ReducibleGraphNode = Graph.getNode(Node->getID());
        const NodeTy *DominanceTreeNode = DominanceTree.getNode(Node->getID());

        for (auto Child : DominanceTreeNode->getChildren()) 
            Node->addNewChild(Nodes[Child->getID()].get());

        for (auto Child : ReducibleGraphNode->getChildren()) {
            NodeTy *ChildIDom = DominanceTree.getNode(Child->getID())->getParents().front();
            if (ChildIDom->getID() != Node->getID())
                Node->addNewChild(Nodes[Child->getID()].get());
        }
    }
}

} // namespace graph