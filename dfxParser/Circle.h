#pragma once
#include "Figure.h"
class Circle :
    public Figure
{
private:
    std::tuple <double, double, double>* center;
    double* radius;
public:
    Circle(double xC, double yC, double zC, double radius);
    Circle(const Circle& obj);
    Circle& operator=(const Circle& obj);
    ~Circle();
    std::wstring returnProperties() override {
        return L"Ellipse \n center: " +
            std::to_wstring(std::get<0>(*center)) + L", " +
            std::to_wstring(std::get<1>(*center)) + L", " +
            std::to_wstring(std::get<2>(*center)) + L"\n radius:"
            + std::to_wstring(*radius) + L"\n";
    }
    Figure* copy() { return new Circle(*this); }
    std::vector <double>* getValues() override
    {
        std::vector<double>* points = new std::vector<double>();
        for (double i = 0.0; i <= 6.283; i += 0.001)
        {
            points->push_back(std::get<0>(*center) + (*radius) * cos(i));
            points->push_back(std::get<1>(*center) + (*radius) * sin(i));
        }
        return points;
    }
    void draw(HDC& hdc, HBRUSH& hbrush, int scale) override
    {
        Ellipse(hdc, 100+ (std::get<0>(*center) - *radius)*scale, 100+ (std::get<1>(*center) - *radius)*scale,
            100+(std::get<0>(*center) + *radius)*scale, 100+(std::get<1>(*center) + *radius)*scale);
    }
};

