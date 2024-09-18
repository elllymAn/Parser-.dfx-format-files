#pragma once
class Figure
{
protected:
    Figure() {}
    Figure(const Figure& obj) {}
    Figure& operator=(const Figure& obj) { return *this; }
public:
    virtual std::wstring returnProperties() = 0;
    virtual ~Figure() {}
    virtual Figure* copy() = 0;
    virtual std::vector <double>* getValues() = 0;
    virtual void draw(HDC& hdc, HBRUSH& hbrush, int scale) = 0;
};

