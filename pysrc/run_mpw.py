from mpw import *
from graphs import *

G = binary_digraph(100)
while not connected(G, 0):
    G = binary_digraph(100)
write_mpb(G, 0, "test.mpb")
