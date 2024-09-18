// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DFXPARSER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DFXPARSER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DFXPARSER_EXPORTS
#define DFXPARSER_API __declspec(dllexport)
#else
#define DFXPARSER_API __declspec(dllimport)
#endif


extern "C" DFXPARSER_API void* getConverter(wchar_t* mode, wchar_t* input);
extern "C" DFXPARSER_API void deleteConverter(Converter* obj);
extern "C" DFXPARSER_API void MemoryLeaks(wchar_t** s_array, int& s_len);

extern "C" DFXPARSER_API HWND GetWindowHandle(Converter * obj) {
    return obj->paintObjects();
}
extern "C" DFXPARSER_API void showWindow(HWND hwnd, int nCmdShow) {
    ::ShowWindow(hwnd, nCmdShow);
}

extern "C" DFXPARSER_API void drawFigure(Converter* obj, HDC hdc, int* scale);

