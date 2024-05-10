#include "headers/System.h"


void System::DefineBounds(int l, int t, int r, int b)
{
	Node* cur = _mesh.LineX().front();
	while (cur)
	{
		cur->SetB(b);
		cur = cur->r();
	}
	cur = _mesh.LineX().back();
	while (cur)
	{
		cur->SetB(t);
		cur = cur->r();
	}
	cur = _mesh.LineY().front();
	while (cur)
	{
		cur->SetB(l);
		cur = cur->u();
	}
	cur = _mesh.LineY().back();
	while (cur->u())
	{
		cur->SetB(r);
		cur = cur->u();
	}
	/*for (auto line : _mesh.Nodes())
	{
		for (auto node : line)
		{
			if (!node->l() || !node->r() || !node->u() || !node->d())
			{
				//node->SetT(100);
				node->SetB(1);
			}
		}
	}*/
}

std::vector<std::vector<Node*>>& System::Nodes() {return _mesh.Nodes();}
std::vector<Node*>& System::LineX() {return _mesh.LineX();}
std::vector<Node*>& System::LineY()  {return _mesh.LineY();}

double System::step() const {return _step;}
double System::a1() const {return _a1;}
double System::a2() const {return _a2;}
