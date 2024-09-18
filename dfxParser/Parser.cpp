#include "pch.h"
#include "Parser.h"

Parser::Parser(std::wstring name)
{
    strs = new std::vector<std::wstring>;
    file.open(name);
    if (!file.is_open())
    {
        std::ofstream file("errorLog.txt");
        file << "error: incorrect path to file";
        file.close();
        throw "error: incorrect path to file";
    }
    std::wstring line;
    while (std::getline(file, line)) strs->push_back(line);
}
std::vector <Figure*>* Parser::getObject()
{
    std::vector<Figure*>* objects = new std::vector<Figure*>();
    std::vector <double> values;
    std::wstring type;
    std::vector<std::wstring>::iterator it = strs->begin();
    while (it != strs->end())
    {
        values.clear();
        std::wstring type = *(it++);
        std::vector<std::wstring>::iterator nextIt = std::find(it, strs->end(), L"  0");
        if (nextIt != strs->end())
        {
            if (type == L"CIRCLE")
            {
                while (it != nextIt)
                {
                    if ((*it) == L" 10")
                    {
                        values.push_back(std::stod(*(++it)));
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));
                    }
                    ++it;
                }
                objects->push_back(ObjectFactory::createObject<Circle, double, double, double, double>(values));
            }
            else if (type == L"POINT")
            {
                while (it != nextIt)
                {
                    if ((*it) == L" 10")
                    {
                        values.push_back(std::stod(*(++it)));
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));
                    }
                    ++it;
                }
                objects->push_back(ObjectFactory::createObject<Point, double, double, double>(values));
            }
            else if (type == L"POLYLINE")
            {
                while (*it != L"  0") ++it;
                PolyLine* poly = new PolyLine((*(--it) == L"     1"));
                while (*it != L"SEQEND")
                {
                    if ((*it) == L" 10")
                    {
                        values.push_back(std::stod(*(++it)));//центр
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));
                        poly->addVertex(Vertex(values[0], values[1], values[2]));
                        values.clear();
                    }
                    ++it;
                }
                objects->push_back(poly);
            }
            else if (type == L"ELLIPSE")
            {
                while (it != nextIt)
                {
                    if ((*it) == L" 10")
                    {
                        values.push_back(std::stod(*(++it)));//центр
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));

                        values.push_back(std::stod(*(++(++it))));//конечная точка
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));

                        while ((*it) != L" 40") ++it;
                        values.push_back(std::stod(*(++it)));//отношение осей
                        values.push_back(std::stod(*(++(++it))));//длина рисовки
                        values.push_back(std::stod(*(++(++it))));
                    }
                    ++it;
                }
                objects->push_back(ObjectFactory::createObject<EllipseForm, double, double, double, double,
                    double, double, double, double, double>(values));
            }
            else if (type == L"LINE")
            {
                while (it != nextIt)
                {
                    if ((*it) == L" 10")
                    {
                        values.push_back(std::stod(*(++it)));//начальная
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));

                        values.push_back(std::stod(*(++(++it))));//конечная точка
                        values.push_back(std::stod(*(++(++it))));
                        values.push_back(std::stod(*(++(++it))));
                    }
                    ++it;
                }
                objects->push_back(ObjectFactory::createObject<Line, double, double, double, double,
                    double, double>(values));
            }
        }
        else break;
    }
    return objects;
}