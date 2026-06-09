import subprocess
import sys
import os

sys.path.append(os.path.join(os.path.dirname(__file__), "..", "PlotPython"))
from Visualizer import Graph_Representation


def run_algorithm(algorithm: str):

    base = os.path.dirname(os.path.abspath(__file__))
    search_dir = os.path.normpath(os.path.join(base, "..", "SearchAlgorithms"))

    executaveis = {
    "dijkstra":      os.path.join(base, "..", "SearchAlgorithms", "Dijkstra.exe"),
    "bellmanford":   os.path.join(base, "..", "SearchAlgorithms", "BellmanFord.exe"),
    "floydwarshall": os.path.join(base, "..", "SearchAlgorithms", "FloydWarshall.exe"),
    }

    executavel = os.path.join(base, "..", "Main", "programa.exe")
    
    executable = executaveis[algorithm]

    result = subprocess.run(
        [executavel, algorithm],# str(origem), str(destino)],
        capture_output=True,
        text=True,
        cwd=search_dir
    )

    if result.returncode != 0:
        print(f"Houve erro no C++:\n{result.stderr}")
        sys.exit(1)

    print(result.stdout)

    path_csv = os.path.join(search_dir, "PathOfEdges.csv")
    if os.path.exists(path_csv):
        print(f"CSV encontrado: {path_csv}")
    else:
        print(f"CSV NÃO encontrado em: {path_csv}")
        sys.exit(1)


if __name__ == "__main__":

    algorithm = True
    while(algorithm != "0"):
        print("=== HealthTech - Sistema de Roteamento ===\n")

        print("Algoritmos disponíveis:")
        print("  1. dijkstra")
        print("  2. bellmanford")
        print("  3. floydwarshall")
        algorithm = input("\nEscolha o algoritmo: ").strip().lower()

        mapa = {
            "1": "dijkstra",
            "2": "bellmanford",
            "3": "floydwarshall"
        }

        algorithm = mapa.get(algorithm, algorithm)

        if algorithm not in ["dijkstra", "bellmanford", "floydwarshall"]:
            print("Algoritmo inválido.")
            sys.exit(1)

        elif algorithm in ["dijkstra", "bellmanford", "1", "2"]:
            Graph_Representation()

        run_algorithm(algorithm)
        