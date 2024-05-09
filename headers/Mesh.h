#ifndef MIMAPR_MESH_H
#define MIMAPR_MESH_H

#include <vector>
#include "Object.h"
#include "Node.h"

class Mesh
{
	std::vector<std::vector<Node*>> _mesh;
	std::vector<Node*> _hlines;
	std::vector<Node*> _vlines;
	Object& _obj;
	double _step;
	void LinkX();
	void LinkY();
	void Delnode(int, int);
	void Adapt();
	
public:
	Mesh(Object&, double);
	void ShowLinks();
	const std::vector<std::vector<Node*>>& nodes() const;
	const std::vector<Node*>& lineX() const;
	const std::vector<Node*>& lineY() const;
	~Mesh();
};

#endif
