#include "../include/ElementFactory.hpp"

ProceduralObject* ElementFactory::createProceduralObject(){
    return new ProceduralObject();
}