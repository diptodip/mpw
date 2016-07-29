import numpy as np
import random as rng
import itertools
from collections import deque

MIN_COST = 10
MAX_COST = 100
MIN_POWER = 10
MAX_POWER = 100

class Vertex:
    def __init__(self, name, power, neighbors):
        self.name = str(name)
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

    def write_graph(self, filename):
        with open(filename, 'w') as f:
            f.write(str(len(self.V)) + "\n")
            for v in self.V:
                f.write(str(v.power) + "\n")
            for v in self.V:
                costs = ""
                for n in self.V:
                    if n in v.neighbors:
                        costs += str(v.neighbors[n]) + " "
                    else:
                        costs += str(-1) + " "
                costs = costs[:-1]
                costs += "\n"
                f.write(costs)

    def read_graph(self, filename):
        vertices = []
        edges = {}
        with open(filename) as f:
            num_vertices = int(f.readline())
            for i in range(num_vertices):
                power = float(f.readline())
                v = Vertex(i, power, {})
                vertices.append(v)
            for v in vertices:
                line = f.readline()
                strings = line.split()
                costs = [float(s) for s in strings]
                print(costs)
                for i in range(len(costs)):
                    cost = costs[i]
                    if cost > -1:
                        v.neighbors[vertices[i]] = cost
                        edges[(v, vertices[i], 0)] = (cost, 1)
        self.V = vertices
        self.E = edges

def random_digraph(num_vertices):
    vertices = []
    edges = {}
    for i in range(num_vertices):
        vertices.append(Vertex(i, rng.randint(MIN_POWER, MAX_POWER), {}))
    for v in vertices:
        for n in vertices:
            cost = rng.randint(MIN_COST, MAX_COST)
            if n is not v and v.power >= cost:
                v.neighbors[n] = cost
                edges[(v, n, 0)] = (cost, 1)
            elif n is not v:
                pass
    return Graph(vertices, edges)

def bfs(G, source_index=0):
    s = G.V[source_index]
    frontier = deque()
    visited = set()
    frontier.append(s)
    while len(frontier) > 0:
        current = frontier.popleft()
        visited.add(current)
        for neighbor in current.neighbors.keys():
            if neighbor not in visited:
                frontier.append(neighbor)
    return visited

def connected(G, source_index=0):
    reached = bfs(G, source_index)
    if len(reached) < len(G.V):
        return False
    else:
        return True

def djikstra(G, source_index=0):
    s = G.V[source_index]
    paths = {}
    costs = {}
    for v in G.V:
        costs[v] = 1e40
        paths[v] = []
    costs[s] = 0
    paths[s] = [s]
    current = s
    for i in range(len(G.V)):
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
