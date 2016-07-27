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

for k in range(14):
    print("k: " + str(k))
    k += 2
    ksingle_costs = []
    kdisjoint_costs = []
    kdisjoint_ratios = []
    i = 0
    while i is not 50:
        try:
            print("iteration: " + str(i))
            system("../gensen")
            nodes = []
            edges = {}
            locations = {}
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
            print(nodes)
            print(locations)
            with open("random.tcl") as f:
                n = 0
                while n is not 32:
                    line = f.readline()
                    if "initialEnergy" in line:
                        index = line.rfind("Energy")
                        index += 7
                        power = float(line[index:index+8])
                        nodes[n].power = power
                        n += 1
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
            P, p = minimum_energy_single_path(G, 0, 31)
            OPT, opt = minimum_energy_disjoint_paths(G, 0, 31, k)
            print(OPT)
            ksingle_costs.append(p)
            kdisjoint_costs.append(opt)
            kdisjoint_ratios.append(opt / p)
            i += 1
        except:
            continue
    """
    ksingle_average = np.average(ksingle_costs)
    kdisjoint_average = np.average(kdisjoint_costs)
    single_costs.append(ksingle_average)
    disjoint_costs.append(kdisjoint_average)
    k_values.append(k)

    plt.figure()
    plt.title("Cost increase of {}-disjoint paths vs. cost of single path".format(k))
    plt.xlabel("single path cost")
    plt.ylabel("{}-disjoint paths cost increase factor".format(k))
    single_plot, = plt.plot(ksingle_costs, kdisjoint_ratios, 'bo', label='')
    plt.savefig("july_24_{}_graph.png".format(k), format="png", dpi=300)
    plt.clf()

plt.figure()
plt.title("Average costs of single path and k-disjoint paths as k increases")
plt.xlabel("k value")
plt.ylabel("cost")
single_plot, = plt.plot(k_values, single_costs, 'bo', label='single path cost')
disjoint_plot, = plt.plot(k_values, disjoint_costs, 'rx', label='k-disjoint paths cost')
plt.legend(handles=[single_plot, disjoint_plot])
plt.savefig("july_24_average_graph.png", format="png", dpi=300)
plt.clf()
"""
