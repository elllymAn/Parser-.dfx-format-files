#pragma once
#include "Figure.h"
class Point :
    public Figure
{
private:
    std::tuple <double, double, double>* coordinate;
public:
    Point(double x, double y, double z);
    Point(const Point& obj);
    Point& operator=(const Point& obj);
    ~Point();
    Figure* copy() { return new Point(*this); }
    std::wstring returnProperties() override {
        return L"Point \n coordinates: " +
            std::to_wstring(std::get<0>(*coordinate)) + L", " +
            std::to_wstring(std::get<1>(*coordinate)) + L", " +
            std::to_wstring(std::get<2>(*coordinate)) + L"\n";
    }
    std::vector <double>* getValues() override
    {
        return new std::vector <double>{std::get<0>(*coordinate), std::get<1>(*coordinate)};
    }
    void draw(HDC& hdc, HBRUSH& hbrush, int scale) override
    {
        RECT r;
        SetRect(&r, 100+(std::get<0>(*coordinate) - 2)*scale, 100+(std::get<1>(*coordinate) + 2)*scale, 
           100+ (std::get<0>(*coordinate) + 2)*scale,100+ (std::get<1>(*coordinate) - 2)*scale);
        FillRect(hdc, &r, hbrush);
    }
};

