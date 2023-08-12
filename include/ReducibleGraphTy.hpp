#pragma once

#include "NodeTy.hpp"
#include "GraphTy.hpp"
#include "GraphDumpTy.hpp"

#include <memory>
#include <vector>
#include <functional>

namespace graph{

class ReducibleGraphTy final : public GraphTy {
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;

    NodeTy *getRandomNode() const;
    NodeTy *addNewNode();
    
    void reverseT1() const;
    void reverseT2();

    void generate(const size_t Size);

    public:
    ReducibleGraphTy(const size_t Size);
    ReducibleGraphTy(const size_t Size, const std::vector<EdgeTy> &Edges);
    void print() const { Dump(Nodes, "ReducibleGraph.dot"); }
};

} // namespace graph
