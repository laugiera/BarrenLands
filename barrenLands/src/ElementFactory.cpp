#include "../include/ElementFactory.hpp"

/**
 * createProceduralObject()
 * @return ProceduralObject*
 */
ProceduralObject* ElementFactory::createProceduralRock(const std::string &name){
    if(name == "sand" || name == "grass")
        return new RoundRock();
    else if(name == "toundra")
        return new MenirRock();
    else
        return new CrystalRock();
}

ProceduralObject* ElementFactory::createProceduralGrass(const glm::vec3 &position){
        return new ProceduralGrass(position);
}