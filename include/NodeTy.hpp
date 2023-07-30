#pragma once

#include <memory>
#include <vector>
#include <fstream>

namespace graph {

class NodeTy final {
    std::vector<NodeTy*> Children;
    unsigned NodeID;

    public:
    NodeTy(const unsigned NodeID) : NodeID{NodeID} {}

    void addNewChild(NodeTy *Node) { Children.push_back(Node); }
    void reverseT1() { Children.push_back(this); }
    void reverseT2(NodeTy *Node);

    const std::vector<NodeTy*> &getChildren() const { return Children; }
    unsigned getID() const { return NodeID; }
};

} // namespace graph
