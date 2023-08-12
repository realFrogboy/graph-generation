add_library(graphs DJGraphTy.cpp DominanceFrontierTy.cpp DominanceTreeTy.cpp GraphDumpTy.cpp NodeTy.cpp ReducibleGraphTy.cpp)

target_include_directories(graphs PUBLIC ${PUB_INCLUDE_DIR})