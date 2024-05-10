#ifndef MIMAPR_OBJECT_H
#define MIMAPR_OBJECT_H

#include "Primitives.h"
#include <vector>

class Object {
private:
    std::vector<Form*> forms_;
    double _w;
    double _h;
    void Updsize();
public:
    Object();
    ~Object();

    double Inhere(double, double);
    double Width() const;
    double Height() const;
    bool Add_Form(const std::string&, std::map<std::string, double>&, bool, int);
   

    bool Delete_Form(size_t);
    std::pair<double, double> Filly(double, double);
    std::pair<double, double> Fillx(double, double);

    std::vector<size_t> Get_IDs();
    Form* Who(double, double);
};


#endif //MIMAPR_OBJECT_H
