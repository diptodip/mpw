from graphs import *
from mpw import *

G = random_digraph(50)
OPT = minimum_energy_disjoint_paths(G, 0, 9, 2)
print(OPT)
