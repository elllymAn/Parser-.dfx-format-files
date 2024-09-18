// dfxParser.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "dfxParser.h"


// This is an example of an exported variable


// This is an example of an exported function.
//DFXPARSER_API void ndfxParser(wchar_t* mode, wchar_t* input , double** data, long* len)
//{
//    std::wstring path(input);
//    std::wstring mod(mode);
//    std::string obj;
//    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
//    obj = converter.to_bytes(mod);
//    std::ofstream file("log.txt");
//    file << obj;
//    file.close();
//    Parser parser(path);
//    DB db;
//    std::vector<Figure*> buffer = parser.getObject();
//    db.addElems(buffer);
//    std::vector<std::vector <double>> buff = db.getPaintingPoints(obj);
//   // std::fstream file("log.txt");
//    //file << (*buff)[0].size();
//    //file.close();
//    std::vector<double> v1 = buff[0];
//    *len = v1.size();
//    auto size = (*len) * sizeof(double);
//    *data = static_cast<double*>(CoTaskMemAlloc(size));
//    memcpy(*data, v1.data(), size);
//}

DFXPARSER_API void* getConverter(wchar_t* mode, wchar_t* input) 
{
	std::wstring mod(mode);
	std::wstring path(input);
	return new Converter(path, mod); 
}
DFXPARSER_API void deleteConverter(Converter * obj)
{
	delete obj;
}

DFXPARSER_API void drawFigure(Converter* obj, HDC hdc, int* scale)
{
	HBRUSH brush = CreateSolidBrush(RGB(111,231, 301));
	SelectObject(hdc, brush);
	obj->paintObjectByHDC(hdc, brush,*scale);
	DeleteObject(brush);
}

DFXPARSER_API void MemoryLeaks(wchar_t** s_array, int& s_len)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	short* ii = new short(92);
	CoTaskMemFree(*s_array);
	HANDLE hLogFile;
	hLogFile = CreateFile(L"log.txt", GENERIC_WRITE,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);
	_CrtDumpMemoryLeaks();
	CloseHandle(hLogFile);
	std::wifstream in(L"log.txt");
	std::wstring  ws((std::istreambuf_iterator<wchar_t >(in)), std::istreambuf_iterator<wchar_t>());
	wchar_t* n_sarr = (wchar_t*)CoTaskMemAlloc((ws.size() + 1) * sizeof(wchar_t*));
	ZeroMemory((n_sarr), (ws.size() + 1) * sizeof(wchar_t));
	StringCchCatW(n_sarr, ws.size() + 1, ws.data());

	*s_array = n_sarr;
	s_len = ws.size() + 1;
}
//DFXPARSER_API void clearMemory(void* data)
//{
//    std::vector<std::vector<double>>* vecVec = static_cast<std::vector<std::vector<double>>*>(data);
//    delete vecVec;
//}

// This is the constructor of a class that has been exported.
