import numpy as np
import random as rng
import itertools

MAX_DISTANCE = 100

class Vertex:
    def __init__(self, name, neighbors):
        self.name = name
        self.neighbors = neighbors # dict of neighbor : distance
    
    def __str__(self):
        return "V{}".format(self.name)

    def __repr__(self):
        return "V{}".format(self.name)

class Graph:
    def __init__(self, V=[]):
        self.V = V
        self.E = np.zeros((len(V), len(V)))
        for i, j in itertools.product(range(len(V)), repeat=2):
            self.E[i, j] = -1
            if self.V[i].neighbors.has_key(self.V[j]):
                self.E[i, j] = self.V[i].neighbors[self.V[j]]

def random_digraph(num_vertices):
    vertices = []
    for i in range(num_vertices):
        vertices.append(Vertex(i, {}))
    for v in vertices:
        neighbors = rng.sample(vertices, rng.randint(1, num_vertices))
        if v in neighbors:
            neighbors.remove(v)
        for neighbor in neighbors:
            v.neighbors[neighbor] = rng.randint(1, MAX_DISTANCE)
    return Graph(vertices)

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
    solution = djikstra_minpath(G)
    print(solution)

if __name__ == "__main__": main()
