#pragma once

#include "NodeTy.hpp"
#include "GraphDumpTy.hpp"
#include "ReducibleGraphTy.hpp"

#include <set>
#include <memory>
#include <vector>
#include <functional>
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
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;

    static std::set<NodeTy*> Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs);

    void runDFS() const { DFS->run(Nodes.front().get()); }
    unsigned getDFSPosition(const unsigned NodeID) const { return DFS->getPosition(NodeID); }
    
    NodeTy *getIDominator(NodeTy *Node) const;

    void initDominatorSets();
    void generate();

    public:
    DominanceTreeTy(const ReducibleGraphTy &Graph);
    void print() const {  Dump(Nodes, "DomTree.dot"); }

    const NodeTy *getNode(const unsigned NodeID) const { return Nodes[NodeID].get(); }
};

} // namespace graph
