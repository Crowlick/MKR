#include <iostream>
#include <fstream>
#include "headers/Solver.h"

void visualize(std::ofstream &file, std::string filename) {
	file << "set cbrange [" << 0 << ":" << 100 << "]" << std::endl;
	file << "set size ratio " << float(400) / 500 << std::endl;            
	file << "do for [i=0:" << 1000 << ":25]{" << std::endl;                 
	file << "plot '" << filename << "' u 1:2:3 index i w points pt 5 palette" << std::endl;
	file << "pause " << 0.0000001 << "}" << std::endl;
	file << "pause -1";
}

int main()
{
	double w = 500.;
	double h = 400.;
	double S = 150.;
	double R1 = 150.;
	double R2 = 101.;
	double XS1 = 155.;
	double YS1 = 155.;
	double XS2 = 355.;
	double YS2 = 255.;
	
	std::map<std::string, double> base{{"a", w / 2}, {"b", h / 2}, {"h_x", 1/ w}, {"h_y", 1/ h}};
	std::map<std::string, double> sqr{{"a", XS2}, {"b", YS2}, {"h_x", 1 / S}, {"h_y", 1 / S}};
	std::map<std::string, double> circle{{"a", XS1}, {"b", YS1}, {"h_x", 1 / R2}, {"h_y", 1 / R2}};
	std::map<std::string, double> arc{{"a", w - R1}, {"b", h - R1}, {"h_x", 1 / R1}, {"h_y", 1 / R1}};
	
	Object obj;
	obj.Add_Form("Rectangle", sqr, true, 2);
	obj.Add_Form("Circle", circle, true, 3);
	obj.Add_Form("Arc", arc, true, 1);
	obj.Add_Form("Rectangle", base, false, 1);
	
	double step = 5.;
	std::ofstream file("data.dat");
	std::ofstream script("script.plt");
	
	System sys(obj, step);
	sys.DefineBounds(1, 1, 1, 1);
	
	Solver s("explicit.dat", "implicit.dat", 1.);
	s.SolveImplicit(sys, 1000.);
	for (auto line : sys.Nodes())
		for (auto node : line)
			file << node->X() << ' ' << node->Y() << ' ' << node->T() << '\n';
	file.close();
	system("python3 vis.py");
	visualize(script, "implicit.dat");
	system("gnuplot script.plt");
	return 0;
}
