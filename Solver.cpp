#include "headers/Solver.h"



void Solver::SolveImplicit(System& sys, double tstop) const
{
	std::ofstream ExplicitOut(_name_2);
	for (double t = 0.0; t < tstop; t += _dt)
	{
		for (int i = 1; i < sys.LineX().size() - 1; i++)
		{
			std::vector<Node*> temperature;
			Node* cur = sys.LineX()[i];
			while (cur)
			{
				if (cur->r() &&  cur->r()->X() - cur->X() > sys.step())
				{
					temperature.push_back(cur);
					SolveLine(sys, temperature);
					temperature.clear();
					cur = cur->r();
				}
				else
				{
					temperature.push_back(cur);
					cur = cur->r();		
				}
			}
			SolveLine(sys, temperature);
		}
		for (int i = 1; i < sys.LineY().size() - 1; i++)
		{
			std::vector<Node*> temperature;
			Node* cur = sys.LineY()[i];
			while (cur)
			{
				if (cur->u() &&  cur->u()->Y() - cur->Y() > sys.step())
				{
					temperature.push_back(cur);
					SolveLine(sys, temperature);
					temperature.clear();
					cur = cur->u();
				}
				else
				{
					temperature.push_back(cur);
					cur = cur->u();		
				}
			}
			SolveLine(sys, temperature);
		}
		for (auto line : sys.Nodes()) 
		{
			for (auto node : line)
				ExplicitOut << node->X() << ' ' << node->Y() << ' ' <<  node->T() <<'\n';
		}
		ExplicitOut << "\n\n";
	}
}


void Solver::SolveExplicit(System& sys, double tstop) const
{
	std::ofstream EmplicitOut(_name_1);
	for (double t = 0.; t < tstop; t += _dt)
	{
		for (auto line : sys.Nodes())
			for (auto node : line)
			{
				if (!node->IsBound())
				{
					double m1 = 1.;
					double m2 = 1.;
					/*if (node->r()->IsBound())
						m1 = (node->r()->X() - node->X()) / sys.step();
					if (node->l()->IsBound())
						m1 = (node->X() - node->l()->X()) / sys.step();
					if (node->u()->IsBound())
						m2 = (node->u()->Y() - node->Y()) / sys.step();
					if (node->d()->IsBound())
						m2 = (node->X() - node->d()->Y()) / sys.step();
					if (m1 <= 0.1)
						m1 = 0.1;
					if (m2 <= 0.1)
						m2 = 0.1;*/
					double tx = 2 * (m1 * node->r()->T() - (m1 + 1) * node->T() + node->l()->T()) / (m1 * (m1 + 1) * pow(sys.step(), 2));
					double ty = 2 * (m2 * node->u()->T() - (m2 + 1) * node->T() + node->d()->T()) / (m2 * (m2 + 1) *pow(sys.step(), 2));
					double t = _dt * sys.a1() * (tx + ty) + node->T();
					node->SetT(t);
				}
			}
		for (auto line : sys.Nodes()) 
		{
			for (auto node : line)
				EmplicitOut << node->X() << ' ' << node->Y() << ' ' <<  node->T() <<'\n';
		}
		EmplicitOut << "\n\n";
	}
}

void Solver::SolveLine(System& sys, std::vector<Node*>& n) const
{
	int size = n.size() - 2;
	double mu1 =  n.front()->Dist(n[1]) / sys.step();
	double mu2 = n.back()->Dist(n[n.size() - 2]) / sys.step();
	//mu1 = 1.;
	//mu2 = 1.;
	//if (mu2 <= 0.05)
	//	mu2 = .1;
	double val2 = -(2 * sys.a1()) / (pow(sys.step(), 2)) - 1 / _dt;
	double val1 = sys.a1() / (pow(sys.step(), 2));
	std::vector<std::vector<double>> next(size);
	std::vector<double> right(size);
	for (int i = 0; i < next.size(); i++)
		next[i].resize(3, 0.0);
	next[0][0] = -(2 * sys.a1()) / (mu1 * pow(sys.step(), 2)) - 1 / _dt;//val2;
	next[0][1] = (2 * sys.a1()) / ((mu1 + 1) * pow(sys.step(), 2));// val1;
	next.back()[1] = (2 * sys.a1()) / ((mu2 + 1) * pow(sys.step(), 2));// val1;
	next.back()[2] = -(2 * sys.a1()) / (mu2 * pow(sys.step(), 2)) - 1 / _dt;//val2;
	for (int i = 1; i < size - 1; i++)
	{
		next[i][0] = val1;
		next[i][1] = val2;
		next[i][2] = val1;
	}
	
	for (int i = 0; i < right.size(); i++)
		right[i] = -n[i+1]->T() / _dt;
	right.front() += -(2 * sys.a1() * n.front()->T()) / (mu1 * (mu1 + 1) * pow(sys.step(), 2));
	right.back() += -(2 * sys.a1() * n.back()->T()) / (mu2 * (mu2 + 1) * pow(sys.step(), 2));
	std::vector<double> tmps = ThomasMethod(next, right);
	for (int i = 0; i < tmps.size(); i++)
		n[i + 1]->SetT(tmps[i]);
}


std::vector<double> Solver::ThomasMethod(std::vector<std::vector<double>>& A, std::vector<double>& b) const
{
	int row = b.size() - 1;
	std::vector<double>alph(row);
	std::vector<double>bet(row);
	std::vector<double>x(b.size());
	alph[0] = - A[0][1] / A[0][0];
	bet[0] = b[0] / A[0][0];
	for (int i = 1; i < row; i++)
	{
		double a = A[i][0];
		double b1 = A[i][1];
		double c = A[i][2];
		alph[i] = -c / (a * alph[i - 1] + b1);
		bet[i] = (b[i] - a * bet[i - 1]) / (a * alph[i - 1] + b1); 
	}
	x.back() = (b.back() - A.back()[1]*bet.back()) / (A.back()[2] + A.back()[1]*alph.back());
	for (int i = row - 1; i > -1; i--)
		x[i] = alph[i] * x[i+1] + bet[i];
	return x;
}


