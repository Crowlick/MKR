#include "headers/Primitives.h"

Rectangle::Rectangle(double a, double b, double h_x, double h_y, bool excluded, int btype) : a_(a), b_(b), h_x_(h_x), h_y_(h_y) {
    excluded_ = excluded;
    _boundtype = btype;
}

std::pair<double, double> Rectangle::missX(double y)
{
	return {0.5 / h_x_ + a_, -0.5 / h_x_ + a_};
}
std::pair<double, double> Rectangle::missY(double x)
{
	return {0.5 / h_y_ + b_, -0.5 / h_y_ + b_};
}

std::pair<double, double> Rectangle::size()
{
	return {1 / h_x_, 1 / h_y_};
}

double Rectangle::Function(double x, double y) {
    return std::max(h_x_ * std::abs(x - a_), h_y_ * std::abs(y - b_));
}

std::pair<double, double> Rectangle::Deriative(double x, double y) {
    return {(h_x_ / 2) * ((x - a_) / std::abs(x - a_)), (h_y_ / 2) * ((y - b_) / std::abs(y - b_))};
}

bool Rectangle::Inhere(double x, double y) {
    return Function(x, y) <= 0.5;
}




Circle::Circle(double a, double b, double h_x, double h_y, bool excluded, int btype) : a_(a), b_(b), h_x_(h_x), h_y_(h_y) {
    excluded_ = excluded;
    _boundtype = btype;
}

std::pair<double, double> Circle::missY(double x)
{
	return {std::sqrt(1 - pow((h_x_ * (x - a_)), 2))/h_y_ + b_, -std::sqrt(1 - pow((h_x_ * (x - a_)), 2))/h_y_ + b_};
}
std::pair<double, double> Circle::missX(double y)
{
	return {std::sqrt(1 - pow((h_y_ * (y - b_)), 2))/h_x_ + a_, -std::sqrt(1 - pow((h_y_ * (y - b_)), 2))/h_x_ + a_};
}


double Circle::Function(double x, double y) {
    return pow(h_x_ * (x - a_), 2) + pow(h_y_ * (y - b_), 2);
}

std::pair<double, double> Circle::Deriative(double x, double y) {
    return {2 * h_x_ * (x - a_), 2 * h_y_ * (y - b_)};
}

std::pair<double, double> Circle::size()
{
	return {1 / h_x_, 1 / h_y_};
}

bool Circle::Inhere(double x, double y) {
    return Function(x, y) <= 1;
}


Arc::Arc(double a, double b, double h_x, double h_y, bool excluded, int btype): a_(a), b_(b), h_x_(h_x), h_y_(h_y) {
    excluded_ = excluded;
    _boundtype = btype;
}

std::pair<double, double> Arc::missY(double x)
{
	return {std::sqrt(1 - pow((h_x_ * (x - a_)), 2))/h_y_ + b_, std::sqrt(1 - pow((h_x_ * (x - a_)), 2))/h_y_ + b_};
}
std::pair<double, double> Arc::missX(double y)
{
	return {std::sqrt(1 - pow((h_y_ * (y - b_)), 2))/h_x_ + a_, std::sqrt(1 - pow((h_y_ * (y - b_)), 2))/h_x_ + a_};
}

double Arc::Function(double x, double y) {
    if (x >= a_ && y >= b_) {
        return pow(h_x_ * (x - a_), 2) + pow(h_y_ * (y - b_), 2);
    }
  /*  if (x < a_) {
        std::cout << "x < a\n";
    }
    if (y < b_) {
        std::cout << "y < b\n";
    }*/
    return -1.0;
}

std::pair<double, double> Arc::Deriative(double x, double y) {
    if (x >= a_ && y >= b_) {
        return {2 * h_x_ * (x - a_), 2 * h_y_ * (y - b_)};
    }
    if (x < a_) {
        std::cout << "x < a\n";
    }
    if (y < b_) {
        std::cout << "y < b\n";
    }
    return {-1.0, -1.0};
}


std::pair<double, double> Arc::size()
{
	return {1 / h_x_, 1 / h_y_};
}

bool Arc::Inhere(double x, double y) {
    return Function(x, y) >= 1;
}
