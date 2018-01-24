#ifndef BARRENLANDS_ELEMENTFACTORY_HPP
#define BARRENLANDS_ELEMENTFACTORY_HPP
#include <RoundRock.hpp>
#include "MenirRock.hpp"
#include "CrystalRock.hpp"
#include <ProceduralGrass.hpp>

/**
 * Class ElementFactory
 * Creates all sort of object for the map
 */
class ElementFactory{
public:
    ElementFactory() = default;

    ProceduralObject* createProceduralRock(const std::string &name);
    ProceduralObject* createProceduralGrass(const glm::vec3 &position);
};

#endif //BARRENLANDS_ELEMENTFACTORY_HPP
