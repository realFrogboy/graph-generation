#pragma once

#include "NodeTy.hpp"

#include <vector>
#include <memory>

namespace graph {

class GraphTy {
    protected:
    using NodePtr = std::unique_ptr<NodeTy>;
    std::vector<NodePtr> Nodes;

    public:
    GraphTy(const size_t Size = 0) : Nodes(Size) {}

    NodeTy *getRoot() const { return Nodes.front().get(); }
    size_t getNNodes() const { return Nodes.size(); }
    NodeTy *getNode(const unsigned NodeID) const { return Nodes.at(NodeID).get(); }

    virtual ~GraphTy() {}
};

} // namespace graph