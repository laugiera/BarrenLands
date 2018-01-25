//
// Created by Lou Landry on 17/01/2018.
//

#include "ProceduralBiome.hpp"
/**
 * Constructor
 * @param _color
 */
ProceduralBiome::ProceduralBiome(Color *_color,const std::string &_name) : elements(), color(new Color(_color)), name(_name) {
    indices.clear();
    createElements();
}
/**
 * Destructor
 */
ProceduralBiome::~ProceduralBiome(){
    delete color;
}
/**
 * Create the procedural objects for all the element the biome contains
 * will certainly be replaced by addElement()
 */
void ProceduralBiome::createElement(glm::vec3 position, const std::string &type) {
    //Use factory to fill elements attribute
    if(type == "rock"){
        if(rocks.empty()) throw std::runtime_error("Biome " + name + " : an element category is empty");
        rocks[0]->addInstance(position, *color);
    }
    else if (type == "grass"){
        grass.push_back(ElementManager::getInstance().createProceduralGrass(position));
        grass[grass.size()-1]->addInstance(glm::vec3(0,0,0), *color);
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

}


/**
 * Set the vertices vector
 * @param vertices
 */
void ProceduralBiome::setVertices(const std::vector<glimac::ShapeVertex *> &vertices) {
    ProceduralBiome::vertices = vertices;
}

/**
 * Add one vertex to vertices
 * @param vertex
 */
void ProceduralBiome::addVertex(glimac::ShapeVertex *vertex) {
    vertices.push_back(vertex);
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
    rocks.push_back(ElementManager::getInstance().createProceduralRock(name));
    //grass.push_back(ElementManager::getInstance().createProceduralGrass());
}
