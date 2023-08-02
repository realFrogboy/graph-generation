#include "GraphDumpTy.hpp"

#include <fstream>

namespace graph {

void GraphDumpTy::operator()(const std::vector<NodePtr> &Nodes, const std::string &Filename) const {
    std::ofstream File(Filename);
    File << "digraph tree {\n";

    for (auto &Node : Nodes) {
        File << "\tnode" << Node->getID() << " [shape = \"record\", label = \"" << Node->getID() << "\"];\n";
    }

    for (auto &Node : Nodes) {
        for (auto Child : Node->getChildren())
            File << "node" << Node->getID() << " -> node" << Child->getID() << ";\n";
    }

    File << "}";
    return;
}

} // namespace graph
