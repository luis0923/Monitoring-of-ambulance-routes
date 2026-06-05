import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import networkx as nx
import os

class save:

    base = os.path.dirname(os.path.abspath(__file__))
    csv_path = os.path.join(base, "..", "SearchAlgorithms", "PathOfEdges.csv")
    edges_path = os.path.join(base, "..", "SearchAlgorithms", "edges.csv")

    path_df = pd.read_csv(csv_path)
    path = path_df["vertex"].tolist()

    edges_df = pd.read_csv(edges_path)
    edge_lookup = {(int(r["from"]), int(r["to"])): int(r["weight"]) for _, r in edges_df.iterrows()}

    G = nx.DiGraph()
    path_edges = list(zip(path[:-1], path[1:]))
    for u, v in path_edges:
        w = edge_lookup.get((u, v), 0)
        G.add_edge(u, v, weight=w)

    pos = nx.kamada_kawai_layout(G)
    fig, ax = plt.subplots(figsize=(10, 7))

    def update(frame):
        ax.clear()

        # Nós e arestas já visitados até o frame atual
        visited_nodes = path[:frame + 1]
        visited_edges = path_edges[:frame]

        # Cores dos nós
        node_colors = ["red" if n in visited_nodes else "#cccccc" for n in G.nodes()]

        # Cores das arestas
        edge_colors = ["red" if e in visited_edges else "#eeeeee" for e in G.edges()]

        nx.draw(G, pos, ax=ax,
                with_labels=True,
                node_color=node_colors,
                edge_color=edge_colors,
                node_size=700,
                font_color="white",
                font_weight="bold",
                arrows=True,
                arrowsize=20,
                connectionstyle="arc3,rad=0.1")

        # Destaca o nó atual com borda
        nx.draw_networkx_nodes(G, pos, ax=ax,
                            nodelist=[path[frame]],
                            node_color="orange",
                            node_size=900)
        nx.draw_networkx_labels(G, pos, ax=ax,
                                labels={path[frame]: path[frame]},
                                font_color="white",
                                font_weight="bold")

        labels = nx.get_edge_attributes(G, "weight")
        nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=9, ax=ax)

        ax.set_title(f"Passo {frame + 1}/{len(path)} — Vértice atual: {path[frame]}")

    ani = animation.FuncAnimation(
        fig,
        update,
        frames=len(path),
        interval=800,    # milissegundos entre cada passo
        repeat=True
    )

    plt.show()