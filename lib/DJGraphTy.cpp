#include "Utils.hpp"
#include "DJGraphTy.hpp"

#include <fstream>
#include <numeric>
#include <iostream>

namespace graph {

DJGraphTy::DJGraphTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree) : GraphTy{Graph.getNNodes()}, Dump{GraphDumpTy{}} {
    std::iota(Nodes.begin(), Nodes.end(), utils::MakeUnique<NodeTy>(0));

    for (auto &Node : Nodes) {
        const NodeTy *ReducibleGraphNode = Graph.getNode(Node->getID());
        const NodeTy *DominanceTreeNode = DominanceTree.getNode(Node->getID());

        for (auto Child : DominanceTreeNode->getChildren()) 
            Node->addNewChild(Nodes[Child->getID()].get());

        for (auto Child : ReducibleGraphNode->getChildren()) {
            NodeTy *ChildIDom = DominanceTree.getNode(Child->getID())->getParents().front();
            if (ChildIDom->getID() != Node->getID()) {
                Node->addNewChild(Nodes[Child->getID()].get());
                JoinEdges.push_back({Node->getID(), Child->getID()});
            }
        }
    }
}

} // namespace graph