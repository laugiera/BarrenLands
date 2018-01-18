#ifndef BARRENLANDS_ELEMENTFACTORY_HPP
#define BARRENLANDS_ELEMENTFACTORY_HPP

#include "FlatRock.hpp"

class ElementFactory{
public:
    ElementFactory() = default;

    ProceduralObject* createProceduralObject();
    //ProceduralMap* createProceduralMap();
};

#endif //BARRENLANDS_ELEMENTFACTORY_HPP
