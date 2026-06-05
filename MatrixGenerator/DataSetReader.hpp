#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>


struct Edge //Criado para representar a estrutura de uma aresta; 39 arestas LEMBRAR
{
    int from;
    int to;
    int weight;
};

struct Vertex //Criado para representar a estrutura de uma aresta; 20 verties lembrar
{
    int amoutVertex;
};

class DataSetRead //Leitor de DataSet, vai ler e armazenar os dados das arestas
{
public:
    
    std::vector<Edge> edges;
    int amountVertex = 0;


    DataSetRead()
    {
        
        Edge edge;
        std::ifstream file("dataset.txt");
        if(!file.is_open())
        {
            std::cout<< "Falha ao abrir o dataset\n";
            return;
        }
        while(file >> edge.from >> edge.to >> edge.weight)
        {
            edges.push_back(edge);
            amountVertex = std::max(amountVertex, std::max(edge.from, edge.to));
        };

    };

};