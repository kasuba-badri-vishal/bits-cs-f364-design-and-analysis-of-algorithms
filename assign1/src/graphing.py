import networkx as nx
import sys
import matplotlib.pyplot as plt

DG = nx.DiGraph()

with open(sys.argv[1]) as edges_file:
    v,e = map(int, edges_file.readline().split())
    for i in range(e):
        x,y = map(int, edges_file.readline().split())
        DG.add_weighted_edges_from([(x, y, 1)])

options = {
    'node_size': 10,
    'width': 0.01,
    'edge_color': 'gray',
    'alpha':0.5
}

nx.draw(DG, **options)
plt.savefig("graphs/email.png")
# g_list = []
# un = nx.DiGraph()
# with open(sys.argv[2]) as scc:
#     s = scc.readlines()
#     for line in s:
#         V = map(int, line.split())
#         sub = nx.subgraph(DG, V)
        # g_list.append(sub)
        # un = nx.union(un, sub)
        # plt.subplot()
        # nx.draw(sub, **options)

# print(nx.number_connected_components(nx.to_undirected(un)))
# print(nx.number_connected_components(nx.to_undirected(DG)))
# nx.draw(un, **options)
# plt.savefig("email1.png")