#pragma once

#include "NodeTy.hpp"

namespace graph {

class GraphDumpTy final {
    using NodePtr = std::unique_ptr<NodeTy>;

    public:
    void operator()(const std::vector<NodePtr> &Nodes, const std::string &Filename) const;
};

} // namespace graph