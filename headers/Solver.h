#ifndef MIMAPR_SOLVER_H
#define MIMAPR_SOLVER_H

#include "System.h"
#include <string>
#include <fstream>


class Solver
{
	double _dt;
	std::vector<double> ThomasMethod(std::vector<std::vector<double>>&, std::vector<double>&) const;
	void SolveLine(System&, std::vector<Node*>&) const;
	std::string _name_1;
	std::string _name_2;
	
public:
	Solver(std::string name_1, std::string name_2, double dt = 1.): _dt(dt), _name_1(name_1), _name_2(name_2) {}
	void SolveExplicit(System&, double) const;
	void SolveImplicit(System&, double) const;
};

#endif
