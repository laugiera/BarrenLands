//
// Created by Lou Landry on 17/01/2018.
//

#include "ProceduralBiome.hpp"

void ProceduralBiome::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    for(ProceduralObject * element : elements){
        element->createRenderObject(programManager, textureManager, getColor());
    }
}

ProceduralBiome::ProceduralBiome(Color *_color) : elements(), color(_color) {
    indices.clear();
    //createElements();
}

ProceduralBiome::~ProceduralBiome(){
    delete color;
    //delete elements et textures
}

void ProceduralBiome::createElements() {
    //Use factory to fill elements attribute
    ElementFactory factory = ElementFactory();
    elements.push_back(factory.createProceduralObject());
}

void ProceduralBiome::createElements(glm::vec3 position) {
    //Use factory to fill elements attribute
    ElementFactory factory = ElementFactory();
    elements.push_back(factory.createProceduralObject());
    elements[elements.size()-1]->setPosition(position);
}

void ProceduralBiome::setVertices(const std::vector<glimac::ShapeVertex *> &vertices) {
    ProceduralBiome::vertices = vertices;
}

void ProceduralBiome::addVertex(glimac::ShapeVertex *vertex) {
    vertices.push_back(vertex);
}

void ProceduralBiome::draw(const glm::mat4 &viewMatrix) {
    //setPosition();
    for(ProceduralObject * element : elements){
        //std::cout << element->getPosition() << std::endl;
        glm::mat4 modelMat = glm::scale(glm::translate(viewMatrix, element->getPosition()),glm::vec3(0.5));
        element->draw(modelMat);
    }
}

Color* ProceduralBiome::getColor() const {
    return color;
}

void ProceduralBiome::setColor(Color *color) {
    ProceduralBiome::color = color;
}
