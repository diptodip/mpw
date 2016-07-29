# Minimum Power Wireless Network Routing Algorithms

**Note:** This project is over and incomplete.

## Introduction
Simulation code for minimum power routing schemes in ad-hoc wireless networks. Part of BigDataX REU 2016.

## Location files

Location files are stored as .loc files. They contain (x, y) coordinates of each node. Each line represents a node. The first number of a line is the x coordinate and the second number (separated by a space) is the y coordinate. The first line represents the first node (indexing from 0) and is designated as the source. The last line represents the last node and represents the sink.

## Graph files

Graph files are stored as .grf files. The first line of a graph file denotes the number of nodes $n$ in the graph. The next $n$ lines denote the power of the vertex (although this is often not used). The following $n$ lines comprise a matrix that denotes the costs of edges between vertices of the graph. If a cost is -1, there is no edge between those two vertices.

## k-Disjoint Paths

This algorithm is implemented in ``mpw.py`` as ``minimum_energy_disjoint_paths``.
