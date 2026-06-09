#pragma once

#include "FloydWarshall.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Dijkstra//Algoritmoo de busca minima
{
    
    public:
    
    vector<vector<Edge>> AdjacencyList;
    vector<vector<Edge>> ReverseAdjacencyList;
    DataSetRead dataset;

    Dijkstra()
    {
        AdjacencyList.resize(dataset.amountVertex + 1);
        ReverseAdjacencyList.resize(dataset.amountVertex + 1);

        for(const auto& e : dataset.edges)
        {
            AdjacencyList[e.from].push_back(e);

            ReverseAdjacencyList[e.to].push_back({
            e.to,
            e.from,
            e.weight
            });
        }

        //baseAmbulance = floydwarshall.baseAmbulanceDefiner();

        ofstream file("edges.csv");

        file << "from,to,weight\n";

        for(const auto& e : dataset.edges)
            file << e.from << "," << e.to << "," << e.weight << "\n";
        file.close();
        
    };

    int bestRouteOfBaseToAccident(int base, int accident) //USando Dijkstra calcula a melhor rota da base até o acidente
    {
        long long visitados = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> dijkstra;

        vector<int> dist(dataset.amountVertex + 1, INT_MAX);
        vector<int> prev(dataset.amountVertex + 1, -1);

        dist[base] = 0;
        dijkstra.push({0, base});

        while(!dijkstra.empty())
        {
            visitados++;
            auto[d, u] = dijkstra.top();
            dijkstra.pop();

            if(d > dist[u]){continue;}

            if(u == accident)
            {
                //cout << visitados << " Quantidade de passos\n";

                vector<int> path;
                for(int v = accident; v != -1; v = prev[v])
                    path.push_back(v);
                reverse(path.begin(), path.end());

                ofstream file("PathOfEdges.csv");
                file << "step,vertex\n";
                for(int i = 0; i < (int)path.size(); i++)
                    file << i << "," << path[i] << "\n";
                file.close();


                return dist[u];
            }
            
            for(const auto& edge : AdjacencyList[u])
            {
                
                if(edge.weight < 0){ continue;}

                if(dist[u] + edge.weight < dist[edge.to])
                {
                    dist[edge.to] = dist[u] + edge.weight;
                    prev[edge.to] = u;
                    dijkstra.push({dist[edge.to], edge.to});
                }

            }
        }
        return dist[accident];
    };


    int averageTimetoRescue()
    {
        
        int bestVertexTime = INT_MAX;
        int bestVertex = 0;


        for(int i = 1 ; i <= dataset.amountVertex; i++)
        {
            int averageTime = 0;
            int time = 0;
            for(int j = 1; j <= dataset.amountVertex; j++)
            {
                time += bestRouteOfBaseToAccident(i, j);
            }
            averageTime = time / dataset.amountVertex;
            if(bestVertexTime > averageTime)
            {
                bestVertexTime = averageTime;
                bestVertex = i;
            }
        }

        return bestVertex;

    }

};
