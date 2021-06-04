#include "Graph.h"
#include <cmath>
#include <random>
#include <iterator>
#include <algorithm>

Graph::Graph(int n) : nodes{ n } {
	generate_graphcost(100);
	generate_graphdemand(5);

}

void Graph::generate_graphcost(float square_side) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, square_side);

    std::vector<float> x_coord(nodes);
    std::vector<float> y_coord(nodes);

    std::generate(x_coord.begin(), x_coord.end(), [&]() { return dist(mt); });
    std::generate(y_coord.begin(), y_coord.end(), [&]() { return dist(mt); });
    
    costs = std::vector<std::vector<float> >(nodes, std::vector<float>(nodes));
    
    for (auto i = 0u; i < costs.size(); ++i) {
        costs[i][i] = 666 * square_side;
        for (auto j = i + 1; j < costs[i].size(); ++j) {
            const auto distance = std::sqrt(std::pow(x_coord[i] - x_coord[j], 2.0) + std::pow(y_coord[i] - y_coord[j], 2.0));
            costs[i][j] = distance;
            costs[j][i] = distance;
        }
    }
}

void Graph::generate_graphdemand(int max_demand)
{
    std::for_each(demands.begin(), demands.end(), [max_demand](std::vector<float> row)
        {
            std::generate(row.begin(), row.end(), [max_demand]() {return (rand() % (max_demand))+1; });
        }
    );

    for (int i = 0; i < nodes; i++)
    {
        demands[i][i] = 0;
    }
}
