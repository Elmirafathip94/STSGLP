#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph {
	const int nodes;
	std::vector<std::vector<float>> costs;
	std::vector<std::vector<int>> demands;
	void generate_graphcost(float square_side);
	void generate_graphdemand(int max_demand);

public:
	explicit Graph(int n);
	int size() const { return nodes; }
	
	float cost(int i, int j)const { return costs[i][j]; }
	int demand(int i, int j)const { return demands[i][j]; }
	

};

#endif
