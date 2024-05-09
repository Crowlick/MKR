#ifndef MIMAPR_SOLVER_H
#define MIMAPR_SOLVER_H

#include "System.h"

class Solver
{
	double _dt;
	std::vector<double> ThomasMethod(std::vector<std::vector<double>>&, std::vector<double>&) const;
	void SolveLine(System&, std::vector<Node*>&) const;
public:
	Solver(double dt = 1.): _dt(dt) {}
	void SolveExplicit(System&, double) const;
	void SolveImplicit(System&, double) const;
};

#endif
