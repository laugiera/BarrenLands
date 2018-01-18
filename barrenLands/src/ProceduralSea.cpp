//
// Created by Lou Landry on 18/01/2018.
//

#include "ProceduralSea.hpp"

void ProceduralSea::generateVertices() {
    vertices.clear();
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,0,1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,0,1), glm::vec3(0,1,0), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,0,-1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,0,-1), glm::vec3(0,1,0), glm::vec2(0,1)));

}

void ProceduralSea::generateIndices() {
    indices.clear();
    indices =  {
                    0,1,2,
                    0,2,3,
            };
}

ProceduralSea::ProceduralSea() {
    generateVertices();
    generateIndices();
}

void ProceduralSea::createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color *color) {
    std::vector<glcustom::Texture *> texture(1,textureManager->getRandomTexture("sea"));
    renderObject = new RenderObject(programManager->getTestProgram(), texture, new Color(0,0,255));
    renderObject->fillData(vertices, indices);
}

void ProceduralSea::draw(const glm::mat4 &viewMatrix) {
    renderObject->transform(glm::vec3(0, Tools::seaLevel, 0), 0, glm::vec3(0,1,0), glm::vec3(100,100,100));
    renderObject->render(viewMatrix);
}
