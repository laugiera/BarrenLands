#ifndef BARRENLANDS_ELEMENTFACTORY_HPP
#define BARRENLANDS_ELEMENTFACTORY_HPP
#include <RoundRock.hpp>
#include "MenirRock.hpp"
#include "CrystalRock.hpp"

/**
 * Class ElementFactory
 * Creates all sort of object for the map
 */
class ElementFactory{
public:
    ElementFactory() = default;

    ProceduralObject* createProceduralRock(const std::string &name);
};

#endif //BARRENLANDS_ELEMENTFACTORY_HPP
