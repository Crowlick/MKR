#include <iostream>
#include <fstream>
#include <unistd.h>
#include "headers/Solver.h"

void visualize(std::ofstream &file, std::string filename, int time_end) {
	file << "set cbrange [" << 0 << ":" << 100 << "]" << std::endl;
	file << "set size ratio " << float(400) / 500 << "\nunset key\n" << "\nset palette defined (0 0 0 1, 0.25 0 1 1, 0.5 0 1 0, 0.75 1 1 0, 1 1 0 0)\n" << std::endl;            
	file << "do for [i=0:" << time_end - 1 << "]{" << std::endl;                 
	file << "plot '" << filename << "' u 1:2:3 index i w points pt 5 palette" << std::endl;
	file << "pause " << 0.0000001 << "}" << std::endl;
	file << "pause mouse";
}

int main()
{
	double w = 500.; // Geometry parameters
	double h = 400.;
	double S = 100.;
	double R1 = 150.;
	double R2 = 51.;
	double XS1 = 155.;
	double YS1 = 155.;
	double XS2 = 355.;
	double YS2 = 155.;
	
	int l = 1; //Bound conditions
	int t = 1;
	int r = 1;
	int b = 1;
	int r1 = 1;
	int r2 = 3;
	int s = 2;
	
	double step = 10.; // Mesh step
	double step2 = 5.; // Mesh step
	
	double time_step = 1.;	//Tipe step
	double time_end = 100.;
	
	std::map<std::string, double> base{{"a", w / 2}, {"b", h / 2}, {"h_x", 1/ w}, {"h_y", 1/ h}};
	std::map<std::string, double> sqr{{"a", XS2}, {"b", YS2}, {"h_x", 1 / S}, {"h_y", 1 / S}};
	std::map<std::string, double> circle{{"a", XS1}, {"b", YS1}, {"h_x", 1 / R2}, {"h_y", 1 / R2}};
	std::map<std::string, double> arc{{"a", w - R1}, {"b", h - R1}, {"h_x", 1 / R1}, {"h_y", 1 / R1}};
	
	Object obj;
	obj.Add_Form("Rectangle", sqr, true, s);
	//obj.Add_Form("Circle", circle, true, r2);
	obj.Add_Form("Arc", arc, true, r1);
	obj.Add_Form("Rectangle", base, false, 1);
	
	
	
	System explicit10(obj, step);
	explicit10.DefineBounds(l, t, r, b);
	
	System explicit5(obj, step2);
	explicit5.DefineBounds(l, t, r, b);
	
	System implicit10(obj, step);
	implicit10.DefineBounds(l, t, r, b);
	
	System implicit5(obj, step2);
	implicit5.DefineBounds(l, t, r, b);
	
	
	
	
	Solver slv10("explicit10.dat", "implicit10.dat", time_step);
	slv10.SolveExplicit(explicit10, time_end);
	slv10.SolveImplicit(implicit10, time_end);
	
	Solver slv5("explicit5.dat", "implicit5.dat", time_step);
	slv5.SolveExplicit(explicit5, time_end);
	slv5.SolveImplicit(implicit5, time_end);
	
	std::ofstream script("es10.plt");
	visualize(script, "explicit10.dat", time_end);
	script.close();
	system("gnuplot es10.plt");
	
	script.open("is10.plt");
	visualize(script, "implicit10.dat", time_end);
	script.close();
	system("gnuplot is10.plt");
	
	script.open("es5.plt");
	visualize(script, "explicit5.dat", time_end);
	script.close();
	system("gnuplot es5.plt");
	
	script.open("is5.plt");
	visualize(script, "implicit5.dat", time_end);
	script.close();
	system("gnuplot is5.plt");
	

	return 0;
}
