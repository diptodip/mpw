from graphs import *

def mku_generate(size):
    while f

def minimum_energy_single_path(G, source_index, sink_index):
    s = G.V[source_index]
    t = G.V[sink_index]
    paths, costs = djikstra(G, source_index)
    return paths[t]

def minimum_energy_disjoint_paths(G, source_index, sink_index, k):
    V = G.V
    E = G.E
    H = G.H
    arcs = G.arcs
    s = G.V[source_index]
    t = G.V[sink_index]
    G = node_disjoint(G)
    M = len(V) * max(H)
    sorted_neighbors = sort_neighbors(s, G)

def write_mku(G, source_index, sink_index, filename):
    with open(filename, 'w') as f:
        f.write(str(len(G.V)) + "\n")
        f.write(str(source_index) + "\n")
        f.write(str(sink_index) + "\n")
        for i in range(len(G.V)):
            f.write(str(G.V[i].power) + "\n")
        for i in range(len(G.V)):
            line = ""
            for j in range(len(G.V)):
                line += str(G.E[i, j]) + " "
            line = line[:-1]
            line += "\n"
            f.write(line)
        for i in range(len(G.V)):
            line = ""
            for j in range(len(G.V)):
                line += str(G.H[i, j]) + " "
            line = line[:-1]
            line += "\n"
            f.write(line)

def write_mpb(G, source_index, filename):
    with open(filename, 'w') as f:
        f.write(str(len(G.V)) + "\n")
        f.write(str(source_index) + "\n")
        for i in range(len(G.V)):
            f.write(str(G.V[i].power) + "\n")
        for i in range(len(G.V)):
            line = ""
            for j in range(len(G.V)):
                line += str(G.E[i, j]) + " "
            line = line[:-1]
            line += "\n"
            f.write(line)
        for i in range(len(G.V)):
            line = ""
            for j in range(len(G.V)):
                line += str(G.H[i, j]) + " "
            line = line[:-1]
            line += "\n"
            f.write(line)
