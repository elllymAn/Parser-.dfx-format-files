#include "pch.h"
#include "DB.h"

std::vector <std::string>* DB::listClasses(std::string names)
{
    std::set <std::string> strs;
    std::stringstream ss(names);
    std::string item;
    while (std::getline(ss, item, ',')) { strs.insert(item); }
    std::vector <std::string>* answer = new std::vector <std::string>();
    std::set_union(strs.begin(), strs.end(), answer->begin(), answer->end(), std::back_inserter(*answer));
    return answer;
}

DB::DB()
{
    warehouse = new std::map<std::string, std::vector<Figure*>>();
}

DB::DB(const DB& obj)
{
    warehouse = new std::map<std::string, std::vector<Figure*>>();
    std::for_each(obj.warehouse->begin(), obj.warehouse->end(),
        [&](std::pair <const std::string, std::vector<Figure*>>& p)
        {
            std::vector<Figure*> buffer;
            std::transform(p.second.begin(), p.second.end(), std::back_inserter(buffer),
                [](Figure* elem)
                {
                    return elem->copy();
                });
            warehouse->insert({ p.first, buffer });
        }
    );
}

std::vector <std::string>* DB::getTypes()
{
    std::vector <std::string>* names = new std::vector <std::string>();
    std::for_each(warehouse->begin(), warehouse->end(),
        [&](std::pair <const std::string, std::vector<Figure*>>& p)
        {
            names->push_back(p.first);
        }
    );
    auto range = std::equal_range(names->begin(), names->end(), "");
    if (std::distance(range.first, range.second) == 0) return names;
    else
    {
        std::ofstream file("errorLog.txt");
        file << "vector consist empty objects";
        file.close();
        throw "vector consist empty objects";
    }
}

std::vector<std::vector <double>*>* DB::getPaintingPoints(std::string name)
{
    std::vector<std::string>* names = listClasses(name);
    std::vector<std::vector <double>*>* points = new std::vector<std::vector <double>*>();
    if (warehouse->size() == 0)
    {
        delete names;
        return points;
    }
    if ((*names)[0] != "all")
    {
        std::for_each(names->begin(), names->end(),
            [&](std::string& n)
            {
                std::map<std::string, std::vector<Figure*>>::iterator it = warehouse->find(n);
                /*if (it == warehouse->end() && warehouse->size() != 0)
                {
                    throw "undefined type of object";
                }*/
                std::for_each(it->second.begin(), it->second.end(),
                    [&points](Figure* obj)
                    {
                        points->push_back(obj->getValues());
                    });
            });
    }
    else
    {
        std::for_each(warehouse->begin(), warehouse->end(),
            [&](std::pair <const std::string, std::vector<Figure*>>& p)
            {
                std::for_each(p.second.begin(), p.second.end(),
                [&](Figure* obj)
                    {
                        points->push_back(obj->getValues());
                    });
            });
    }
    delete names;
    return points;
}

void DB::addElems(std::vector <Figure*>* obj)
{
    std::transform(obj->begin(), obj->end(), obj->begin(),
        [&](Figure* elem)
        {
            std::string key = typeid(*elem).name();
            std::map<std::string, std::vector<Figure*>> ::iterator it = warehouse->find(key);
            if (it == warehouse->end())
            {
                std::vector<Figure*> newVec{ elem };
                warehouse->insert({ key, newVec });
            }
            else
            {
                it->second.push_back(elem);
            }
            return elem;
        });
}

DB& DB::operator=(const DB& obj)
{
    if (this == &obj) return *this;
    std::for_each(warehouse->begin(), warehouse->end(),
        [](std::pair <const std::string, std::vector<Figure*>>& p)
        {
            std::for_each(p.second.begin(), p.second.end(),
            [](Figure* elem)
                {
                    delete elem;
                });
        }
    );
    warehouse->clear();
    std::for_each(obj.warehouse->begin(), obj.warehouse->end(),
        [&](std::pair <const std::string, std::vector<Figure*>>& p)
        {
            std::vector<Figure*> buffer;
            std::transform(p.second.begin(), p.second.end(), std::back_inserter(buffer),
                [](Figure* elem)
                {
                    return elem->copy();
                });
            warehouse->insert({ p.first, buffer });
        }
    );
    return *this;
}

std::vector<Figure*>* DB::getObjects(std::string name)
{
    std::vector<std::string>* names = listClasses(name);
    std::vector<Figure*>* figures = new std::vector<Figure*>();
    if (warehouse->size() == 0)
    {
        delete names;
        return figures;
    }
    if ((*names)[0] != "all")
    {
        std::for_each(names->begin(), names->end(),
            [&](std::string& n)
            {
                std::map<std::string, std::vector<Figure*>>::iterator it = warehouse->find(n);
                /*if (it == warehouse->end() && warehouse->size() != 0)
                {
                    throw "undefined type of object";
                }*/
                std::for_each(it->second.begin(), it->second.end(),
                    [&figures](Figure* obj)
                    {
                        figures->push_back(obj);
                    });
            });
    }
    else
    {
        std::for_each(warehouse->begin(), warehouse->end(),
            [&](std::pair <const std::string, std::vector<Figure*>>& p)
            {
                std::for_each(p.second.begin(), p.second.end(),
                [&](Figure* obj)
                    {
                        figures->push_back(obj);
                    });
            });
    }
    delete names;
    return figures;
}

DB::~DB()
{
    std::for_each(warehouse->begin(), warehouse->end(),
        [](std::pair <const std::string, std::vector<Figure*>>& p)
        {
            std::for_each(p.second.begin(), p.second.end(),
            [](Figure* obj)
                {
                    delete obj;
                });
        }
    );
    delete warehouse;
}