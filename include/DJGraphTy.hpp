#pragma once

#include "NodeTy.hpp"
#include "GraphDumpTy.hpp"
#include "ReducibleGraphTy.hpp"
#include "DominanceTreeTy.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace graph {

class DJGraphTy final {
    using NodePtr = std::unique_ptr<NodeTy>;

    std::vector<NodePtr> Nodes;
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;

    public:
    DJGraphTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree);
    void print() const { Dump(Nodes, "DJGraph.dot"); }
};

} // namespace graph
