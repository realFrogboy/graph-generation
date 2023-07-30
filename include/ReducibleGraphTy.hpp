#pragma once

#include "NodeTy.hpp"

#include <set>
#include <memory>
#include <vector>
#include <unordered_map>

namespace graph{

class ReducibleGraphTy;

class DFSTy final {
    const ReducibleGraphTy &Graph;
    std::unordered_map<unsigned, unsigned> Positions;
    public:
    DFSTy(const ReducibleGraphTy &Graph) : Graph{Graph} {}
    void run();
    unsigned getPosition(const unsigned NodeID) const { return Positions.at(NodeID); }
};

class DominanceTreeTy final {
    using NodePtr = std::unique_ptr<NodeTy>;
    
    std::vector<NodePtr> Nodes;
    std::vector<std::set<NodeTy*>> DominatorSets;

    static std::set<NodeTy*> Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs);
    void initDominatorSets(const ReducibleGraphTy &Graph);
    NodeTy *getIDominator(NodeTy *Node, const ReducibleGraphTy &Graph) const;
    void generate(const ReducibleGraphTy &Graph);

    public:
    DominanceTreeTy(const ReducibleGraphTy &Graph);
    void print() const;
};

class ReducibleGraphTy final {
    using NodePtr = std::unique_ptr<NodeTy>;

    std::vector<NodePtr> Nodes;
    std::unique_ptr<DFSTy> DFS;

    NodeTy *getRandomNode() const;
    NodeTy *addNewNode();
    void reverseT1() const;
    void reverseT2();
    void generate(const size_t Size);

    public:
    ReducibleGraphTy(const size_t Size);
    void runDFS() const { DFS->run(); }
    void print() const;

    NodeTy *getRoot() const { return Nodes.front().get(); }
    unsigned getDFSPosition(const unsigned NodeID) const { return DFS->getPosition(NodeID); }
    size_t getNNodes() const { return Nodes.size(); }
    const std::vector<NodePtr> &getNodes() const { return Nodes; }
};

} // namespace graph
