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

    NodeTy *getRoot() const { return Nodes.front().get(); }
    size_t getNNodes() const { return Nodes.size(); }
    const std::vector<NodePtr> &getNodes() const { return Nodes; }
};

} // namespace graph
