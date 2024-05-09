#include "headers/System.h"


void System::DefineBounds()
{
	for (auto start : _mesh.LineX())
	{
		Node* cur = start;
		while (cur)
		{
			/*if (!cur->l() || !cur->r() || 
				cur->Dist(cur->r()) > _step || cur->Dist(cur->l()) > _step ||
				cur->Dist(cur->u()) > _step || cur->Dist(cur->d()) > _step)
				cur->SetT(100);*/
			if (!cur->l() || !cur->r())
				cur->SetT(100);
			if (cur->l() && cur->Dist(cur->l()) > _step)
				cur->SetT(100);
			if (cur->r() && cur->Dist(cur->r()) > _step)
				cur->SetT(100);
			cur = cur->r();
		}
	}
	for (auto start : _mesh.LineY())
	{
		Node* cur = start;
		while (cur)
		{
			if (!cur->u() || !cur->d())
				cur->SetT(100);
			if (cur->u() && cur->Dist(cur->u()) > _step)
				cur->SetT(100);
			if (cur->d() && cur->Dist(cur->d()) > _step)
				cur->SetT(100);
			cur = cur->u();
		}
	}
}

std::vector<std::vector<Node*>>& System::Nodes() {return _mesh.Nodes();}
std::vector<Node*>& System::LineX() {return _mesh.LineX();}
std::vector<Node*>& System::LineY()  {return _mesh.LineY();}

double System::step() const {return _step;}
double System::a1() const {return _a1;}
double System::a2() const {return _a2;}
