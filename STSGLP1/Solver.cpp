#include "solver.h"
#include <cmath>
#include <limits>

typedef std::vector<std::vector<float>> Vector2D_Float;
typedef std::vector<Vector2D_Float> Vector3D_Float;
typedef std::vector< Vector3D_Float> Vector4D_Float;

typedef IloArray<IloNumVarArray> NumVar2d;
typedef IloArray<NumVar2d> NumVar3d;
typedef IloArray<NumVar3d> NumVar4d;

// I'm adding an xample

void Solver::solve_and_print() const {
	const auto n = g.size();

	int sum_demands = 0;
	for (auto i = 0; i < n; i++) {
		for (auto j = 0; j < n; j++) {
			sum_demands += g.demand(i, j);
		}
	}

	Vector4D_Float q = std::vector < std::vector<std::vector < std::vector<float>>>>(n, std::vector<std::vector < std::vector<float>>>(n, std::vector< std::vector<float>>(n, std::vector<float>(n))));

	for (auto h = 0; h < n; h++) {
		for (auto k = 0; k < n; k++) {
			for (auto i = 0; i < n; i++) {
				for (auto j = 0; j < n; j++) {
					q[h][k][i][j] = g.cost(i, j) * (static_cast<float>(g.demand(h, k)) / static_cast<float>(sum_demands));
				}
			}
		}
	}
	IloEnv env;

	IloModel model(env);

	IloArray<IloNumVarArray> x(env, n);
	IloNumVarArray t(env, n);
	NumVar4d F(env, n);

	std::stringstream name;

	t[0] = IloNumVar(env, 1, 1, IloNumVar::Int, "t_0");


	for (auto i = 1u; i < n; ++i) {
		name << "t_" << i;
		t[i] = IloNumVar(env, 2, n, IloNumVar::Int, name.str().c_str());
		name.str("");
	}

	for (auto i = 0u; i < n; ++i) {
		x[i] = IloNumVarArray(env, n);
		for (auto j = 0u; j < n; ++j) {
			name << "x_" << i << "_" << j;
			x[i][j] = IloNumVar(env, 0, 1, IloNumVar::Bool, name.str().c_str());
			name.str("");
		}
	}

	for (auto h = 0u; h < n; ++h) {
		F[h] = NumVar3d (env, n);
		for (auto k = 0u; k < n; ++k) {
			F[h][k] = NumVar2d(env, n);
			for (auto i = 0u; i < n; ++i) {
				F[h][k][i] = IloNumVarArray(env, n);
				for (auto j = 0u; j < n; ++j) {
					name << "x_" <<h << "_" << k << "_" << i << "_" << j;
					F[h][k][i][j] = IloNumVar(env, 0, 1, IloNumVar::Bool, name.str().c_str());
					name.str(""); // Clean name
				}
			}
		}
	}

}

