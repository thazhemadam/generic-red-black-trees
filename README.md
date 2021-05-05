# Red-Black Trees

## Introduction

Implementation of Red-Black trees in C++ using generic programming concepts, created as a part of coursework for Generic Programming.

### What are Red-Black Trees?

Red-Black trees are a type of self balancing binary search trees.\
Red-Black trees constrain the color of nodes on any simple path from root to a leaf, and thus ensure that no such path is twice as long as another, and that the tree is approximately balanced at all times.\

Each node in a Red-Black tree stores the following information:

* `parent` : pointer to the parent of node
* `left-child` : pointer to the left-child of the node.
* `right-child` : pointer to the right-child of the node.
* `color` : color of the node (either `RED` or `BLACK`)

If a child, or parent of a node does not exist, the corresponding pointer attribute of the node contains the value `NIL`. In this implementation, these `NIL`s have been regarded as pointers to the leaves(external nodes) of the binary search tree and the normal, key-bearing nodes as the internal nodes of the tree.

**Note**:
In this implementation, in an attempt to improve space efficiency, the `NIL` node is created as one centralized, common node, as opposed to the idea of spawning new `NIL` nodes for every leaf node in every tree.

### Red-Black Properties

A Red-Black tree is considered valid only if it satisfies the following red-black properties.

1. Every node is either `RED` or `BLACK`.
2. The root of the tree is `BLACK`.
3. Every leaf (`NIL`) is `BLACK`.
4. If a node is `RED`, then both its children are `BLACK`.
5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

## Getting Started

* Clone the repository
* From the root of the repository, run `make` to generate all the object files, and the final executable

```bash
#!/bin/sh
git clone git@github.com:thazhemadam/generic-red-black-trees.git
cd generic-red-black-trees
make
./RBT
```

## Directory Structure

* All header files belong in the `include/` directory
* All source files belong in the `src/` directory
* All object files are generated in the `bin/` directory
* The `Makefile` must be updated everytime a new file is added in either directory, appropriately.
* Object files are generated in `bin/` following the same directory structure as observed in `src/`.

## Team Members

* [Anant Thazhemadam](https://github.com/thazhemadam)
* [Roshini Bhaskar K](https://github.com/roshbhaskar)
* [Sampath Sri Harsha Durvasula](https://github.com/harsha-source)
