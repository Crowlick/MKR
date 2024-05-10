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
	double w = 500.; // Geometry parameters
	double h = 400.;
	double S = 150.;
	double R1 = 150.;
	double R2 = 101.;
	double XS1 = 155.;
	double YS1 = 155.;
	double XS2 = 355.;
	double YS2 = 255.;
	
	int l = 1; //Bound conditions
	int t = 3;
	int r = 1;
	int b = 3;
	int r1 = 1;
	int r2 = 3;
	int s = 3;
	
	double step = 5.; // Mesh step
	
	std::map<std::string, double> base{{"a", w / 2}, {"b", h / 2}, {"h_x", 1/ w}, {"h_y", 1/ h}};
	std::map<std::string, double> sqr{{"a", XS2}, {"b", YS2}, {"h_x", 1 / S}, {"h_y", 1 / S}};
	std::map<std::string, double> circle{{"a", XS1}, {"b", YS1}, {"h_x", 1 / R2}, {"h_y", 1 / R2}};
	std::map<std::string, double> arc{{"a", w - R1}, {"b", h - R1}, {"h_x", 1 / R1}, {"h_y", 1 / R1}};
	
	Object obj;
	//obj.Add_Form("Rectangle", sqr, true, s);
	obj.Add_Form("Circle", circle, true, r2);
	obj.Add_Form("Arc", arc, true, r1);
	obj.Add_Form("Rectangle", base, false, 1);
	
	std::ofstream script("script.plt");
	
	System sys(obj, step);
	sys.DefineBounds(l, t, r, b);
	
	Solver slv("explicit.dat", "implicit.dat", 1.);
	slv.SolveImplicit(sys, 1000.);

	visualize(script, "implicit.dat");
	system("gnuplot script.plt");
	return 0;
}
