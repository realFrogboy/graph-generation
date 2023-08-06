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
    void print() const { Dump(Nodes, "ReducibleGraph.dot"); }

    const std::vector<NodePtr> &getNodes() const { return Nodes; }
};

} // namespace graph
