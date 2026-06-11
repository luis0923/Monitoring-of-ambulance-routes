#pragma once

#include "../MatrixGenerator/DataSetReader.hpp"
#include <climits>
#include <random>
#include <chrono>
#include <iomanip>


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
                    pondMatrix[i][j] = INT_MAX;
                }
            }
        }
        for(const auto& e: dataSet.edges)
        {
            pondMatrix[e.from][e.to] = e.weight;
        }
    };
    void floydWarshall()//Define a matriz ponderada, em cada loop ele tenta extrair o melhor caminho para ij, passando por k
    {
        //complexidade de N3
        for(int k = 1; k <= dataSet.amountVertex; k++)
        {
            for(int i = 1; i<=dataSet.amountVertex; i++)
            {
                for(int j = 1; j<=dataSet.amountVertex; j++)
                {   //ele compara para ver se a soma da linha coluna k + linha k coluna i, é menor que o valor da linha i coluna j;
                    if(pondMatrix[i][k] != INT_MAX && pondMatrix[k][j] != INT_MAX && pondMatrix[i][k] + pondMatrix[k][j] < pondMatrix[i][j]) //Só soma se os caminhos existirem
                    {
                        pondMatrix[i][j] = pondMatrix[i][k] + pondMatrix[k][j];
                    }
                }
            }
        }
    };

    void printMatrix()
    {
        const int COL_WIDTH = 6;

        
        std::cout << std::string(COL_WIDTH, ' ');
        for(int j = 1; j <= dataSet.amountVertex; j++)
            std::cout << std::setw(COL_WIDTH) << j;
        std::cout << "\n";

        std::cout << std::string(COL_WIDTH * (dataSet.amountVertex + 1), '-') << "\n";

        for(int i = 1; i <= dataSet.amountVertex; i++)
        {
            std::cout << std::setw(COL_WIDTH - 1) << i << "|";

            for(int j = 1; j <= dataSet.amountVertex; j++)
            {
                if(pondMatrix[i][j] == INT_MAX)
                    std::cout << std::setw(COL_WIDTH) << "INF";
                else
                    std::cout << std::setw(COL_WIDTH) << pondMatrix[i][j];
            }
            std::cout << "\n";
        }
    }
    int baseAmbulanceDefiner() //Inutil no Dijkstra, talvez sirva para o Bellman-Ford
    {
        //Acho que coloquei como parametro do Bellman, se tu quiser pode remover e colocar na mão a partida
        long long routeSum = INT_MAX;
        int bestVertex = 0;
        
        for(int i = 1; i <= dataSet.amountVertex; i++)
        {
            long long atualRoute = 0;
            for(int j = 1; j <= dataSet.amountVertex; j++)
            {
                if(pondMatrix[i][j] != INT_MAX)
                {
                    atualRoute += pondMatrix[i][j];
                }
               

            }
            if(i == 1 || routeSum > atualRoute)
            {
                routeSum = atualRoute;
                bestVertex = i;
            }
        }
        return bestVertex;
    }
    
    void ambulanceObservatory()// vai printar quais das ambulancias que estão circulando, estão mais próximas do acidente, de umma forma aleatória
    {
        
        std::uniform_int_distribution<int> dist(1, 20);
        std::vector<int> ambulanceFleet;
        int accident = randomAccident();

        for(int i = 0; i < 5; i++)
        {
            ambulanceFleet.push_back(randomAccident()); //Valores aleatorios de 1 a 20 (quantidade máxima de vertices)
        }

        int BestDistance = INT_MAX;
        int nearestAmbulance = 0;
        int distanceActual = 0;
        for(int k = 0; k < ambulanceFleet.size(); k++)
        {
            distanceActual = pondMatrix[ambulanceFleet[k]][accident];
            if(BestDistance > distanceActual && distanceActual >= 0 && distanceActual != INT_MAX) //Evite que haja temos infinitos e neegativos
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
