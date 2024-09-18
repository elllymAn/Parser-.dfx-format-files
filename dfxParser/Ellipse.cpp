#include "pch.h"
#include "Ellipse.h"
EllipseForm::EllipseForm(double xC, double yC, double zC, double xE, double yE, double zE, double ratio, double begin,
    double end) : Figure()
{
    mainAxe = new double(sqrt(pow(xC - xE, 2) + pow(yC - yE, 2) + pow(zC - zE, 2)));
    minorAxe = new double(*mainAxe * ratio);
    center = new std::tuple <double, double, double>{ xC, yC, zC };
    painting = new std::pair <double, double>{ begin, end };
}
EllipseForm::EllipseForm(const EllipseForm& obj) : Figure(obj)
{
    center = new std::tuple <double, double, double>{ std::get<0>(*obj.center), std::get<1>(*obj.center), std::get<2>(*obj.center) };
    mainAxe = new double(*obj.mainAxe);
    this->minorAxe = new double(*obj.minorAxe);
    painting = new std::pair <double, double>{ obj.painting->first, obj.painting->second };
}

EllipseForm::~EllipseForm()
{
    delete center;
    delete mainAxe;
    delete painting;
    delete minorAxe;
}
EllipseForm& EllipseForm::operator=(const EllipseForm& obj)
{
    if (this == &obj) return *this;
    delete center;
    delete painting;
    center = new std::tuple<double, double, double>{ std::get<0>(*obj.center), std::get<1>(*obj.center) ,
    std::get<2>(*obj.center) };
    *mainAxe = *obj.mainAxe;
    *minorAxe = *obj.minorAxe;
    painting = new std::pair <double, double>{ obj.painting->first, obj.painting->second };
    return *this;
}
