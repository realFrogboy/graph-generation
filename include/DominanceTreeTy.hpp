#pragma once

#include "NodeTy.hpp"
#include "ReducibleGraphTy.hpp"

#include <set>
#include <memory>
#include <vector>
#include <unordered_map>

namespace graph {

class DFSTy final {
    std::unordered_map<unsigned, unsigned> Positions;
    public:
    void run(NodeTy *Root);
    unsigned getPosition(const unsigned NodeID) const { return Positions.at(NodeID); }
};

class DominanceTreeTy final {
    using NodePtr = std::unique_ptr<NodeTy>;
    
    std::vector<NodePtr> Nodes;
    std::vector<std::set<NodeTy*>> DominatorSets;
    std::unique_ptr<DFSTy> DFS;

    static std::set<NodeTy*> Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs);

    void runDFS() const { DFS->run(Nodes.front().get()); }
    unsigned getDFSPosition(const unsigned NodeID) const { return DFS->getPosition(NodeID); }
    
    NodeTy *getIDominator(NodeTy *Node) const;

    void initDominatorSets();
    void generate();

    public:
    DominanceTreeTy(const ReducibleGraphTy &Graph);
    void print() const;

    const NodeTy *getNode(const unsigned NodeID) const { return Nodes[NodeID].get(); }
};

} // namespace graph
