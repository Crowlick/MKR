#include "headers/Node.h"

double Node::X() const {return _x;}

double Node::Y() const {return _y;}

double Node::T() const {return _t;}

double Node::Dist(const Node* to) const
{
	return std::sqrt(pow(X() - to->X(), 2) + pow(Y() - to->Y(), 2));
}

Node*& Node::l() {return _left;}
Node*& Node::r() {return _right;}
Node*& Node::u() {return _above;}
Node*& Node::d() {return _below;}


void Node::LinkX(Node* l, Node* r)
{
	_left = l;
	_right = r;
}

void Node::LinkY(Node* d, Node* u)
{
	_below = d;
	_above = u;
}

void Node::SetT(double t) {_t = t;}
