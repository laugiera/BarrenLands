#ifndef BARRENLANDS_ELEMENTFACTORY_HPP
#define BARRENLANDS_ELEMENTFACTORY_HPP

#include "MenirRock.hpp"

/**
 * Class ElementFactory
 * Creates all sort of object for the map
 */
class ElementFactory{
public:
    ElementFactory() = default;

    ProceduralObject* createProceduralObject();
    //ProceduralMap* createProceduralMap();
};

#endif //BARRENLANDS_ELEMENTFACTORY_HPP
