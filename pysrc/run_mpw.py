from mpw import *
from graphs import *

G = random_digraph(20)
write_mpb(G, 0, "test.mpb")
solution = minimum_energy_single_path(G, 0, 9)
print(solution)
