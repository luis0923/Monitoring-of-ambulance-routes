import subprocess
import sys
import os

sys.path.append(os.path.join(os.path.dirname(__file__), "..", "PlotPython"))
from Visualizer import Graph_Representation


def run_algorithm(algorithm: str, destiny: str):

    base = os.path.dirname(os.path.abspath(__file__))
    search_dir = os.path.normpath(os.path.join(base, "..", "SearchAlgorithms"))

    #eU removi o executáveis e manti só o executável.
    
    executavel = os.path.join(base, "..", "Main", "programa.exe")
    

    result = subprocess.run(
        [executavel, algorithm, str(destiny)],
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
#Ta mal feito kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk mas to com sono ent tá otimo
    flag = True
    while(flag != "0"):
        print("=== HealthTech - Sistema de Monitoramento de descolamento de ambulância ===\n")

        print("Algoritmos disponíveis:")
        print(" 1. Dijkstra\n", "2. Bellman-ford \n", "3. floyd-warshall\n", "4: SAÍDA")

        algorithm = input("\nDigite o número correspondente ao algoritmo que deseje interagir, ou apenas encerre isso :) ").strip().lower()
        

        mapa = {
            "1": "dijkstra",
            "2": "bellmanford",
            "3": "floydwarshall",
            "4": "sair"
        }

        algorithm = mapa.get(algorithm, algorithm)

        if algorithm not in ["dijkstra", "bellmanford", "floydwarshall", "sair"]:
            print("Algoritmo inválido, por favor tente novamente!\n")

        elif algorithm in ["dijkstra", "bellmanford"]:
        
            destiny = input("\nDigite o destino do acidente: ")

            run_algorithm(algorithm, destiny)
            Graph_Representation()
        elif algorithm == "floydwarshall":
            run_algorithm(algorithm, 0)
        elif algorithm == "sair":
            print("ACABOUUUUUUUUUUUUUUUUUUUUUU!")
            sys.exit(1)

        
        