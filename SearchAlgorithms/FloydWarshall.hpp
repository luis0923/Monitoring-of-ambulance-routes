#pragma once

#include "../MatrixGenerator/DataSetReader.hpp"
#include <climits>
#include <random>
#include <chrono>

static const int INF = 1e9;

class FloydWarshall
{
public:
    DataSetRead dataSet;
    int pondMatrix[21][21];

    int randomAccident()
    {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 20);
        return dist(rng);
    }
 
    void matrixGenerator()
    {
        for(int i = 0; i <= dataSet.amountVertex; i++)
        {
            for(int j = 0; j <= dataSet.amountVertex; j++)
            {
                if(i == j)
                {
                    pondMatrix[i][j] = 0;
                }
                else
                {
                    pondMatrix[i][j] = INF;
                }
            }
        }
        for(const auto& e: dataSet.edges)
        {
            pondMatrix[e.from][e.to] = e.weight;
        }
    };
    void floydWarshall()//Define a matriz ponderada
    {
        for(int k = 1; k <= dataSet.amountVertex; k++)
        {
            for(int i = 1; i<=dataSet.amountVertex; i++)
            {
                for(int j = 1; j<=dataSet.amountVertex; j++)
                {
                    if(pondMatrix[i][k] != INF && pondMatrix[k][j] != INF && pondMatrix[i][k] + pondMatrix[k][j] < pondMatrix[i][j])
                    {
                        pondMatrix[i][j] = pondMatrix[i][k] + pondMatrix[k][j];
                    }
                }
            }
        }
    };

    void printMatrix()
    {
        for(int i = 1; i <= dataSet.amountVertex; i++)
        {
            for(int j = 1; j <= dataSet.amountVertex; j++)
            {
                if(pondMatrix[i][j] == INF)
                {
                    std::cout << "INF ";
                }
                else
                {
                    std::cout << pondMatrix[i][j] << " ";
                }
            }

            std::cout << "\n";
        }
    };

    int baseAmbulanceDefiner() //Inutil no Dijkstra, talvez sirva para o Bellman-Ford
    {
        long long routeSum = LLONG_MAX;
        int bestVertex = 0;
        
        for(int i = 1; i <= dataSet.amountVertex; i++)
        {
            long long atualRoute = 0;
            for(int j = 1; j <= dataSet.amountVertex; j++)
            {
                atualRoute += pondMatrix[i][j];

            }
            if(i == 1 || routeSum > atualRoute)
            {
                routeSum = atualRoute;
                bestVertex = i;
            }
        }
        return bestVertex;
    }
    
    void ambulanceObservatory()// vai printar quais das ambulancias que estão circulando, estão mais próximas do acidente
    {
        
        std::uniform_int_distribution<int> dist(1, 20);
        std::vector<int> ambulanceFleet;
        int accident = randomAccident();

        for(int i = 0; i < 5; i++)
        {
            ambulanceFleet.push_back(randomAccident()); //Valores aleatorios de 1 a 20 (quantidade máxima de vertices)
        }

        int BestDistance = INF;
        int nearestAmbulance = 0;
        int distanceActual = 0;
        for(int k = 0; k < ambulanceFleet.size(); k++)
        {
            distanceActual = pondMatrix[ambulanceFleet[k]][accident];
            if(BestDistance > distanceActual)
            {
                BestDistance = distanceActual;
                nearestAmbulance = ambulanceFleet[k];
                
            }
        }
        std::cout << "Nossas ambulancias estao localizadas: ";
        for(int j = 0; j < ambulanceFleet.size(); j++)
        {
            std::cout << ambulanceFleet[j] << " ";
        }
        std::cout << "\n"<< "A ambulancia mais proxima do acidente localizado no vertice " << accident <<" eh: " << nearestAmbulance << "\n";

    }
};
