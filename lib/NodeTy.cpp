#include "NodeTy.hpp"

#include <random>
#include <algorithm>

namespace {

bool randomBool() {
    std::random_device Rd;
    std::seed_seq seed2{Rd(), Rd(), Rd(), Rd(), Rd(), Rd(), Rd(), Rd()};
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1), std::default_random_engine(seed2));
    return gen();
}

} // namespace

namespace graph {

void NodeTy::reverseT2(NodeTy *Node) {
    Children.erase(std::remove_if(Children.begin(), Children.end(), [Node, this](NodeTy *Child) {
        if (randomBool() || Child == this) {
            Node->addNewChild(Child);
            return 1;
        }
        return 0;
    }), Children.end());
    Children.push_back(Node);
}

} // namespace graph
