#include "headers/Mesh.h"
#include <iostream>

Mesh::Mesh(Object& obj, double step): _obj(obj), _step(step)
{
	
	for (double y = 0; y <= _obj.Height(); y += _step)
	{
		_mesh.push_back(std::vector<Node*>());
		for (double x = 0; x <= _obj.Width(); x += _step)
		{
			_mesh.back().push_back(new Node(x, y));
		}
	}
	LinkX();
	LinkY();
//	ShowLinks();
	Adapt();
//	ShowLinks();
}

void Mesh::LinkX()
{
	
	for (int i = 0; i < _mesh.size(); i++)
	{
		_mesh[i][0]->LinkX(nullptr, _mesh[i][1]);
		for (int j = 1; j < _mesh[i].size() - 1; j++)
			_mesh[i][j]->LinkX(_mesh[i][j - 1], _mesh[i][j + 1]);
		_mesh[i].back()->LinkX(_mesh[i][_mesh[i].size() - 2], nullptr);
	}
	for (int i = 0; i < _mesh.size(); i++)
		_hlines.push_back(_mesh[i][0]);
}


void Mesh::LinkY()
{
	for (int j = 0; j < _mesh[0].size(); j++)
	{
		_mesh[0][j]->LinkY(nullptr, _mesh[1][j]);
		for (int i = 1; i < _mesh.size() - 1; i++)
			_mesh[i][j]->LinkY(_mesh[i - 1][j], _mesh[i + 1][j]);
		_mesh[_mesh.size() - 1][j]->LinkY(_mesh[_mesh.size() - 2][j], nullptr);
	}
	for (int i = 0; i < _mesh[0].size(); i++)
		_vlines.push_back(_mesh[0][i]);
}


void Mesh::Adapt()
{

	for (int i = 0; i < _mesh.size(); i++)
	{
		int s = _mesh[i].size();
		for (int j = 0; j < s; j++)
		{
			if (!_obj.Inhere(_mesh[i][j]->X(), _mesh[i][j]->Y()))
			{
				Delnode(i, j);
				j--;
				s--;
			}
		}
	}
}



void Mesh::ShowLinks()
{
	for (auto line : _mesh)
	{
		for (auto node : line)
		{

			if (node->d())
				std::cout << "|  ";
		}
		std::cout << '\n';
		for (auto node : line)
		{
			if (node->l())
			{
				std::cout << '-';
			}
			std::cout << 'N';
			if (node->r())
			{
				std::cout << '-';
			}
			else
			{
				std::cout << '\n';
			}	
		}
		for (auto node : line)
		{
			if (node->u())
				std::cout << "|";
			std::cout << "  ";

		}
		std::cout << '\n';
	}
}

void Mesh::Delnode(int i, int j)
{
	Node* node = _mesh[i][j];
	double bndX1 = _obj.Fillx(node->X(), node->Y()).first;
	double bndX2 = _obj.Fillx(node->X(), node->Y()).second;
	double bndY1 = _obj.Filly(node->X(), node->Y()).first;
	double bndY2 = _obj.Filly(node->X(), node->Y()).second;
	int btype = _obj.Who(node->X(), node->Y())->GetB();
	if (node->l())
	{
		if (node->l()->X() != bndX2 && node->l()->X() != bndX1)
		{
			if (bndX1 != bndX2)
			{
				Node* left = new Node(bndX2, node->Y(), btype);
				Node* right = new Node(bndX1, node->Y(), btype);
				node->l()->r() = left;
				if (node->r())
					node->r()->l() = right;
				left->LinkX(node->l(), right);
				right->LinkX(left, node->r());
				node->l() = right;
				_mesh[i].push_back(left);
				_mesh[i].push_back(right);
			}
			else
			{
				Node* left = new Node(bndX2, node->Y(), btype);
				node->l()->r() = left;
				if (node->r())
					node->r()->l() = left;
				left->LinkX(node->l(), node->r());
				node->l() = left;
				_mesh[i].push_back(left);
			}
		}
		else
			node->l()->r() = node->r();
	}
	if (node->r())
	{
		node->r()->l() = node->l();
	}
	if (node->d())
	{
		if (node->d()->Y() != bndY2 && node->d()->Y() != bndY1)
		{
			if (bndY2 != bndY1)
			{
				Node* down = new Node(node->X(), bndY2, btype);
				Node* up = new Node(node->X(), bndY1, btype);
				node->d()->u() = down;
				if (node->u())
					node->u()->d() = up;
				down->LinkY(node->d(), up);
				up->LinkY(down, node->u());
				node->d() = up;
				_mesh[i].push_back(down);
				_mesh[i].push_back(up);
			}
			else
			{
				Node* down = new Node(node->X(), bndY2, btype);
				node->d()->u() = down;
				if (node->u())
					node->u()->d() = down;
				down->LinkY(node->d(), node->u());
				node->d() = down;
				_mesh[i].push_back(down);
			}
		}
		else
			node->d()->u() = node->u();
	}
	if (node->u())
	{
		node->u()->d() = node->d();
	}
	_mesh[i].erase(_mesh[i].begin() + j);
	delete node;
}


std::vector<std::vector<Node*>>& Mesh::Nodes() {return _mesh;}

std::vector<Node*>& Mesh::LineX()  {return _hlines;}
std::vector<Node*>& Mesh::LineY()  {return _vlines;}

Mesh::~Mesh()
{
	for (auto line : _mesh)
		for (auto node : line)
			delete node;
}


