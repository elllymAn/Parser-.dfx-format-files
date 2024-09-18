#pragma once
#include "Figure.h"
#include "Vertex.h"

class PolyLine :
    public Figure
{
private:
    bool* isClosed;
    std::vector <Vertex>* vert_mass;
public:
    PolyLine(bool close) { vert_mass = new std::vector<Vertex>; isClosed = new bool(close); }
    PolyLine(int x, int y, int z);
    PolyLine(const PolyLine& obj);
    PolyLine& operator=(const PolyLine& obj);
    ~PolyLine();
    Figure* copy() { return new PolyLine(*this); }
    void addVertex(Vertex obj) { vert_mass->push_back(obj); }
    std::wstring returnProperties() override {
        std::wstring out = L"PolyLine: \n";
        std::for_each(vert_mass->begin(), vert_mass->end(),
            [&out](Vertex& obj)
            {
                out += obj.returnProperties();
            });
        out += L"\n";
        return out;
    }
    std::vector <double>* getValues() override
    {
        std::vector <double>* points = new std::vector <double>();
        std::for_each(vert_mass->begin(), vert_mass->end(),
            [&points](Vertex vert)
            {
                std::vector<double>* values = vert.getValues();
                std::copy(values->begin(), values->end(), std::back_inserter(*points));
                delete values;
            });
        std::vector<double>* values = (*vert_mass)[0].getValues();
        if (*isClosed) { std::copy(values->begin(), values->end(), std::back_inserter(*points)); }
        delete values;
        return points;
    }
    void draw(HDC& hdc, HBRUSH& hbrush, int scale) override
    {
        for (int i = 0; i < vert_mass->size() - 1; i++)
        {
            std::vector <double>* coord1 = (*vert_mass)[i].getValues();
            MoveToEx(hdc, 100 + ((*coord1)[0])*scale, 100 + ((*coord1)[1])*scale, NULL);
            delete coord1;
            std::vector <double>* coord2 = (*vert_mass)[i+1].getValues();
            LineTo(hdc, 100 + ((*coord2)[0])*scale, 100 + ((*coord2)[1])*scale);
            delete coord2;
        }
    }
};

