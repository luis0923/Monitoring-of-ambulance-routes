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
        std::mt19937 rng(random_device{}());
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
    void floydWarshall()
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
    
    void ambulanceObservatory()
    {
        
        uniform_int_distribution<int> dist(1, 20);
        int accident = randomAccident();

        vector<int> ambulanceFleet;
        for(int i = 0; i < 5; i++)
        {
            ambulanceFleet.push_back(randomAccident());
        }

        int bestAmbulance = -1;
        int shortestDistance = INF;

        for(int i = 0; i < (int)ambulanceFleet.size(); i++)
        {
            int distance = pondMatrix[ambulanceFleet[i]][accident];
            if(distance < shortestDistance)
            {
                shortestDistance = distance;
                bestAmbulance = i;
            }
        }
        cout << "Acidente no setor: " << accident << "\n";
        cout << "Ambulâncias nos setores: ";
        for(int s : ambulanceFleet) cout << s << " ";
        cout << "\n";
        cout << "Ambulância " << bestAmbulance + 1 << " despachada do setor " << ambulanceFleet[bestAmbulance] << " | Distância: " << shortestDistance << "\n";
    }
};
