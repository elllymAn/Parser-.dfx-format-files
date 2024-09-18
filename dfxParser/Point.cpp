#include "pch.h"
#include "Point.h"

Point::Point(double x, double y, double z) : Figure()
{
    coordinate = new std::tuple<double, double, double>{ x, y, z };
}
Point::Point(const Point& obj) : Figure(obj)
{
    coordinate = new std::tuple<double, double, double>{ std::get<0>(*obj.coordinate), std::get<1>(*obj.coordinate) ,
    std::get<2>(*obj.coordinate) };
}
Point& Point::operator=(const Point& obj)
{
    if (this == &obj) return *this;
    delete coordinate;
    coordinate = new std::tuple<double, double, double>{ std::get<0>(*obj.coordinate), std::get<1>(*obj.coordinate) ,
    std::get<2>(*obj.coordinate) };
    return *this;
}
Point::~Point()
{
    delete coordinate;
}
