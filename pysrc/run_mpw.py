from mpw import *
from graphs import *

v1 = Vertex(1, 50, {})
v2 = Vertex(2, 50, {})
v3 = Vertex(3, 50, {})
v4 = Vertex(4, 50, {})
v5 = Vertex(5, 50, {})
v1.neighbors[v2] = 2
v1.neighbors[v3] = 3
v1.neighbors[v4] = 4
v1.neighbors[v5] = 50
v2.neighbors[v1] = 50
v2.neighbors[v3] = 50
v2.neighbors[v4] = 50
v2.neighbors[v5] = 2
v3.neighbors[v1] = 50
v3.neighbors[v2] = 50
v3.neighbors[v4] = 50
v3.neighbors[v5] = 3
v4.neighbors[v1] = 50
v4.neighbors[v2] = 50
v4.neighbors[v3] = 50
v4.neighbors[v5] = 4
vertices = [v1, v2, v3, v4, v5]
edges = {}
edges[(v1, v2, 0)] = (2, 1)
edges[(v2, v5, 0)] = (2, 1)
edges[(v1, v3, 0)] = (3, 1)
edges[(v3, v5, 0)] = (3, 1)
edges[(v1, v4, 0)] = (4, 1)
edges[(v4, v5, 0)] = (4, 1)
edges[(v2, v1, 0)] = (50, 1)
edges[(v2, v3, 0)] = (50, 1)
edges[(v2, v4, 0)] = (50, 1)
edges[(v3, v1, 0)] = (50, 1)
edges[(v3, v2, 0)] = (50, 1)
edges[(v3, v4, 0)] = (50, 1)
edges[(v4, v1, 0)] = (50, 1)
edges[(v4, v2, 0)] = (50, 1)
edges[(v4, v3, 0)] = (50, 1)
edges[(v1, v5, 0)] = (50, 1)

G = Graph(vertices, edges)

OPT = minimum_energy_disjoint_paths(G, 0, 4, 3)
print(OPT)
