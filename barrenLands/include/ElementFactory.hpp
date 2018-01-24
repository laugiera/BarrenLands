#ifndef BARRENLANDS_ELEMENTFACTORY_HPP
#define BARRENLANDS_ELEMENTFACTORY_HPP

#include "FlatRock.hpp"
#include <RoundRock.hpp>
#include <SharpRock.hpp>
#include <ArchedRock.hpp>

/**
 * Class ElementFactory
 * Creates all sort of object for the map
 */
class ElementFactory{
public:
    ElementFactory() = default;

    ProceduralObject* createProceduralRock(const std::string &name);
    //ProceduralMap* createProceduralMap();
};

#endif //BARRENLANDS_ELEMENTFACTORY_HPP
