#pragma once
#include "Point.h"
class Line :
    public Figure
{
private:
    std::pair <Point, Point>* points;
public:
    Line(double x1, double x2, double x3, double y1, double y2, double y3);
    Line(const Line& obj);
    Line& operator=(const Line& obj);
    ~Line();
    std::wstring returnProperties() override {
        return L"Ellipse \n coordinates: " +
            points->first.returnProperties();
    }
    Figure* copy() { return new Line(*this); }
    std::vector <double>* getValues() override
    {
        std::vector<double>* values = new std::vector<double>();
        std::vector<double>* buffer;
        buffer = points->first.getValues();
        std::copy(buffer->begin(), buffer->end(), std::back_inserter(*values));
        delete buffer;
        buffer = points->second.getValues();
        std::copy(buffer->begin(), buffer->end(), std::back_inserter(*values));
        delete buffer;
        return values;
    }
    void draw(HDC& hdc, HBRUSH& hbrush, int scale) override
    {
        std::vector <double>* coord = points->first.getValues();
        MoveToEx(hdc, 100+((*coord)[0])*scale, 100+((*coord)[1])*scale, NULL);
        LineTo(hdc, 100+((*coord)[0])*scale, 100+((*coord)[1])*scale);
        delete coord;
    }
};

