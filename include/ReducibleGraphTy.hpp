#pragma once

#include "NodeTy.hpp"

#include <memory>
#include <vector>

namespace graph{

class ReducibleGraphTy final {
    using NodePtr = std::unique_ptr<NodeTy>;

    std::vector<NodePtr> Nodes;

    NodeTy *getRandomNode() const;
    NodeTy *addNewNode();
    
    void reverseT1() const;
    void reverseT2();

    void generate(const size_t Size);

    public:
    ReducibleGraphTy(const size_t Size);
    void print() const;

    size_t getNNodes() const { return Nodes.size(); }
    const NodeTy *getNode(const unsigned NodeID) const { return Nodes[NodeID].get(); }
    const std::vector<NodePtr> &getNodes() const { return Nodes; }
};

} // namespace graph
