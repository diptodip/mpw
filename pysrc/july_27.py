from graphs import *
from mpw import *
from math import sqrt
from random import uniform
from random import random
from random import sample
from random import randint

clique_size = 64

MIN_COST = 100
MAX_COST = 2000

num_neighbors = 16

vertices = []
edges = {}
locations = {}

s = Vertex(0, 0, {})
vertices.append(s)

for i in range(num_neighbors):
    v = Vertex(i+1, 0, {})
    vertices.append(v)
    cost = uniform(MIN_COST, MAX_COST)
    s.neighbors[v] = cost
    edges[(s, v, 0)] = (cost, 1)

for i in range(clique_size):
    v = Vertex(i+1+num_neighbors, 0, {})
    vertices.append(v)

for i in range(clique_size):
    v = vertices[i+1+num_neighbors]
    for j in range(clique_size):
        n = vertices[j+1+num_neighbors]
        if random() > 0.33:
            cost = uniform(MIN_COST, MAX_COST)
            v.neighbors[n] = cost
            edges[(v, n, 0)] = (cost, 1)

for i in range(num_neighbors):
    v = vertices[i+1]
    clique_points = [vertices[j+1+num_neighbors] for j in range(clique_size)]
    neighbors = sample(clique_points, randint(len(clique_points)//3, len(clique_points)))
    for n in neighbors:
        cost = uniform(MIN_COST, MAX_COST)
        v.neighbors[n] = cost
        edges[(v, n, 0)] = (cost, 1)


G = Graph(vertices, edges)

OPT, opt = minimum_energy_disjoint_paths(G, 0, 40, 6)

print(OPT)
