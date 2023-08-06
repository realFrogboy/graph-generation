#pragma once

#include <memory>
#include <vector>

namespace graph {

class NodeTy final {
    std::vector<NodeTy*> Parents;
    std::vector<NodeTy*> Children;
    const unsigned NodeID;

    public:
    NodeTy(const unsigned NodeID) : NodeID{NodeID} {}
    void removeDublicates();

    void addNewChild(NodeTy *Node) { Children.push_back(Node); }
    void addNewParent(NodeTy *Node) { Parents.push_back(Node); }

    void T1();

    void reverseT1();
    void reverseT2(NodeTy *Node);

    const std::vector<NodeTy*> &getChildren() const { return Children; }
    const std::vector<NodeTy*> &getParents() const { return Parents; }
    unsigned getID() const { return NodeID; }
};

} // namespace graph
