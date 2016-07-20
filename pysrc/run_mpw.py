from mpw import *
from graphs import *

v1 = Vertex(1, 50, {})
v2 = Vertex(2, 50, {})
v3 = Vertex(3, 50, {})
v4 = Vertex(4, 50, {})
v5 = Vertex(5, 50, {})
v6 = Vertex(6, 50, {})
v1.neighbors[v2] = 30
v1.neighbors[v3] = 3
v1.neighbors[v4] = 4
v1.neighbors[v5] = 5
v2.neighbors[v6] = 2
v3.neighbors[v6] = 3
v4.neighbors[v6] = 4
v5.neighbors[v6] = 5
vertices = [v1, v2, v3, v4, v5, v6]
edges = {}
edges[(v1, v2, 0)] = (30, 1)
edges[(v2, v6, 0)] = (2, 1)
edges[(v1, v3, 0)] = (3, 1)
edges[(v3, v6, 0)] = (3, 1)
edges[(v1, v4, 0)] = (4, 1)
edges[(v4, v6, 0)] = (4, 1)
edges[(v1, v5, 0)] = (5, 1)
edges[(v5, v6, 0)] = (5, 1)


G = Graph(vertices, edges)

OPT = minimum_energy_disjoint_paths(G, 0, 5, 2)
print(OPT)
