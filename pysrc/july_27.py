from graphs import *
from mpw import *
from math import sqrt
from random import uniform

clique_size = 32

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

f
