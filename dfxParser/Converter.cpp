#include "pch.h"
#include "Converter.h"

Converter::Converter(std::wstring path, std::wstring mod)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string types;
    types = converter.to_bytes(mod);
    Parser parser(path);
    DB db;
    std::vector<Figure*>* buffer = parser.getObject();
    db.addElems(buffer);
    delete buffer;
    buff = new std::vector<Figure*>();
    std::vector<Figure*>* paint = db.getObjects(types);
    std::for_each(paint->begin(), paint->end(),
        [&](Figure* obj)
        {
            buff->push_back(obj->copy());
        });
    delete paint;
}

HWND Converter::paintObjects()
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
    wc.lpszClassName = L"EllipseWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"EllipseWindowClass",
        L"Ellipse Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, (HINSTANCE)GetModuleHandle(nullptr), nullptr);

    if (hwnd)
    {
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);
        HDC hdc = GetDC(hwnd);
        HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hbrush);
        std::for_each(buff->begin(), buff->end(),
            [&](Figure* shape) {
                shape->draw(hdc, hbrush, 5);
            });

        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_CLOSE)
            {
                ReleaseDC(hwnd, hdc);
                DeleteObject(hbrush);
                DestroyWindow(hwnd);
            }
        }
    }

    return hwnd;
}

void Converter::paintObjectByHDC(HDC& hdc, HBRUSH& hbrush, int scale)
{
    std::for_each(buff->begin(), buff->end(),
        [&](Figure* shape) {
            shape->draw(hdc, hbrush, scale);
        });
}