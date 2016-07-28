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

prefix = "100-node-k-{0}-{1}"

k_values = [2, 3, 4, 5, 6]
table = "\\begin{tabular}{| c | c | c | c | c | c |}\n"
table += "\hline\n"
table += "k & average single path value & single path standard deviation & average disjoint paths value & disjoint paths standard deviation & average disjoint paths increase factor \\\\ \hline\n"
for k in k_values:
    single_costs = []
    disjoint_costs = []
    
    print("k: " + str(k))

    while len(single_costs) is not 50 and len(disjoint_costs) is not 50:
        print("current iteration: " + str(len(single_costs)))
        system("../gensen -n 100")
        nodes = []
        edges = {}
        locations = {}
        x_coordinates = []
        y_coordinates = []
        with open("random_topology.tcl") as f:
            n = 0
            while len(nodes) is not 100:
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
        t = nodes[80]
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
            if node is not t:
                for neighbor in nodes:
                    if neighbor is not node and neighbor is not s:
                        neigh_x, neigh_y = locations[neighbor]
                        cost = sqrt((neigh_x - node_x)**2 + (neigh_y - node_y)**2)
                        cost = cost**2
                        node.neighbors[neighbor] = cost
                        edges[(node, neighbor, 0)] = (cost, 1)
        
        G = Graph(nodes, edges)
        G_ = Graph(nodes[:], dict(edges))
        path, single_cost = minimum_energy_single_path(G, 0, 99)
        paths, OPT, opt = minimum_energy_disjoint_paths(G, 0, 99, k)

        if len(OPT) > 0:
            print(paths)
            print(opt)
            print(path)
            print(single_cost)
            single_costs.append(single_cost)
            disjoint_costs.append(opt)
            G_.write_graph(prefix.format(k, len(disjoint_costs)) + "-graph.grf")
            with open(prefix.format(k, len(disjoint_costs))+"-solution.uns", 'w') as f:
                f.write("single cost solution\n")
                f.write(str(path)+"\n")
                f.write(str(single_cost)+"\n")
                f.write("disjoint paths solution\n")
                f.write(str(paths)+"\n")
                f.write(str(opt)+"\n")
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
    single_average = np.average(single_costs)
    disjoint_average = np.average(disjoint_costs)
    single_std = np.std(single_costs)
    disjoint_std = np.std(disjoint_costs)
    factor = disjoint_average / single_average
    table += str(single_average) + " & " + str(single_std) + " & " + str(disjoint_average) + " & " + str(disjoint_std) + " & " + str(factor) + " \\\\ \\hline\n"
    with open(prefix.format(k, "table")+".tex", 'w') as f:
        f.write(table)
    plt.figure()
    cost_plot, = plt.plot(single_costs, disjoint_costs, color = 'r', marker = 'o', linestyle='-', linewidth=2, label='')
    plt.xlabel("single path cost")
    plt.ylabel("disjoint paths cost")
    plt.title("{}-disjoint paths cost vs. single path cost".format(k))
    plt.savefig(prefix.format(k, "plot")+".png", format='png', dpi=300)
