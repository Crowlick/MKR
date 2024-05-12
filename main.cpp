#include <iostream>
#include <fstream>
#include <unistd.h>
#include "headers/Solver.h"

void visualize(std::ofstream &file, std::string filename, int time_end) {
	file << "set cbrange [" << 0 << ":" << 100 << "]" << std::endl;
	file << "set size ratio " << float(400) / 500 << "\nunset key\n" << "\nset palette defined (0 0 0 1, 0.25 0 1 1, 0.5 0 1 0, 0.75 1 1 0, 1 1 0 0)\n" << std::endl;            
	file << "do for [i=0:" << time_end - 1 << ":25]{" << std::endl;                 
	file << "plot '" << filename << "' u 1:2:3 index i w points pt 5 palette" << std::endl;
	file << "pause " << 0.000000001 << "}" << std::endl;
	file << "pause mouse";
}

int main()
{
	double w = 500.; // Geometry parameters
	double h = 400.;
	double S = 100.;
	double R1 = 150.;
	double R2 = 60.;
	double XS1 = 155.;
	double YS1 = 155.;
	double XS2 = 155.;
	double YS2 = 155.;
	
	int l = 1; //Bound conditions
	int t = 3;
	int r = 1;
	int b = 3;
	int r1 = 3;
	int r2 = 1;
	int s = 1;
	
	double step = 10.; // Mesh step
	double step2 = 5.; // Mesh step
	
	double time_step = 1.;	//Time step
	double time_end = 100.;
	
	double C = 1.; // Material props
	
	std::map<std::string, double> base{{"a", w / 2}, {"b", h / 2}, {"h_x", 1/ w}, {"h_y", 1/ h}};
	std::map<std::string, double> sqr{{"a", XS2}, {"b", YS2}, {"h_x", 1 / S}, {"h_y", 1 / S}};
	std::map<std::string, double> circle{{"a", XS1}, {"b", YS1}, {"h_x", 1 / R2}, {"h_y", 1 / R2}};
	std::map<std::string, double> arc{{"a", w - R1}, {"b", h - R1}, {"h_x", 1 / R1}, {"h_y", 1 / R1}};
	
	Object obj;
//	obj.Add_Form("Rectangle", sqr, true, s);
	obj.Add_Form("Circle", circle, true, r1);
	obj.Add_Form("Arc", arc, true, r2);
	obj.Add_Form("Rectangle", base, false, 1);
	
	
	
	System explicit10(obj, step, C);
	explicit10.DefineBounds(l, t, r, b);
	
	System explicit5(obj, step2, C);
	explicit5.DefineBounds(l, t, r, b);
	
	System implicit10(obj, step, C);
	implicit10.DefineBounds(l, t, r, b);
	
	System implicit5(obj, step2, C);
	implicit5.DefineBounds(l, t, r, b);
	
	
	
	
	Solver slv10("edumma_lab_2024_rk6_64b_kochetov_lab1_res1.dat", "edumma_lab_2024_rk6_64b_kochetov_lab1_res2.dat", time_step);
	slv10.SolveExplicit(explicit10, time_end);
	slv10.SolveImplicit(implicit10, time_end);
	
	Solver slv5("edumma_lab_2024_rk6_64b_kochetov_lab1_res3.dat", "edumma_lab_2024_rk6_64b_kochetov_lab1_res4.dat", time_step);
	slv5.SolveExplicit(explicit5, time_end);
	slv5.SolveImplicit(implicit5, time_end);
	
	std::ofstream script("es10.plt");
	visualize(script, "edumma_lab_2024_rk6_64b_kochetov_lab1_res1.dat", time_end);
	script.close();
	system("gnuplot es10.plt");
	
	script.open("is10.plt");
	visualize(script, "edumma_lab_2024_rk6_64b_kochetov_lab1_res2.dat", time_end);
	script.close();
	system("gnuplot is10.plt");
	
	script.open("es5.plt");
	visualize(script, "edumma_lab_2024_rk6_64b_kochetov_lab1_res3.dat", time_end);
	script.close();
	system("gnuplot es5.plt");
	
	script.open("is5.plt");
	visualize(script, "edumma_lab_2024_rk6_64b_kochetov_lab1_res4.dat", time_end);
	script.close();
	system("gnuplot is5.plt");
	

	return 0;
}
