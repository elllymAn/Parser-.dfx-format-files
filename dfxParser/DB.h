#pragma once
class DB
{
private:
    std::map<std::string, std::vector<Figure*>>* warehouse;
    std::vector <std::string>* listClasses(std::string names);
public:
    DB();
    DB(const DB& obj);
    std::vector <std::string>* getTypes();
    std::vector<std::vector <double>*>* getPaintingPoints(std::string name);
    std::vector<Figure*>* getObjects(std::string name);
    void addElems(std::vector <Figure*>* obj);
    DB& operator=(const DB& obj);
    ~DB();
};

