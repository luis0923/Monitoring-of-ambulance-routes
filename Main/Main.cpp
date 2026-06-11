#include "../SearchAlgorithms/Dijkstra.hpp"
#include "../SearchAlgorithms/BellmanFord.hpp"
#include "../SearchAlgorithms/FloydWarshall.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

FloydWarshall floydwarshall;
Dijkstra dijkstra;
BellmanFord bellmanford;
const int baseDijkstra = dijkstra.averageTimetoRescue();
const int baseBellmanFord = floydwarshall.baseAmbulanceDefiner();
using namespace std;

int main(int argc, char* argv[])
{


    if(argc < 3)
    {
        cerr << "Uso: algoritmo <dijkstra|bellmanford|floydwarshall> <destino>\n";
        return 1;
    }
    string algorithm = argv[1];
    int destiny = stoi(argv[2]);


    vector<int> path;


    if (algorithm == "dijkstra" || algorithm == "1")
    {
        

        cout << "Base escolhida: " << baseDijkstra << "\n"; 
        cout << "Destino: " << destiny <<  "\n"; 

        int dist = dijkstra.bestRouteOfBaseToAccident(baseDijkstra, destiny);

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
        
        int dist = bellmanford.bestRouteOfBaseToAccident(baseBellmanFord, destiny);
        if(dist == -1)
        {
            cerr << "Erro no BellmaanFord. \n";
        }
        else
        {
        cout << "A base do BellmanFord EH: " << baseBellmanFord << "\n";
        cout << "A menor distancia EH: " << dist << "\n"; 
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


    cout <<"\nAlgoritmo " << algorithm << " concluido.\n";
    return 0;
}