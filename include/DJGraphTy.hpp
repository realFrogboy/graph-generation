#pragma once

#include "NodeTy.hpp"
#include "GraphTy.hpp"
#include "GraphDumpTy.hpp"
#include "ReducibleGraphTy.hpp"
#include "DominanceTreeTy.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace graph {

class DJGraphTy final : public GraphTy {
    std::vector<EdgeTy> JoinEdges;
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;

    public:
    DJGraphTy(const ReducibleGraphTy &Graph, const DominanceTreeTy &DominanceTree);
    void print() const { Dump(Nodes, "DJGraph.dot"); }

    const std::vector<EdgeTy> &getJoinEdges() const { return JoinEdges; }
};

} // namespace graph
