from graphs import *

def minimum_energy_single_path(G, source_index, sink_index):
    s = G.V[source_index]
    t = G.V[sink_index]
    paths, costs = djikstra(G, source_index)
    return paths[t]

def add_neighbor(G, s, s_i, cost):
    G.E[(s, s_i, 0)] = (cost, 1)
    G.E[(s_i, s, 0)] = (0 - cost, 0)
    s.neighbors[s_i] = cost

def node_disjoint_transformation(G_, s, t):
    V = G_.V[:]
    G = Graph(G_.V[:], dict(G_.E))
    for u in G.V:
        if u is not s and u is not t:
            u_prime = Vertex(u.name + "'", u.power, u.neighbors)
            V.append(u_prime)
            u.neighbors = {}
            u.neighbors[u_prime] = 0
            G.E[(u, u_prime, 0)] = (0, 1)
            for neighbor in u_prime.neighbors:
                (cost, capacity) = G.E[(u, neighbor, 0)]
                G.E.pop((u, neighbor, 0), None)
                G.E[(u_prime, neighbor, 0)] = (cost, capacity)
    G.V = V
    return G

def positive_cost_transformation(G, d):
    a = {}
    for e in G.E.keys():
        a[e] = G.E[e][0] + d[e[0]] - d[e[1]]
    return a

def residual_graph(G_, f):
    G = Graph(G_.V[:], dict(G_.E))
    for (u, v, x) in f.keys():
        if f[(u, v, x)] > 0 and G.E.has_key((u, v, x)) and G.E[(u, v, x)][0] >= 0:
            if G.E[(u, v, x)][0] >= 0:
                weight, capacity = G.E[(u, v, x)]
                if capacity == f[(u, v, x)]:
                    G.E.pop((u, v, x), None)
                else:
                    G.E[(u, v, x)] = (weight, capacity - f[(u, v, x)])
                G.E[(v, u, x)] = (0 - weight, f[(u, v, x)])
    for (u, v, x) in f.keys():
        if f[(u, v, x)] > 0 and G.E.has_key((u, v, x)) and G.E[(u, v, x)][0] < 0:
            weight, capacity = G.E[(u, v, x)]
            if capacity == f[(u, v, x)]:
                G.E.pop((u, v, x), None)
            else:
                G.E[(u, v, x)] = (weight, capacity - f[(u, v, x)])
    return G

def djikstra_path(G, s, t, a, sink):
    source = t
    d = {v: 1e40 for v in G.V}
    P = {v: [] for v in G.V}
    P[s] = [s]
    d[s] = 0
    current = s
    for i in range(len(G.V)):
        path = P[current]
        cost = 1e40
        choose = current
        neighbors = [(v, x) for (u, v, x) in a.keys() if u is current]
        for (neighbor, x) in neighbors:
            if d[current] + a[(current, neighbor, x)] < d[neighbor]:
                d[neighbor] = d[current] + a[(current, neighbor, x)]
                P[neighbor] = path + [neighbor]
                if d[neighbor] <= cost:
                    cost = d[neighbor]
                    choose = neighbor
        current = choose
    path = []
    for i in range(len(P[t]) - 1):
        u = P[t][i]
        v = P[t][i+1]
        if u is not sink or v is not source:
            path.append((u, v, 0))
        else:
            path.append((u, v, 1))
        if v is t:
            break
    P = path
    return (P, d)

def djikstra_distances(G, s, a):
    d = {v: 1e40 for v in G.V}
    d[s] = 0
    current = s
    for i in range(len(G.V)):
        cost = 1e40
        choose = current
        neighbors = [(v, x) for (u, v, x) in a.keys() if u is current]
        for neighbor in neighbors:
            if d[current] + a[(current, neighbor[0], neighbor[1])] < d[neighbor[0]]:
                d[neighbor[0]] = d[current] + a[(current, neighbor[0], neighbor[1])]
                if d[neighbor[0]] <= cost:
                    cost = d[neighbor[0]]
                    choose = neighbor[0]
        current = choose
    return d

def augment_flow(G, f, P):
    for e in P:
        if f.has_key(e) and G.E[e][1] > 0:
            f[e] += 1
        elif not f.has_key(e) and G.E[e][1] > 0:
            f[e] = 1

def calc_path_cost(P, E):
    cost = 0
    for e in P:
        cost += E[e][0]
    return cost

def calc_flow_cost(f, E):
    cost = 0
    for e in f.keys():
        if E.has_key(e):
            cost += f[e] * E[e][0]
        else:
            print("error: " + str(e))
    return cost

def add_auxiliary_arcs(G, s, M, n, sorted_neighbors):
    for u in G.V:
        if u is not s and u not in sorted_neighbors:
            G.E[(s, u, 1)] = (M, 2*n + 1)
        elif u is not s:
            G.E[(s, u, 1)] = (M, n + 1)

def sort_neighbors(G, s):
    neighbors = [n for n in s.neighbors.keys()]
    costs = [s.neighbors[n] for n in neighbors]
    out = [s_i for (cost, s_i) in sorted(zip(costs, neighbors), key=lambda pair: pair[0])]
    return out

def remove_source_arcs(G_, s):
    G = Graph(G_.V[:], dict(G_.E))
    for n in s.neighbors.keys():
        G.E.pop((s, n, 0), None)
    return G

def merge_dicts(*dicts):
    out = {}
    for d in dicts:
        out.update(d)
    return out

def minimum_energy_disjoint_paths(G, source_index, sink_index, k):
    V = G.V
    E = G.E
    s = G.V[source_index]
    t = G.V[sink_index]
    max_cost = 0
    neighbor_costs = {}
    for neighbor in s.neighbors.keys():
        neighbor_costs[neighbor] = E[(s, neighbor, 0)][0]
    for e in E.keys():
        if E[e][0] > max_cost:
            max_cost = E[e][0]
    M = len(V) * max_cost
    sorted_neighbors = sort_neighbors(G, s)
    G = node_disjoint_transformation(G, s, t)
    f = {}
    opt = 1e40
    OPT = set()
    d = {v: M for v in G.V}
    d[s] = 0
    G_i = remove_source_arcs(G, s)
    add_auxiliary_arcs(G_i, s, M, len(V), sorted_neighbors)
    for e in G_i.E:
        f[e] = 0
    for s_i in sorted_neighbors:
        f[(s, s_i, 0)] = 0
    f[(s, t, 1)] = k
    residual_G = residual_graph(G_i, f)
    prev_residual_G = residual_G
    i = 1
    while i <= len(sorted_neighbors):
        print("iteration: " + str(i))
        prev_a = positive_cost_transformation(residual_G, d)
        add_neighbor(G_i, s, sorted_neighbors[i-1], neighbor_costs[sorted_neighbors[i-1]])
        P, d_i_prime = djikstra_path(residual_G, sorted_neighbors[i-1], s, prev_a, t)
        for v in V:
            d_i_prime[v] = d_i_prime[v] + d[v] - d[sorted_neighbors[i-1]]
        c = d_i_prime[s]
        if c < 0:
            augment_flow(residual_G, f, P)
            f[(s, sorted_neighbors[i-1], 0)] = 1
            prev_residual_G = Graph(residual_G.V[:], dict(residual_G.E))
            residual_G = residual_graph(G_i, f)
            print("augmented flow")
        print("flow: " + str(f))
        a_i_prime = positive_cost_transformation(residual_G, d_i_prime)
        d = djikstra_distances(residual_G, s, a_i_prime)
        for v in V:
            d[v] = d[v] + d_i_prime[v] - d_i_prime[s]
        print("opt: " + str(opt))
        print("current: " + str(neighbor_costs[sorted_neighbors[i-1]] + calc_flow_cost(f, merge_dicts(G_i.E, prev_residual_G.E, residual_G.E, G.E))))
        if neighbor_costs[sorted_neighbors[i-1]] + calc_flow_cost(f, merge_dicts(G_i.E, prev_residual_G.E, residual_G.E, G.E)) <= opt:
            opt = neighbor_costs[sorted_neighbors[i-1]] + calc_flow_cost(f, merge_dicts(G_i.E, prev_residual_G.E, prev_residual_G.E, G.E))
            for e in G.E.keys():
                if f.has_key(e) and f[e] == 1:
                    OPT.add(e)
        i += 1
    return OPT

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
