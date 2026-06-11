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
            AdjacencyList[e.from].push_back(e); //Definimos como estrutura de armazenamento a AdjacencyList, pelo desempenho

            ReverseAdjacencyList[e.to].push_back({
            e.to,
            e.from,
            e.weight
            });
        }

        ofstream file("edges.csv");

        file << "from,to,weight\n";

        for(const auto& e : dataset.edges)
            file << e.from << "," << e.to << "," << e.weight << "\n";
        file.close();
        
    };


    //Dijkstra
    int bestRouteOfBaseToAccident(int base, int accident) //Utilizamos de Dijkstra para calcular a melhor rota da base até o acidente
    {
        //Removi a variavel visitados, pq nãoestou compparando com o bidirecional mais
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue; //Troquei o nome antigo, tinha deixado dijkstra mas fica meio confuso


        //A prioriryQueue ela é organizada assim: (Tipo de elemento, o alocador interno, comparador) nesa ordem
        //Ah e tbm ela é max_heap por padrão, então a gente utiliza o greater para que ela vire min_heap, retornando o menor elemento


        vector<int> dist(dataset.amountVertex + 1, INT_MAX);//Vetor que armazena as distancias
        vector<int> prev(dataset.amountVertex + 1, -1);

        dist[base] = 0;
        queue.push({0, base}); //Adiciona a base como elemento da PQ, além disso, a distãncia inicial é estabelecida como 0, justamente o valor de ir a si mesmo.

        while(!queue.empty())
        {

            auto[d, u] = queue.top();//Para rodar no teu pc, tem que ta com mys, no MINGW tu troca para o .firs e .second
                                    //Basicamente ele pega o pair do vetor e utiliza como base de comparação para a a distancia/tempo

            queue.pop(); //deleta o elemento que está alocado na queue

            if(d > dist[u]){continue;} //Comppara se o peso atual é maior que o peso que foi inserido anteriormente,se sim, pode continuar

            if(u == accident) //Se u == acident, significa que chegamos no alvo
    {                       // Para salvar em .csv
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
            
            for(const auto& edge : AdjacencyList[u]) //Captura os elementos da struct Edges que estão presentes na posição u da adjacencyList
            {                                          //Ou seja, ele pega os Edges.to que estão na posição do vetor da aresta atual
                
                if(edge.weight < 0){ continue;} //Tratamento para arestas negativas

                if(dist[u] + edge.weight < dist[edge.to]) //Se a distancia atual + o peso da aresta que está sendo analisada for menor que a distancia do aresta atual
                {
                    dist[edge.to] = dist[u] + edge.weight; //então a distancia atual vai ser igual a soma das arestas
                    prev[edge.to] = u; //Salva o caminho da aresta para o visualizer
                    queue.push({dist[edge.to], edge.to}); //adiciona o valor atual do peso da aresta e  melhor aresta
                }

            }
        }
        return dist[accident];
    };


    int averageTimetoRescue() //Calcula o tempo médio de resgate partindo de cada vertice, para definir o melhor ponto para localizar a base
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
