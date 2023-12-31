#pragma once

#include <memory>
#include <vector>
#include <algorithm>

namespace graph {

using EdgeTy = std::pair<size_t, size_t>;

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

    bool hasChildren() const { return !Children.empty(); }
    bool hasParents() const { return !Parents.empty(); }

    bool hasChild(const size_t NodeID) { 
        auto It = std::find_if(Children.begin(), Children.end(), [NodeID](auto Child){ return Child->getID() == NodeID; });
        return It != Children.end();
    }

    const std::vector<NodeTy*> &getChildren() const { return Children; }
    const std::vector<NodeTy*> &getParents() const { return Parents; }
    unsigned getID() const { return NodeID; }
};

} // namespace graph
