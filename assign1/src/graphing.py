import networkx as nx
import sys
import numpy as np
import matplotlib.pyplot as plt

'''
Constructing graph for the whole dataset.
'''
# getting name of dataset from the filepath passed as cmdline argument
dataset_name = sys.argv[1].split('/')[-1][:-4]

# Empty Directed Graph
DG = nx.DiGraph()

# Constructing graph from dataset file
with open(sys.argv[1]) as edges_file:
    v,e = map(int, edges_file.readline().split())
    for i in range(e):
        line = edges_file.readline()
        # break for the "Time taken" line.
        if "ime" in line: break
        x,y = map(int, line.split())
        DG.add_weighted_edges_from([(x, y, 1)])

shape = nx.spring_layout(DG)
options = {
    'node_size': 20,
    'width': 0.1,
    'alpha':0.6,
    'edge_color': '#333333',
    'pos':shape
}
nx.draw(DG, **options)
plt.title(dataset_name)
plt.savefig(f"results/graphs/{dataset_name}.png")
# plt.show()

'''
Constructing graph for Strongly Connected Components using 
the output files in results folder.
'''
comp_graph = nx.DiGraph()
colors = np.array([])
c = 0
with open(sys.argv[2]) as scc:
    s = scc.readlines()
    for line in s:
        if "ime" in line: break
        V = list(map(int, line.split()))
        if(len(V)==0): break
        sub = DG.subgraph(V)
        colors = np.append(colors, np.ones((len(V), )) * np.random.randint(255))
        # colors = np.append(colors, np.array([(np.random.randint(100), np.random.randint(100), np.random.randint(100))]*len(V)))
        comp_graph = nx.union(comp_graph, sub)

shape = nx.spring_layout(comp_graph)
options = {
    'node_size': 20,
    'width': 0.1,
    'edge_color': '#333333',
    'alpha':0.5,
    "node_color":colors,
    'pos':shape,
    'cmap':'jet'
}
plt.figure()
nx.draw(comp_graph, **options)
plt.savefig(f"results/graphs/{dataset_name}_comp.png")
# plt.show()