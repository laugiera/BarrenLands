//
// Created by Lou Landry on 18/01/2018.
//

#include "ProceduralSea.hpp"

ProceduralSea::ProceduralSea() {
    generateVertices();
    generateIndices();
}

void ProceduralSea::generateVertices() {
    vertices.clear();
    float nbDiv = 24;
    float angle = 2 * glm::pi<float>()/nbDiv;
    vertices.push_back(glimac::ShapeVertex(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec2(0.5,0.5)));
    for(int i = 0 ; i < nbDiv; i ++){
        float x = glm::cos( angle * i );
        float z = glm::sin( angle * i );
        vertices.push_back(glimac::ShapeVertex(glm::vec3(x,0,z), glm::vec3(0,1,0), glm::vec2((x+1)/2,(z+1)/2)));
    }
}

void ProceduralSea::generateIndices() {
    indices.clear();
    uint32_t nbDiv = 24;
    for(uint32_t i = 1; i < nbDiv; i++){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i+1);
    }
    indices.push_back(0);
    indices.push_back(nbDiv);
    indices.push_back(1);
}

void ProceduralSea::createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color *color) {
    std::vector<glcustom::Texture *> texture(1,textureManager->getRandomTexture("sea"));
    renderObject = new RenderObject(programManager->getTestProgram(), texture, new Color(0.25,0.55, 0.7));
    renderObject->fillData(vertices, indices);
}

void ProceduralSea::draw(const glm::mat4 &viewMatrix) {
    renderObject->transform(glm::vec3(0, Tools::seaLevel, 0), 0, glm::vec3(0,1,0), glm::vec3(100,100,100));
    renderObject->render(viewMatrix);
}
