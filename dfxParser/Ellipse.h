#pragma once
#include "Figure.h"
class EllipseForm :
    public Figure
{
private:
    std::tuple <double, double, double>* center;
    double* mainAxe;
    double* minorAxe;
    std::pair<double, double>* painting;
public:
    EllipseForm(double xC, double yC, double zC, double xE, double yE, double zE, double ratio, double begin,
        double end);
    EllipseForm(const EllipseForm& obj);
    EllipseForm& operator=(const EllipseForm& obj);
    ~EllipseForm();
    std::wstring returnProperties() override {
        return L"Ellipse \n center: " +
            std::to_wstring(std::get<0>(*center)) + L", " +
            std::to_wstring(std::get<1>(*center)) + L", " +
            std::to_wstring(std::get<2>(*center)) + L"\n axes:"
            + std::to_wstring(*mainAxe) + L", " + std::to_wstring(*minorAxe)
            + L"\n length of line: " + std::to_wstring(painting->first) + L", "
            + std::to_wstring(painting->second) + L"\n";
    }
    Figure* copy() { return new EllipseForm(*this); }
    std::vector <double>* getValues()
    {
        std::vector<double>* points = new std::vector<double>();
        for (double i = painting->first; i <= painting->second; i += 0.001)
        {
            points->push_back(std::get<0>(*center) + (*mainAxe) * cos(i));
            points->push_back(std::get<1>(*center) + (*minorAxe) * sin(i));
        }
        return points;
    }
    void draw(HDC& hdc, HBRUSH& hbrush, int scale) override
    {
        Ellipse(hdc, 100+(std::get<0>(*center)-*mainAxe)*scale, 100+(std::get<1>(*center) - *minorAxe)*scale, 
            100+(std::get<0>(*center) + *mainAxe)*scale, 100+(std::get<1>(*center) + *minorAxe)*scale);
    }
};

