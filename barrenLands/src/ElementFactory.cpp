#include "../include/ElementFactory.hpp"

/**
 * createProceduralObject()
 * @return ProceduralObject*
 */
ProceduralObject* ElementFactory::createProceduralObject(){
    //return new ProceduralObject();
    return new MenirRock();
}