#pragma once

#include "NodeTy.hpp"
#include "GraphDumpTy.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace graph{

class ReducibleGraphTy final {
    using NodePtr = std::unique_ptr<NodeTy>;

    std::vector<NodePtr> Nodes;
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;

    NodeTy *getRandomNode() const;
    NodeTy *addNewNode();
    
    void reverseT1() const;
    void reverseT2();

    void generate(const size_t Size);

    public:
    ReducibleGraphTy(const size_t Size);
    void print() const { Dump(Nodes, "ReducibleGraph.dot"); }

    size_t getNNodes() const { return Nodes.size(); }
    const NodeTy *getNode(const unsigned NodeID) const { return Nodes[NodeID].get(); }
    const std::vector<NodePtr> &getNodes() const { return Nodes; }
};

} // namespace graph
