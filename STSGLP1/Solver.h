#ifndef SOLVER_H
#define SOLVER_H

#include "graph.h"
#include <iostream>

#ifndef IL_STD
#define IL_STD
#endif
#include <cstring>
#include <ilcplex/ilocplex.h>
ILOSTLBEGIN

class Solver {

    const Graph& g;

public:   
    explicit Solver(const Graph& g) : g{ g } {}

    void solve_and_print() const;
};
};


#endif
