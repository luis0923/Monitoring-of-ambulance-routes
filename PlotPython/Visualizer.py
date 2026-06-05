import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import networkx as nx
import os

 #CRIAÇÃO DO AMBIENTE
plt.style.use("dark_background")
fig, ax = plt.subplots(figsize =(12, 8))

fig.patch.set_facecolor("#0d1117")
ax.set_facecolor("#0d1117")
for spine in ax.spines.values():
    spine.set_visible(False)

#EXPORTAÇÃO DOS CAMINHOS

base = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(base, "..", "SearchAlgorithms", "PathOfEdges.csv")
edges_path = os.path.join(base, "..", "SearchAlgorithms", "edges.csv")

path_df = pd.read_csv(csv_path)
path = path_df["vertex"].tolist()

edges_df = pd.read_csv(edges_path)
edge_lookup = {(int(r["from"]), int(r["to"])): int(r["weight"]) for _, r in edges_df.iterrows()}

Digraph = nx.DiGraph()

for(u, v), w in edge_lookup.items():
    Digraph.add_edge(u, v, weight = w)

path = path_df["vertex"].tolist()
path_edges = list(zip(path[:-1], path[1:]))

pos = nx.kamada_kawai_layout(Digraph, weight=None)

COLOR = {
"bg":       "#0d1117",   # fundo
"node":     "#1f2937",   # nó normal
"edge":     "#374151",   # aresta normal
"path_node":"#00d4aa",   # nó no caminho
"path_edge":"#00d4aa",   # aresta no caminho
"current":  "#f97316",   # nó atual (animação)
"text":     "#e6edf3",   # labels
"muted":    "#6b7280",   # labels secundários
}

path_set = set(path)

node_colors = [
COLOR["path_node"] if n in path_set
else COLOR["node"]
for n in Digraph.nodes()
]

def draw_frame(frame):
    ax.clear()
    ax.set_facecolor(COLOR["bg"])

    visited = set(path[:frame + 1])
    visited_edges = set(path_edges[:frame])


    n_colors = [COLOR["current"] if n == path[frame]
                else COLOR["path_node"] if n in visited
                else COLOR["node"] for n in Digraph.nodes()]
    e_colors = [COLOR["path_edge"] if e in visited_edges
                else COLOR["edge"] for e in Digraph.edges()]
    e_widths = [2.5 if e in visited_edges else 0.8
                for e in Digraph.edges()]
    
    nx.draw(Digraph, pos, ax=ax, node_color=n_colors,
    edge_color=e_colors, width=e_widths,
    with_labels=True, font_color=COLOR["text"],
    node_size=700, font_size=9, arrows=True,
    arrowsize=15, connectionstyle="arc3,rad=0.1")


    path_labels = {e: edge_lookup[e] for e in visited_edges
                if e in edge_lookup}
    nx.draw_networkx_edge_labels(Digraph, pos, path_labels,
        font_color=COLOR["path_edge"], font_size=8, ax=ax)

    ax.set_title(f"vértice atual: {path[frame]}",
                color=COLOR["text"], fontsize=12)

ani = FuncAnimation(fig, draw_frame,
    frames=len(path), interval=900, repeat=True)

plt.tight_layout()
plt.show()



