#pragma once

#include "FloydWarshall.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class BellmanFord 
{
public:
    vector<vector<Edge>> AdjacencyList;
    DataSetRead dataset;

    BellmanFord() 
    {
        AdjacencyList.resize(dataset.amountVertex + 1);

        // Preenche a lista de adjacência a partir do dataset
        for(const auto& e : dataset.edges)
        {
            AdjacencyList[e.from].push_back(e);
        }

        // Exporta o arquivo edges.csv assim como no seu Dijkstra
        ofstream file("edges.csv");
        file << "from,to,weight\n";
        for(const auto& e : dataset.edges)
            file << e.from << "," << e.to << "," << e.weight << "\n";
        file.close();
    }

    int bestRouteOfBaseToAccident(int base, int accident) 
    {
        int V = dataset.amountVertex;
        // Usamos INF (1e9) para evitar problemas de overflow de INT_MAX ao somar pesos
        vector<int> dist(V + 1, 1e9);
        vector<int> prev(V + 1, -1);

        dist[base] = 0;

        // Relaxamento de todas as arestas V - 1 vezes
        for (int i = 1; i <= V - 1; ++i) 
        {
            bool uportunityToStop = true; // Otimização: se nada mudar, podemos parar antes
            
            for (int u = 1; u <= V; ++u) 
            {
                if (dist[u] == 1e9) continue;

                for (const auto& edge : AdjacencyList[u]) 
                {
                    if (dist[u] + edge.weight < dist[edge.to]) 
                    {
                        dist[edge.to] = dist[u] + edge.weight;
                        prev[edge.to] = u;
                        uportunityToStop = false;
                    }
                }
            }
            if (uportunityToStop) break; 
        }

        // Verificação de ciclos de peso negativo
        for (int u = 1; u <= V; ++u) 
        {
            if (dist[u] == 1e9) continue;
            for (const auto& edge : AdjacencyList[u]) 
            {
                if (dist[u] + edge.weight < dist[edge.to]) 
                {
                    cout << "Atenção: O grafo contém um ciclo de peso negativo!\n";
                    return -1;
                }
            }
        }

        // Se o destino for inalcançável
        if (dist[accident] == 1e9) 
        {
            cout << "Não há caminho entre a base e o acidente.\n";
            return -1;
        }

        // Reconstrói o caminho percorrido
        vector<int> path;
        for (int v = accident; v != -1; v = prev[v]) 
        {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        // Salva o caminho no PathOfEdges.csv para o Visualizer.py funcionar perfeitamente
        ofstream file("PathOfEdges.csv");
        file << "step,vertex\n";
        for (int i = 0; i < (int)path.size(); i++) 
        {
            file << i << "," << path[i] << "\n";
        }
        file.close();


        return dist[accident];
    }
};
