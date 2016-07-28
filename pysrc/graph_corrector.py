import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
plt.style.use("ggplot")

plot_prefix = "100-node-k-{}-plot.png"
solution_prefix = "100-node-k-{0}-{1}-solution.uns"

k_values = [2, 3, 4]

for k in k_values:
    print("k: " + str(k))
    single_costs = []
    disjoint_costs = []
    for i in range(50):
        single_cost = 0
        disjoint_cost = 0
        with open(solution_prefix.format(k, i+1)) as f:
            line = f.readline()
            line = f.readline()
            line = f.readline()
            single_cost = float(line)
            line = f.readline()
            line = f.readline()
            line = f.readline()
            disjoint_cost = float(line)
        single_costs.append(single_cost)
        disjoint_costs.append(disjoint_cost)
    A = np.array([single_costs, np.ones(len(single_costs))])
    w = np.linalg.lstsq(A.T, disjoint_costs)[0]
    print(w)
    line = w[0]*single_costs+w[1]
    plt.figure()
    plt.plot(single_costs, disjoint_costs, 'bo')
    plt.plot(single_costs, line, 'r-')
    plt.savefig(plot_prefix.format(k), format="png", dpi=300)
