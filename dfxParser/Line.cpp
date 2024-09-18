#include "pch.h"
#include "Line.h"


Line::Line(double x1, double y1, double z1, double x2, double y2, double z2) : Figure()
{
    points = new std::pair <Point, Point>{ Point(x1, y1, z1), Point(x2, y2, z2) };
}
Line::Line(const Line& obj) : Figure(obj)
{
    points = new std::pair <Point, Point>{ obj.points->first, obj.points->second };
}
Line& Line::operator=(const Line& obj)
{
    if (this == &obj) return *this;
    points->first = obj.points->first;
    points->second = obj.points->second;
    return *this;
}
Line::~Line()
{
    delete points;
}
