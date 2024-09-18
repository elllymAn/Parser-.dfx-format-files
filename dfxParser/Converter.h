#pragma once
class Converter
{
private:
    std::vector<Figure*>* buff;
public:
    Converter(std::wstring path, std::wstring mod);
    Converter(const Converter& obj) = delete;
    Converter& operator=(const Converter& obj) = delete;
    ~Converter()
    {
       std::for_each(buff->begin(),buff->end(),
            [](Figure* elem)
            {
                delete elem;
            });
        delete buff;
    }
    HWND paintObjects();
    void paintObjectByHDC(HDC& hdc, HBRUSH& hbrush, int scale);

};

