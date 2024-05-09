#ifndef MIMAPR_NODE_H
#define MIMAPR_NODE_H

#include <cmath>


class Node
{
	double _x;
	double _y;
	double _t;
	Node* _left;
	Node* _right;
	Node* _above;
	Node* _below;
public:
	Node(double x = 0., double y = 0., double t = 0.): _x(x), _y(y), _t(t), _left(nullptr), _right(nullptr), _above(nullptr), _below(nullptr) {}
	double T() const;
	double X() const;
	double Y() const;
	double Dist(const Node*) const;
	void LinkX(Node*, Node*);
	void LinkY(Node*, Node*);
	Node*& l();
	Node*& r();
	Node*& u();
	Node*& d();
	void SetT(double);
	//friend Mesh;
};

#endif
