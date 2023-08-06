#pragma once

#include "GraphTy.hpp"
#include "GraphDumpTy.hpp"
#include "DominanceTreeTy.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace graph {

class DominanceFrontierTy final : public GraphTy {
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;

    public:
    DominanceFrontierTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree);
    void print() const { Dump(Nodes, "DominanceFrontier.dot"); }
}; 

} //namespace graph