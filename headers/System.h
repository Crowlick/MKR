#ifndef MIMAPR_SYSTEM_H
#define MIMAPR_SYSTEM_H

#include "Mesh.h"

class System
{
	Object& _obj;
	Mesh _mesh;
	double _a1;
	double _a2;
	double _dt;
	double _step;
public:
	
System(Object& obj, double step = 10., double dt = 1., double a1 = 1., double a2 = 1.): _obj(obj), _mesh(obj, step), _a1(a1), _a2(a2), _step(step), _dt(dt) {}
	void DefineBounds();
	const std::vector<std::vector<Node*>>& nodes() const;
};

#endif
