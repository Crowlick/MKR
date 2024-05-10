#include "headers/Object.h"

Object::Object(): _w(0), _h(0) {}

double Object::Inhere(double x, double y) 
{
    for (auto form: forms_) 
    {
        if (form->Excluded()) 
        {
            if (form->Inhere(x, y)) 
            {
                return false;
            }
        } 
        else 
        {
            if (form->Inhere(x, y)) 
            {
                return true;
            }
        }
    }
    return false;
}

void Object::Updsize()
{
	for (auto form : forms_)
	{
		_w = std::max(_w, form->size().first);
		_h = std::max(_h, form->size().second);
	}
}

bool Object::Add_Form(const std::string &name, std::map<std::string, double> &args, bool excluded, int btype) {
    if (name == "Rectangle") {
        forms_.push_back(new Rectangle(args["a"], args["b"], args["h_x"], args["h_y"], excluded, btype));
        Updsize();
        return true;
    } else if (name == "Circle") {
        forms_.push_back(new Circle(args["a"], args["b"], args["h_x"], args["h_y"], excluded, btype));
        Updsize();
        return true;
    } else if (name == "Arc") {
        forms_.push_back(new Arc(args["a"], args["b"], args["h_x"], args["h_y"], excluded, btype));
        Updsize();
        return true;
    }
    return false;
}



std::pair<double, double> Object::Fillx(double x, double y)
{
	for (auto form: forms_) 
	{
		if (form->Inhere(x, y)) 
		{
			return form->missX(y);
		} 
	}
	return {0, 0};
}

std::pair<double, double> Object::Filly(double x, double y)
{
	for (auto form: forms_) 
	{
		if (form->Inhere(x, y)) 
		{
			return form->missY(x);
		} 
	}
	return {0, 0};
}

double Object::Width() const
{
	return _w;
}

double Object::Height() const
{
	return _h;
}

bool Object::Delete_Form(size_t id) {
  /*  auto iterator = std::find(forms_.begin(), forms_.end(), id);
    if (iterator != forms_.end()) {
        forms_.erase(iterator);
        return true;
    }
    std::cout << "Don't have element with this ID\n";*/
    return false;
}

std::vector<size_t> Object::Get_IDs() {
    std::vector<size_t> ids;
    ids.reserve(forms_.size());
    for (auto form: forms_) {
        ids.push_back(form->Get_ID());
    }
    return ids;
}

Form* Object::Who(double x, double y)
{
	for (auto form: forms_) 
	{
		if (form->Inhere(x, y)) 
		{
			return form;
		}

	}
	return forms_.back();
}
Object::~Object() 
{
	for (auto form : forms_)
		delete form;
}
