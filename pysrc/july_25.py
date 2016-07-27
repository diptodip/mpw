from os import system
from graphs import *
from mpw import *
from string import rfind
from math import sqrt
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
plt.style.use("ggplot")

prefix = "32-node-k-{0}-{1}"

k_values = []
single_costs = []
disjoint_costs = []

OPT = set()
done = False
#while len(OPT) is 0:
while not done:
    system("../gensen")
    nodes = []
    edges = {}
    locations = {}
    x_coordinates = []
    y_coordinates = []
    with open("random_topology.tcl") as f:
        n = 0
        while len(nodes) is not 32:
            line = f.readline()
            if "node_" in line:
                xindex = line.rfind("_")
                xindex += 2
                x = float(line[xindex:])
                line = f.readline()
                yindex = line.rfind("_")
                yindex += 2
                y = float(line[yindex:])
                node = Vertex(n, 0, {})
                n += 1
                nodes.append(node)
                locations[node] = (x, y)
                x_coordinates.append(x)
                y_coordinates.append(y)
    #print(nodes)
    #print(locations)
    s = nodes[0]
    t = nodes[31]
    #max_neighbors = 7
    """
    for node in nodes:
        if node is s:
            node_x, node_y = locations[node]
            for neighbor in nodes:
                if neighbor is not s and neighbor is not t:
                    neigh_x, neigh_y = locations[neighbor]
                    cost = sqrt((neigh_x - node_x)**2 + (neigh_y - node_y)**2)
                    cost = cost**2
                    node.neighbors[neighbor] = cost
                    edges[(node, neighbor, 0)] = (cost, 1)
        if node is not t:
            node_x, node_y = locations[node]
            for neighbor in nodes:
                if neighbor is not node and neighbor is not s:
                    neigh_x, neigh_y = locations[neighbor]
                    cost = sqrt((neigh_x - node_x)**2 + (neigh_y - node_y)**2)
                    cost = cost**2
                    node.neighbors[neighbor] = cost
                    edges[(node, neighbor, 0)] = (cost, 1)
    """
    for node in nodes:
        node_x, node_y = locations[node]
        for neighbor in nodes:
            if neighbor is not node:
                neigh_x, neigh_y = locations[neighbor]
                cost = sqrt((neigh_x - node_x)**2 + (neigh_y - node_y)**2)
                cost = cost**2
                node.neighbors[neighbor] = cost
                edges[(node, neighbor, 0)] = (cost, 1)
    
    G = Graph(nodes, edges)
    OPT, opt = minimum_energy_disjoint_paths(G, 0, 31, 2)

    if len(OPT) > 0:
        print(OPT)
        """
        plt.figure()
        graph_plot, = plt.plot(x_coordinates, y_coordinates, 'ro', label='')
        source_plot, = plt.plot([locations[nodes[0]][0]], [locations[nodes[0]][1]], 'bo', label='')
        sink_plot, = plt.plot([locations[nodes[31]][0]], [locations[nodes[31]][1]], 'go', label='')
        for (u, v, x) in list(OPT):
            if "'" not in u.name and "'" in v.name:
                u_ind = int(u.name)
                v_ind = int(v.name[:-1])
                if u_ind != v_ind:
                    #print((u_ind, v_ind))
                    u_x, u_y = locations[nodes[u_ind]]
                    v_x, v_y = locations[nodes[v_ind]]
                    plt.plot([u_x, v_x], [u_y, v_y], color = 'k', linestyle='-', linewidth=2)
            elif "'" in u.name and "'" not in v.name:
                u_ind = int(u.name[:-1])
                v_ind = int(v.name)
                if u_ind != v_ind:
                    #print((u_ind, v_ind))
                    u_x, u_y = locations[nodes[u_ind]]
                    v_x, v_y = locations[nodes[v_ind]]
                    plt.plot([u_x, v_x], [u_x, v_y], color = 'k', linestyle='-', linewidth=2)
            elif "'" not in u.name and "'" not in v.name:
                u_ind = int(u.name)
                v_ind = int(v.name)
                if u_ind != v_ind:
                    #print((u_ind, v_ind))
                    u_x, u_y = locations[nodes[u_ind]]
                    v_x, v_y = locations[nodes[v_ind]]
                    plt.plot([u_x, v_x], [u_y, v_y], color = 'k', linestyle='-', linewidth=2)

        plt.savefig("graphvis.png", format="png", dpi=300)
        """
    done = True
