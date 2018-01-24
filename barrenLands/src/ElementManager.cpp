#include "ElementManager.hpp"

/**
 * createProceduralObject()
 * @return ProceduralObject*
 */
ProceduralObject* ElementManager::createProceduralRock(const std::string &name){
    if(name == "sand")
        return rocks[0];
    else if(name == "toundra")
        return rocks[1];
    else
        return rocks[2];
}

void ElementManager::createAllElements() {
    rocks.push_back(new RoundRock);
    rocks.push_back(new MenirRock);
    rocks.push_back(new CrystalRock);
}

ElementManager::ElementManager() {
    createAllElements();
}

ElementManager::~ElementManager() {

}

std::vector<ProceduralObject *> ElementManager::getAllElements() {
    std::vector<ProceduralObject *> elements;
    elements.insert( elements.end(), rocks.begin(), rocks.end());
    elements.insert( elements.end(), grass.begin(), grass.end());

    return elements;
}
