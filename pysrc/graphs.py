import numpy as np
import random as rng
import itertools

MIN_COST = 10
MAX_COST = 100
MIN_POWER = 10
MAX_POWER = 100

class Vertex:
    def __init__(self, name, power, neighbors):
        self.name = name
        self.power = power
        self.neighbors = neighbors # dict of neighbor : distance
    
    def __str__(self):
        return "V{}".format(self.name)

    def __repr__(self):
        return "V{}".format(self.name)

class Graph:
    def __init__(self, V, E):
        self.V = V
        self.E = E
        self.H = np.zeros((len(self.V), len(self.V)), dtype=np.int16)
        for i,j in itertools.product(range(len(self.V)), repeat=2):
            self.H[i, j] = self.E[i, j]
            if self.V[i].power < self.H[i, j]:
                self.H[i, j] = -1

def random_digraph(num_vertices):
    vertices = []
    edges = np.zeros((num_vertices, num_vertices), dtype=np.int16)
    for i in range(num_vertices):
        vertices.append(Vertex(i, rng.randint(MIN_POWER, MAX_POWER), {}))
    v_c = 0
    for v in vertices:
        n_c = 0
        for n in vertices:
            cost = rng.randint(MIN_COST, MAX_COST)
            if n is not v and v.power >= cost:
                v.neighbors[n] = cost
                edges[v_c, n_c] = cost
            elif n is not v:
                edges[v_c, n_c] = cost
            else:
                edges[v_c, n_c] = 0
            n_c += 1
        v_c += 1
    return Graph(vertices, edges)

def binary_digraph(num_vertices):
    vertices = []
    edges = np.zeros((num_vertices, num_vertices))
    for i in range(num_vertices):
        vertices.append(Vertex(i, rng.randint(0, 1), {}))
    v_c = 0
    for v in vertices:
        n_c = 0
        for n in vertices:
            cost = rng.randint(0, 1)
            if n is not v and v.power >= cost:
                v.neighbors[n] = cost
                edges[v_c, n_c] = cost
            elif n is not v:
                edges[v_c, n_c] = cost
            else:
                edges[v_c, n_c] = 0
            n_c += 1
        v_c += 1
    return Graph(vertices, edges)

def djikstra(G, source_index=0):
    s = G.V[source_index]
    paths = {}
    costs = {}
    for v in G.V:
        costs[v] = 1e40
        paths[v] = []
    costs[s] = 0
    paths[s] = [s]
    frontier = set(v for v in G.V)
    current = s
    for i in range(len(G.V)):
        frontier.discard(current)
        path = paths[current]
        cost = 1e40
        choose = current
        for neighbor in current.neighbors.keys():
            if costs[current] + current.neighbors[neighbor] < costs[neighbor]:
                costs[neighbor] = costs[current] + current.neighbors[neighbor]
                paths[neighbor] = path + [neighbor]
                if costs[neighbor] <= cost:
                    cost = costs[neighbor]
                    choose = neighbor
        current = choose
    return (paths, costs)

def main():
    G = random_digraph(10)
    solution = djikstra(G)
    print(solution)

if __name__ == "__main__": main()
