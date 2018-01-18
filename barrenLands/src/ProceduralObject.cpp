//
// Created by Lou Landry on 15/01/2018.
//

#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "../include/ProceduralObject.hpp"

ProceduralObject::ProceduralObject() : renderObject(nullptr) {
    generateVertices();
    generateIndices();
}

ProceduralObject::~ProceduralObject() {
    delete renderObject;
}

void ProceduralObject::generateVertices() {
    vertices.clear();
    //FACE AVANT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,0,1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,0,1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,0,1), glm::vec2(1,1)));
    //Face ARRIERE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,0,-1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)));
    //FACE GAUCHE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(-1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(-1,0,0), glm::vec2(1,0)));
    //FACE DROITE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(1,0,0), glm::vec2(1,0)));
    //FACE HAUT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,1,0), glm::vec2(1,0)));
    //FACE BAS
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,-1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,-1,0), glm::vec2(1,0)));


}

void ProceduralObject::generateIndices() {
    indices.clear();
    uint32_t _indices[] =
            {
                    0,1,2,
                    0,2,3,
                    4,5,6,
                    4,6,7,
                    8,9,10,
                    8,10,11,
                    12,13,14,
                    12,14,15,
                    16,17,18,
                    16,18,19,
                    20,21,22,
                    20,22,23
            };

    indices = std::vector<uint32_t>(_indices, _indices + sizeof(_indices) / sizeof(uint32_t));

}

void ProceduralObject::generateNormals() {

}

void ProceduralObject::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    std::vector<glcustom::Texture *> textures = chooseTextures(textureManager);
    renderObject = new RenderObject(programManager->getTestProgram(), textures);
    renderObject->fillData(vertices, indices);
}

void ProceduralObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0,0,0), 0, glm::vec3(0,1,0), glm::vec3(1,1,1));
    renderObject->render(viewMatrix);
}

std::vector<glcustom::Texture *> ProceduralObject::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("sand"));
}


