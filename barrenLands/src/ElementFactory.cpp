#include "../include/ElementFactory.hpp"

/**
 * createProceduralObject()
 * @return ProceduralObject*
 */
ProceduralObject* ElementFactory::createProceduralRock(const std::string &name){
    //return new ProceduralObject();
    if(name == "sand")
        return new RoundRock();
    else
        return new RoundRock();
}