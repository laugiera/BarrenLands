//
// Created by Lou Landry on 17/01/2018.
//

#include "ProceduralBiome.hpp"
/**
 * Constructor
 * @param _color
 */
ProceduralBiome::ProceduralBiome(Color *_color,const std::string &_name) : color(new Color(_color)), name(_name) {
    indices.clear();
    createElements();
    //std::cout << "this was a biome object not a real one " <<std::endl;
}
/**
 * Destructor
 */
ProceduralBiome::~ProceduralBiome(){
    delete color;
    //std::cout << "delete biome ok" << std::endl;
}
/**
 * Create the procedural objects for all the element the biome contains
 * will certainly be replaced by addElement()
 */
void ProceduralBiome::createElement(glm::vec3 position, const std::string &type) {
    //Use factory to fill elements attribute
    if(type == "rock"){
        if(rocks.empty()) throw std::runtime_error("Biome " + name + " : an the rock category is empty");
        if(name == "sand" || name == "toundra" || name == "rock") {
            int rand = int(NoiseManager::getInstance().getRandomFloat()*8);
            if(rand < 0) rand = 0;
            rocks[rand]->addInstance(position, *color);
        }
        if(name == "savannah"){
            int rand2 = int(NoiseManager::getInstance().getRandomFloat()*4);
            if(rand2 < 0) rand2 = 0;
            rocks[rand2]->addInstance(position, *color);
        }
        else{
            rocks[0]->addInstance(position, *color);
        }
    }
    else if (type == "grass"){
        grass.push_back(ElementManager::getInstance().createProceduralGrass(position));
        //grass[grass.size()-1]->addInstance(glm::vec3(0,0,0), *color);
    }
    else if (type == "tree"){
        if(trees.empty()) throw std::runtime_error("Biome " + name + " : an the tree category is empty");
        trees[0]->addInstance(position, *color);
    }

}
/**
 * Creates the render objects for all the elements the biome contains
 * @param programManager
 * @param textureManager
 */
void ProceduralBiome::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    for(ProceduralObject * rock : rocks){
        rock->createRenderObject(programManager, textureManager, getColor());
    }
    for(ProceduralObject * gras : grass){
        gras->createRenderObject(programManager, textureManager, getColor());
    }
    for(ProceduralObject * tree : trees){
        tree->createRenderObject(programManager, textureManager, getColor());
    }

}


/**
 * Get the biome color
 * @return
 */
Color* ProceduralBiome::getColor() const {
    return color;
}

/**
 * Set the biome color
 * @param color
 */
void ProceduralBiome::setColor(Color *color) {
    ProceduralBiome::color = color;
}

void ProceduralBiome::setName(const std::string &name) {
    ProceduralBiome::name = name;
}

const std::string &ProceduralBiome::getName() const {
    return name;
}

void ProceduralBiome::createElements() {
    if(name == "sand" || name == "toundra" || name == "rock"){
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 0));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 1));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 2));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 3));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 4));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 5));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 6));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 7));
    }
    else if(name == "savannah"){
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 0));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 1));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 2));
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name, 3));
    }
    else{
        rocks.push_back(ElementManager::getInstance().createProceduralRock(name));
    }
    if(name!="toundra"){
        trees.push_back(ElementManager::getInstance().createProceduralSapinTree());
    }
    else{
        trees.push_back(ElementManager::getInstance().createProceduralTree());
    }
    //grass.push_back(ElementManager::getInstance().createProceduralGrass());
}

const std::vector<ProceduralObject *> &ProceduralBiome::getRocks() const {
    return rocks;
}

