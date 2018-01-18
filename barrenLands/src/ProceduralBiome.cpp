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
    createElements();
}

ProceduralBiome::~ProceduralBiome(){
    delete color;
    //delete elements et textures
}

void ProceduralBiome::createElements() {
    //Use factory to fill elements attribute
}

void ProceduralBiome::setVertices(const std::vector<glimac::ShapeVertex *> &vertices) {
    ProceduralBiome::vertices = vertices;
}

void ProceduralBiome::addVertex(glimac::ShapeVertex *vertex) {
    vertices.push_back(vertex);
}

Color* ProceduralBiome::getColor() const {
    return color;
}

void ProceduralBiome::setColor(Color *color) {
    ProceduralBiome::color = color;
}
