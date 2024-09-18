#include "pch.h"
#include "PolyLine.h"

PolyLine::PolyLine(int x, int y, int z) : Figure()
{
    vert_mass = new std::vector<Vertex>{ Vertex(x, y, z) };
    isClosed = new bool(false);
}
PolyLine::PolyLine(const PolyLine& obj) : Figure(obj)
{
    vert_mass = new std::vector<Vertex>;
    std::for_each(obj.vert_mass->begin(), obj.vert_mass->end(),
        [&](Vertex& obj)
        {
            vert_mass->push_back(obj.copy());
        });
    isClosed = new bool(*obj.isClosed);
}
PolyLine& PolyLine::operator=(const PolyLine& obj)
{
    if (this == &obj) return *this;
    vert_mass->clear();
    std::copy(obj.vert_mass->begin(), obj.vert_mass->end(), std::back_inserter(*vert_mass));
    *isClosed = *obj.isClosed;
    return *this;
}
PolyLine::~PolyLine()
{
    delete vert_mass; delete isClosed;
}