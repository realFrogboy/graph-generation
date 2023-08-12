#pragma once

#include "Utils.hpp"
#include "NodeTy.hpp"
#include "GraphTy.hpp"
#include "GraphDumpTy.hpp"
#include "ReducibleGraphTy.hpp"

#include <set>
#include <memory>
#include <vector>
#include <functional>

namespace graph {

class DominanceTreeTy final : public GraphTy {
    class DominatorSearcher final {
        const GraphTy &Graph;

        std::unique_ptr<utils::RPOTy> RPO;
        std::vector<std::set<NodeTy*>> DominatorSets;

        static std::set<NodeTy*> Intersection(std::set<NodeTy*> &Lhs, std::set<NodeTy*> &Rhs);
        void search();
        public:
        DominatorSearcher(const GraphTy &Graph);

        const std::set<NodeTy*> &getDominators(const size_t NodeID) const { return DominatorSets.at(NodeID); }
        size_t getIDominator(const size_t NodeID) const;
    };

    std::unique_ptr<DominatorSearcher> DS;
    std::function<void(const std::vector<NodePtr> &, const std::string &)> Dump;
    
    void generate();

    public:
    DominanceTreeTy(const ReducibleGraphTy &Graph);
    const std::set<NodeTy*> &getDominators(const size_t NodeID) const { return DS->getDominators(NodeID); }
    void print() const { Dump(Nodes, "DomTree.dot"); }
};

} // namespace graph
