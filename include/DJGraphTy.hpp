#pragma once

#include "NodeTy.hpp"
#include "ReducibleGraphTy.hpp"
#include "DominanceTreeTy.hpp"

#include <memory>
#include <vector>

namespace graph {

class DJGraphTy final {
    using NodePtr = std::unique_ptr<NodeTy>;

    std::vector<NodePtr> Nodes;

    public:
    DJGraphTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree);
    void print() const;
};

} // namespace graph
