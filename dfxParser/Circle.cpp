#include "pch.h"
#include "Circle.h"

Circle::Circle(double xC, double yC, double zC, double radius) : Figure()
{
    this->radius = new double(radius);
    center = new std::tuple <double, double, double>{ xC, yC, zC };
}
Circle::Circle(const Circle& obj) : Figure(obj)
{
    center = new std::tuple  <double, double, double>{ std::get<0>(*obj.center), std::get<1>(*obj.center), std::get<2>(*obj.center) };
    this->radius = new double(*obj.radius);
}
Circle& Circle::operator=(const Circle& obj)
{
    if (this == &obj) return *this;
    delete center;
    center = new std::tuple <double, double, double>{ std::get<0>(*obj.center), std::get<1>(*obj.center) ,
    std::get<2>(*obj.center) };
    *radius = *obj.radius;
    return *this;
}
Circle::~Circle()
{
    delete center;
    delete radius;
}