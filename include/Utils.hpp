#pragma once

#include "NodeTy.hpp"
#include "GraphTy.hpp"

#include <memory>
#include <limits>
#include <iostream>

namespace graph::utils {

template <class T>
class MakeUnique {
    public:
    explicit MakeUnique(size_t Value) : Value{Value} {}
    operator std::unique_ptr<T>() {
        return std::unique_ptr<T>(new T(Value));
    }
    MakeUnique &operator++() { ++Value; return *this; }

    private:
    size_t Value;
};

class RPOTy final {
    const GraphTy &Graph;

    std::vector<size_t> Positions;
    std::vector<NodeTy*> Order;

    public:
    RPOTy(const GraphTy &Graph) : Graph{Graph}, Positions(Graph.getNNodes(), std::numeric_limits<size_t>::max()), Order(Graph.getNNodes()) {}
    void run() { 
        std::vector<const NodeTy*> Fronteir{Graph.getRoot()};
        std::vector<const NodeTy*> Head{};
        std::vector<unsigned> Visited(Graph.getNNodes(), 0);
        size_t N = Graph.getNNodes();

        while (!Fronteir.empty()) {
            const NodeTy *Node = Fronteir.back();
            size_t NodeID = Node->getID();

            Visited[NodeID] = 1;

            if (!Head.empty() && Node == Head.back()) {
                Fronteir.pop_back();
                Head.pop_back();
                Positions[NodeID] = --N;
                Order[N] = Graph.getNode(NodeID);
            } else {
                if (Positions[Node->getID()] != std::numeric_limits<size_t>::max()) {
                    Fronteir.pop_back();
                    continue;
                }
                Head.push_back(Node);
                for (auto Child : Node->getChildren())
                    if (!Visited[Child->getID()])
                        Fronteir.push_back(Child);
            }
        }
    } 
    size_t getPosition(const size_t NodeID) const { return Positions.at(NodeID); }
    const std::vector<NodeTy*> &getOrder() const { return Order; }
};

} // namespace graph::utils