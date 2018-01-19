//
// Created by Lou Landry on 17/01/2018.
//

#include "ProceduralBiome.hpp"
/**
 * Constructor
 * @param _color
 */
ProceduralBiome::ProceduralBiome(Color *_color) : elements(), color(new Color(_color)) {
    indices.clear();
}
/**
 * Destructor
 */
ProceduralBiome::~ProceduralBiome(){
    delete color;
    for(ProceduralObject * el : elements){
        delete el;
    }
    for(glimac::ShapeVertex * v : vertices){
        delete v;
    }
}
/**
 * Create the procedural objects for all the element the biome contains
 * will certainly be replaced by addElement()
 */
void ProceduralBiome::createElements(glm::vec3 position) {
    //Use factory to fill elements attribute
    ElementFactory factory = ElementFactory();
    elements.push_back(factory.createProceduralObject());
    elements[elements.size()-1]->setPosition(position);
}
/**
 * Creates the render objects for all the elements the biome contains
 * @param programManager
 * @param textureManager
 */
void ProceduralBiome::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    for(ProceduralObject * element : elements){
        element->createRenderObject(programManager, textureManager, getColor());
    }
}

/**
 * Draws all the elements the biome contains
 * @param viewMatrix
 */
void ProceduralBiome::draw(const glm::mat4 &viewMatrix) {
    //setPosition();
    for(ProceduralObject * element : elements){
        //std::cout << element->getPosition() << std::endl;
        glm::mat4 modelMat = glm::scale(glm::translate(viewMatrix, element->getPosition()),glm::vec3(0.5));
        element->draw(modelMat);
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
