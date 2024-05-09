#include "headers/System.h"


void System::DefineBounds()
{
	for (auto start : _mesh.lineX())
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
	for (auto start : _mesh.lineY())
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

const std::vector<std::vector<Node*>>& System::nodes() const {return _mesh.nodes();}
const std::vector<Node*>& System::lineX() const {return _mesh.lineX();}
const std::vector<Node*>& System::lineY() const {return _mesh.lineY();}
