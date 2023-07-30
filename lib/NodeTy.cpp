#include "NodeTy.hpp"

#include <random>
#include <algorithm>
#include <exception>

namespace {

bool randomBool() {
    std::random_device Rd;
    std::seed_seq seed2{Rd(), Rd(), Rd(), Rd(), Rd(), Rd(), Rd(), Rd()};
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1), std::default_random_engine(seed2));
    return gen();
}

} // namespace

namespace graph {

void NodeTy::removeDublicates() {
    std::sort(Children.begin(), Children.end());
    Children.erase(std::unique(Children.begin(), Children.end()), Children.end());
}

void NodeTy::T1() { 
    Parents.erase(std::remove(Parents.begin(), Parents.end(), this), Parents.end());
    Children.erase(std::remove(Children.begin(), Children.end(), this), Children.end());
}

void NodeTy::reverseT1() { 
    Parents.push_back(this);
    Children.push_back(this); 
}

void NodeTy::reverseT2(NodeTy *Node) {
    Children.erase(std::remove_if(Children.begin(), Children.end(), [Node, this](NodeTy *Child) {
        if (randomBool() || Child == this) {
            Node->Children.push_back(Child);
            Child->Parents.push_back(Node);
            if (randomBool()) {
                auto It = std::find(Child->Parents.begin(), Child->Parents.end(), this);
                if (It == Child->Parents.end())
                    throw std::runtime_error("incorrect T2");
                
                Child->Parents.erase(It);
                return 1;
            }
        }
        return 0;
    }), Children.end());
    Children.push_back(Node);
    Node->Parents.push_back(this);
}

} // namespace graph
