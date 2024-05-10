#include <iostream>
#include <fstream>
//#include "headers/Object.h"
#include "headers/Solver.h"



int main()
{
	double w = 500.;
	double h = 400.;
	double S = 100.;
	double R1 = 150.;
	double R2 = 50.;
	double XS1 = 155.;
	double YS1 = 155.;
	double XS2 = 355.;
	double YS2 = 255.;
	
	std::map<std::string, double> base{{"a", w / 2}, {"b", h / 2}, {"h_x", 1/ w}, {"h_y", 1/ h}};
	std::map<std::string, double> sqr{{"a", XS2}, {"b", YS2}, {"h_x", 1 / S}, {"h_y", 1 / S}};
	std::map<std::string, double> circle{{"a", XS1}, {"b", YS1}, {"h_x", 1 / R2}, {"h_y", 1 / R2}};
	std::map<std::string, double> arc{{"a", w - R1}, {"b", h - R1}, {"h_x", 1 / R1}, {"h_y", 1 / R1}};
	
	Object obj;
	obj.Add_Form("Rectangle", sqr, true);
	obj.Add_Form("Circle", circle, true);
	obj.Add_Form("Arc", arc, true);
	obj.Add_Form("Rectangle", base, false);
	
	double step = 5.;
	std::ofstream file("data.dat");
	
	System sys(obj, step);
	sys.DefineBounds();
	/*for (auto line : sys.Nodes())
		for (auto node : line)
			file << node->X() << ' ' << node->Y() << ' ' <<  node->T() <<'\n';
	/*for (auto start : sys.lineY())
	{
		Node* cur = start;
		while (cur)
		{
			file << cur->X() << ' ' << cur->Y() << ' ' << cur->T() << '\n';
			cur = cur->u();
		}
	}*/
//	file.close();
//	system("python3 vis.py");*/
	Solver s(1.);
	s.SolveExplicit(sys, 1000.);
	for (auto line : sys.Nodes())
		for (auto node : line)
			file << node->X() << ' ' << node->Y() << ' ' <<  node->T() <<'\n';
	/*for (auto start : sys.LineX())
	{
		Node* cur = start;
		while (cur)
		{
			file << cur->X() << ' ' << cur->Y() << ' ' << cur->T() << '\n';
			cur = cur->r();
		}
	}*/
	file.close();
	system("python3 vis.py");
	return 0;
}
