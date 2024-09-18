#include "pch.h"
#include "Vertex.h"
Vertex::Vertex(double x, double y, double z) : coordinate(nullptr)
{
    coordinate = new std::tuple<double, double, double>{ x, y, z };
}
Vertex::Vertex(const Vertex& obj) : coordinate(nullptr)
{
    coordinate = new std::tuple<double, double, double>{ std::get<0>(*obj.coordinate), std::get<1>(*obj.coordinate) ,
    std::get<2>(*obj.coordinate) };
}
Vertex& Vertex::operator=(const Vertex& obj)
{
    if (this == &obj) return *this;
    delete coordinate;
    coordinate = new std::tuple<double, double, double>{ std::get<0>(*obj.coordinate), std::get<1>(*obj.coordinate) ,
    std::get<2>(*obj.coordinate) };
    return *this;
}
Vertex::~Vertex()
{
    if (coordinate != nullptr) delete coordinate;
}