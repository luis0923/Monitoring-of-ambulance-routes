#include "../SearchAlgorithms/Dijkstra.hpp"
#include "../SearchAlgorithms/BellmanFord.hpp"
#include "../SearchAlgorithms/FloydWarshall.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

FloydWarshall floydwarshall;
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cerr << "Uso: algoritmo <dijkstra|bellmanford|floydwarshall> <origem> <destino>\n";
        return 1;
    }
    string algorithm = argv[1];
    //int origem = atoi(argv[2]);
   //int destino = atoi(argv[3]);

    vector<int> path;


    if (algorithm == "dijkstra" || algorithm == "1")
    {
        Dijkstra dijkstra;
        int base = dijkstra.averageTimetoRescue();
        cout << "Base escolhida: " << base << "\n"; 
        cout << "Destino: 10\n"; 

        int dist = dijkstra.bestRouteOfBaseToAccident(dijkstra.averageTimetoRescue(), 10);

        if(dist == INT_MAX)
        {
            cerr << "Destino inalcançaável" << "\n";
        }
        else
        {
            cout << "A menor distancia EH: " << dist << "\n";
        }
    }
    else if (algorithm == "bellmanford" || algorithm == "2")
    {
        BellmanFord bellmanford;
        int dist = bellmanford.bestRouteOfBaseToAccident(floydwarshall.baseAmbulanceDefiner(), 19);
        if(dist == -1)
        {
            cerr << "Erro no BellmaanFord. \n";
        }
        else
        {
        cout << "A menor distancia é: " << dist << "\n"; 
        }
    }
    else if (algorithm == "floydwarshall" || algorithm == "3")
    {
        
        floydwarshall.ambulanceObservatory();

        cout << "\n";

        floydwarshall.matrixGenerator();
        floydwarshall.floydWarshall();

        floydwarshall.printMatrix();

    }
    else
    {
        cerr << "Algoritmo desconhecido: " << algorithm << "\n";
        return 1;
    }


    cout <<"\nAlgoritmo " << algorithm << " concluído.\n";
    return 0;
}