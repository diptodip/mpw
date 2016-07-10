def minimum_energy_single_path(G):
    paths, costs = djikstra(G, 0)
    min_vertex = min(costs, key=costs.get)
    return paths[min_vertex]

def minimum_energy_disjoint_paths(G, ):
    V = G.V
    E = G.E
