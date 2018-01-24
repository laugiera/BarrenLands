#include "../include/ElementFactory.hpp"

/**
 * createProceduralObject()
 * @return ProceduralObject*
 */
ProceduralObject* ElementFactory::createProceduralRock(const std::string &name){
    if(name == "sand")
        return new RoundRock();
    else if(name == "toundra")
        return new MenirRock();
    else
        return new CrystalRock();
}