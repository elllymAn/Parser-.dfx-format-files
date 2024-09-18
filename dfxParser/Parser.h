#pragma once

class Parser : public ObjectFactory
{
private:
    std::vector <std::wstring>* strs;
    std::wifstream file;
public:
    Parser(std::wstring name);
    Parser(const Parser& obj) = delete;
    Parser& operator=(const Parser& obj) = delete;
    std::vector <Figure*>* getObject();
    ~Parser() { file.close();  delete strs; }
};

