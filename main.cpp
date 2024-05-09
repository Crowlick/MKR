#include <iostream>
#include <fstream>
//#include "headers/Object.h"
#include "headers/System.h"



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
	//Form* a = nullptr;
	//Rectangle bases(x, y, hx, hy, 0);
	//a = &bases;
	//Rectangle sqr1(width / 2, height / 2, width / 2, height / 2, 1);
	Object obj;
	obj.Add_Form("Rectangle", sqr, true);
	obj.Add_Form("Circle", circle, true);
	obj.Add_Form("Arc", arc, true);
	obj.Add_Form("Rectangle", base, false);
	double step = 1.;
	std::ofstream file("data.dat");
/*	for (double i = 0; i <= obj.Width(); i += step)
	{
		for (double j = 0; j <= obj.Height(); j += step)
		{
			if (obj.Inhere(i, j))
			{
				file << i << ' ' << j << '\n';
			}
			else 
			{
				file << obj.Fillx(i, j).first << ' ' << j << '\n';
				file << obj.Fillx(i, j).second << ' ' << j << '\n';
				file << i << ' ' << obj.Filly(i, j).first << '\n';
				file << i << ' ' << obj.Filly(i, j).second << '\n';
			}
		}
	}*/
	
	System sys(obj, step);
	//Mesh mesh(obj, step);
	sys.DefineBounds();
	for (auto line : sys.nodes())
		for (auto node : line)
			file << node->X() << ' ' << node->Y() << ' ' <<  node->T() <<'\n';
	/*for (auto start : mesh.lineX())
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
