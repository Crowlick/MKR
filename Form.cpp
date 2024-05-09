//
// Created by vka19 on 05.05.2024.
//

#include "headers/Form.h"

size_t Form::counter_ = 0;

double Form::Function(double, double) {
    return 0;
}

std::pair<double, double> Form::Deriative(double, double) {
    return {0, 0};
}

std::pair<double, double> Form::size()
{
	return {0, 0};
}

bool Form::Inhere(double, double) {
    return false;
}

std::pair<double, double> Form::missX(double)
{
	return {0, 0};
}

std::pair<double, double> Form::missY(double)
{
	return {0, 0};
}

Form::Form() {
    id_ = counter_++;
    excluded_ = false;
}

size_t Form::Get_ID() const {
    return id_;
}

bool Form::Excluded() const {
    return excluded_;
}

bool Form::operator==(size_t id) const {
    return id_ == id;
}
