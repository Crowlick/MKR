#include "headers/Node.h"
#include <iostream>
double Node::X() const {return _x;}

double Node::Y() const {return _y;}

double Node::T() const 
{
	if (_btype == 1)
		return 100.;
		
	if (_btype == 2)
	{
		if (!_left)
			if (_right)
				return _right->T();
		if (!_right)
			if (_left)
				return _left->T();
		if (!_above)
			if (_below)
				return _below->T();
		if (!_below)
			if (_above)
				return _above->T();
	}
	
	if (_btype == 3)
	{
		//std::cout << _x << ' ' << _y << '\n';
		if (!_left)
			if (_right)
				return _right->T() / (1 + Dist(_right));
		if (!_right)
			if (_left)
				return _left->T() / (1 + Dist(_left));
		if (!_above)
			if (_below)
				return _below->T() / (1 + Dist(_below));
		if (!_below)
			if (_above)
				return _above->T() / (1 + Dist(_above));
	}
	
	return _t;
}

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

void Node::SetT(double t)
{
	_t = t;
}

bool Node::IsBound() {return _btype;}

void Node::SetB(int type) {_btype = type;}
