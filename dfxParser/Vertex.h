#pragma once
class Vertex
{
private:
    std::tuple <double, double, double>* coordinate;
public:
    Vertex(double x, double y, double z);
    Vertex(const Vertex& obj);
    Vertex& operator=(const Vertex& obj);
    Vertex copy() { return Vertex(*this); }
    ~Vertex();
    std::wstring returnProperties() {
        return L"Vertex \n coordinates: " +
            std::to_wstring(std::get<0>(*coordinate)) + L", " +
            std::to_wstring(std::get<1>(*coordinate)) + L", " +
            std::to_wstring(std::get<2>(*coordinate)) + L"\n";
    }
    std::vector <double>* getValues()
    {
        return new std::vector <double>{std::get<0>(*coordinate), std::get<1>(*coordinate)};
    }
};

