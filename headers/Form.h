#ifndef MIMAPR_FORM_H
#define MIMAPR_FORM_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>

class Form {
protected:
    static size_t counter_;
    size_t id_;
    bool excluded_;

public:
    Form();

    virtual double Function(double, double);

    virtual std::pair<double, double> Deriative(double, double);

    virtual bool Inhere(double, double);
    
    virtual std::pair<double, double> missX(double); 
    virtual std::pair<double, double> missY(double); 
    virtual std::pair<double, double> size();
    [[nodiscard]] size_t Get_ID() const;

    [[nodiscard]] bool Excluded() const;

    bool operator==(size_t) const;
};



#endif //MIMAPR_FORM_H
