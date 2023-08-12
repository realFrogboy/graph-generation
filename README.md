# graph-generation

## 1. Reducible graph generator
Reducible graph generator.

## 2. Dominance tree generator
Receive a dominance tree from a reducible graph.

## 3. DJ-graph generator
Receive a DJ-garph from a reducible graph and its dominance tree. 

## 4. Dominance frontier generator
Receive a dominance frontier from a dominance tree and DJ-graph. 

## Build

```sh
mkdir build && cd build
cmake ../
cmake -DCMAKE_BUILD_TYPE=Release ./
cmake --build ./
```

There are 2 executables: 
1. `build/tools/custom` <br />
Receive input format: <br />
**NOTE:** A node numbering should start with 0.
```
NNodes
Node -> Node
Node -> Node
...
```

2. `build/tools/generation` <br />
Receive input format:
```
NNodes
```

