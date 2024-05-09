#ifndef MIMAPR_PRIMITIVES_H
#define MIMAPR_PRIMITIVES_H

#include "Form.h"

class Rectangle : public Form {
private:
    double a_;
    double b_;
    double h_x_;
    double h_y_;
public:
    Rectangle(double, double, double, double, bool);

    double Function(double, double) override;

    std::pair<double, double> Deriative(double, double) override;

    bool Inhere(double, double) override;
    std::pair<double, double> missX(double) override;
    std::pair<double, double> missY(double) override;
    std::pair<double, double> size() override;
};
class Circle : public Form {
private:
    double a_;
    double b_;
    double h_x_;
    double h_y_;
public:
    Circle(double, double, double, double, bool);

    double Function(double, double) override;

    std::pair<double, double> Deriative(double, double) override;

    bool Inhere(double, double) override;
    std::pair<double, double> missX(double) override;
    std::pair<double, double> missY(double) override;
    std::pair<double, double> size() override;
};

class Arc : public Form {
private:
    double a_;
    double b_;
    double h_x_;
    double h_y_;
public:
    Arc(double, double, double, double, bool);

    double Function(double, double) override;

    std::pair<double, double> Deriative(double, double) override;
    std::pair<double, double> missX(double) override;
    std::pair<double, double> missY(double) override;
    std::pair<double, double> size() override;
    bool Inhere(double, double) override;
};

#endif //MIMAPR_PRIMITIVES_H
