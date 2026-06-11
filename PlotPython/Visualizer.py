import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import networkx as nx
import os
import pygame


class Graph_Representation:
        
    def __init__(self):  
        #Especial
        pygame.mixer.init()
        sound_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "somdeambulancia.wav")
        if os.path.exists(sound_path):
            pygame.mixer.music.load(sound_path)
            pygame.mixer.music.play()
        else:
            print(f"Caminho do som não encontrado em: {sound_path}")
        #
        plt.style.use("dark_background")
        self.fig, self.ax = plt.subplots(figsize=(12, 8))
        self.fig.patch.set_facecolor("#0d1117")
        self.ax.set_facecolor("#0d1117")
        for spine in self.ax.spines.values():
            spine.set_visible(False)

        base = os.path.dirname(os.path.abspath(__file__))
        csv_path = os.path.join(base, "..", "SearchAlgorithms", "PathOfEdges.csv")
        edges_path = os.path.join(base, "..", "SearchAlgorithms", "edges.csv")

        path_df = pd.read_csv(csv_path)
        self.path = path_df["vertex"].tolist()

        edges_df = pd.read_csv(edges_path)
        self.edge_lookup = {(int(r["from"]), int(r["to"])): int(r["weight"]) for _, r in edges_df.iterrows()}

        self.Digraph = nx.DiGraph()
        for (u, v), w in self.edge_lookup.items():
            self.Digraph.add_edge(u, v, weight=w)

        self.path_edges = list(zip(self.path[:-1], self.path[1:]))
        self.pos = nx.kamada_kawai_layout(self.Digraph, weight=None)

        self.COLOR = {
            "bg":        "#0d1117",
            "node":      "#1f2937",
            "edge":      "#374151",
            "path_node": "#00d4aa",
            "path_edge": "#00d4aa",
            "current":   "#f97316",
            "text":      "#e6edf3",
            "muted":     "#6b7280",
        }

        self.ani = FuncAnimation(self.fig, self.draw_frame,
            frames=len(self.path), interval=900, repeat=True)

        plt.tight_layout()
        plt.show()

    def draw_frame(self, frame):
        self.ax.clear()
        self.ax.set_facecolor(self.COLOR["bg"])

        visited = set(self.path[:frame + 1])
        visited_edges = set(self.path_edges[:frame])

        n_colors = [self.COLOR["current"] if n == self.path[frame]
                    else self.COLOR["path_node"] if n in visited
                    else self.COLOR["node"] for n in self.Digraph.nodes()]
        e_colors = [self.COLOR["path_edge"] if e in visited_edges
                    else self.COLOR["edge"] for e in self.Digraph.edges()]
        e_widths = [2.5 if e in visited_edges else 0.8
                    for e in self.Digraph.edges()]

        nx.draw(self.Digraph, self.pos, ax=self.ax, node_color=n_colors,
            edge_color=e_colors, width=e_widths,
            with_labels=True, font_color=self.COLOR["text"],
            node_size=700, font_size=9, arrows=True,
            arrowsize=15, connectionstyle="arc3,rad=0.1")

        path_labels = {e: self.edge_lookup[e] for e in visited_edges
                       if e in self.edge_lookup}
        nx.draw_networkx_edge_labels(self.Digraph, self.pos, path_labels,
            font_color=self.COLOR["path_edge"], font_size=8, ax=self.ax)

        self.ax.set_title(f"vértice atual: {self.path[frame]}",
                    color=self.COLOR["text"], fontsize=12)
