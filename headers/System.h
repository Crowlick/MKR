#ifndef MIMAPR_SYSTEM_H
#define MIMAPR_SYSTEM_H

#include "Mesh.h"

class System
{
	Object& _obj;
	Mesh _mesh;
	double _a1;
	double _a2;
	double _step;
public:
	
System(Object& obj, double step = 10., double a1 = 1., double a2 = 1.): _obj(obj), _mesh(obj, step), _a1(a1), _a2(a2), _step(step) {}
	void DefineBounds();
	std::vector<std::vector<Node*>>& Nodes();
	std::vector<Node*>& LineX();
	std::vector<Node*>& LineY();
	double step() const;
	double a1() const;
	double a2() const;
};

#endif
